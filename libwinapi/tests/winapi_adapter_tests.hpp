#pragma once

#include "api_mocks.hpp"

#include <exception>
#include <memory>
#include <vector>

namespace libtests::winapi_adapter {
	using libwinapi::_internal::Callbacks;
	using libwinapi::_internal::adapters::WinAPIAdapter;
	using libwinapi::_internal::models::EnumWindowsParam;
	using libwinapi::core::errors::Win32Error;
	using libwinapi::core::models::WindowTitle;

	using testing::DoAll;
	using testing::Invoke;
	using testing::Return;
	using testing::Throw;

	TEST(Test_GetOpenWindows, should_return_open_windows_list)
	{
		WinAPIAdapter<MockWinAPI> win_adapter;
		Win32Error                err;
		std::vector<WindowTitle>  test_titles{WindowTitle{(HWND)0x1, L"Test1", 5},
                                             WindowTitle{(HWND)0x2, L"Test2", 6},
                                             WindowTitle{(HWND)0x3, L"Test3", 7}};

		EXPECT_CALL(win_adapter._api, enum_windows(testing::_, testing::_))
		    .Times(1)
		    .WillOnce(DoAll(
		        Invoke([&test_titles](testing::Unused, LPARAM lparam) {
			        auto params = reinterpret_cast<EnumWindowsParam<MockWinAPI>*>(lparam);

			        for (const auto& title : test_titles) {
				        params->titles->push_back(
				            WindowTitle{title.hwnd, title.text, title.length});
			        }
		        }),
		        Return(TRUE)));

		auto result = win_adapter.get_open_windows(err);
		EXPECT_TRUE(result.has_value());
		EXPECT_FALSE(err.is_error());

		auto titles = result.value();
		EXPECT_EQ(titles.size(), test_titles.size());

		for (size_t i = 0; i < titles.size(); i++) {
			EXPECT_EQ(titles[i].hwnd, test_titles[i].hwnd);
			EXPECT_EQ(titles[i].length, test_titles[i].length);
			EXPECT_STREQ(titles[i].text.c_str(), test_titles[i].text.c_str());
		}
	}

	TEST(Test_GetOpenWindows, shold_return_null_option)
	{
		WinAPIAdapter<MockWinAPI> win_adapter;
		Win32Error                err;
		std::vector<WindowTitle>  test_titles{WindowTitle{(HWND)0x1, L"Test1", 5},
                                             WindowTitle{(HWND)0x2, L"Test2", 5},
                                             WindowTitle{(HWND)0x2, L"Test3", 5}};

		EXPECT_CALL(win_adapter._api, enum_windows(testing::_, testing::_))
		    .Times(1)
		    .WillOnce(Return(FALSE));

		auto result = win_adapter.get_open_windows(err);
		EXPECT_FALSE(result.has_value());
		EXPECT_TRUE(err.is_error());
	}

	TEST(Test_GetOpenWindows, should_throw_exception_correctly)
	{
		constexpr static auto     exception_msg = "callback test exception";
		WinAPIAdapter<MockWinAPI> win_adapter;
		Win32Error                err;
		std::vector<WindowTitle>  test_titles{WindowTitle{(HWND)0x1, L"Test1", 5},
                                             WindowTitle{(HWND)0x2, L"Test2", 5},
                                             WindowTitle{(HWND)0x2, L"Test3", 5}};

		EXPECT_CALL(win_adapter._api, enum_windows(testing::_, testing::_))
		    .Times(1)
		    .WillOnce(DoAll(
		        Invoke([](testing::Unused, LPARAM lparam) {
			        auto params = reinterpret_cast<EnumWindowsParam<MockWinAPI>*>(lparam);

			        try {
				        throw std::exception(exception_msg);
			        } catch (...) {
				        params->eptr = std::current_exception();
			        }
		        }),
		        Return(FALSE)));

		try {
			auto result = win_adapter.get_open_windows(err);
			// Should not hit this code.
			EXPECT_TRUE(false);
		} catch (std::exception& e) {
			EXPECT_STREQ(e.what(), exception_msg);
		}
	}
}
