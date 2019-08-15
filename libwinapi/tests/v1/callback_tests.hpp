#include "api_mocks.hpp"

#include <exception>
#include <string>
#include <vector>

namespace libtests::v1 {
	using libwinapi::_internal::Callbacks;
	using libwinapi::_internal::models::EnumWindowsParam;
	using libwinapi::models::WindowTitle;

	using testing::An;
	using testing::DoAll;
	using testing::Return;
	using testing::SetArrayArgument;
	using testing::Throw;

	TEST(TestEnumWindowsCallback, should_return_correct_titles)
	{
		EnumWindowsParam<v1::MockWinAPI> params;
		Callbacks<v1::MockWinAPI>        callbacks;
		std::vector<WindowTitle>         titles;
		v1::MockWinAPI                   api;
		BOOL                             cb_result;
		int                              test_str_len;
		std::wstring                     test_title = L"Window Test Title";
		HWND                             hwnd       = (HWND)(0x22);

		test_str_len  = static_cast<int>(test_title.size());
		params.api    = &api;
		params.titles = &titles;
		params.eptr   = nullptr;

		EXPECT_CALL(api, get_window_text_length_w(hwnd))
		    .Times(1)
		    .WillOnce(Return(test_str_len));
		EXPECT_CALL(api, is_window_visible(hwnd)).Times(1).WillOnce(Return(true));
		EXPECT_CALL(api, get_window_text_w(hwnd, testing::_, test_str_len + 1))
		    .Times(1)
		    .WillOnce(DoAll(
		        SetArrayArgument<1>(test_title.begin(), test_title.end()),
		        Return(test_str_len)));

		cb_result = callbacks.enum_windows(hwnd, reinterpret_cast<LPARAM>(&params));

		EXPECT_EQ(cb_result, TRUE);
		EXPECT_EQ(titles.size(), 1);
		EXPECT_EQ(titles.at(0).hwnd, hwnd);
		EXPECT_EQ(titles.at(0).length, test_title.size());
		EXPECT_EQ(test_title.compare(test_title), 0);
	}

	TEST(Test_EnumWindowsCallback, should_set_exception_ptr)
	{
		EnumWindowsParam<v1::MockWinAPI> params;
		Callbacks<v1::MockWinAPI>        callbacks;
		std::vector<WindowTitle>         titles;
		v1::MockWinAPI                   api;
		HWND                             hwnd = (HWND)(0x22);
		BOOL                             cb_result;
		auto                             msg     = "Test Exception";
		auto                             test_ex = std::exception(msg);

		params.api    = &api;
		params.titles = &titles;
		params.eptr   = nullptr;

		EXPECT_CALL(api, get_window_text_length_w(hwnd))
		    .Times(1)
		    .WillOnce(Throw(test_ex));

		cb_result = callbacks.enum_windows(hwnd, reinterpret_cast<LPARAM>(&params));

		EXPECT_EQ(cb_result, FALSE);
		EXPECT_NE(params.eptr, nullptr);

		try {
			std::rethrow_exception(params.eptr);
			// Should not hit this expect.
			EXPECT_TRUE(false);
		} catch (std::exception& ex) {
			EXPECT_STREQ(ex.what(), test_ex.what());
		}
	}
}
