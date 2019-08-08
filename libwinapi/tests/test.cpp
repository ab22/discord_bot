#include "gmock/gmock.h"
#include <libwinapi/lib.hpp>

using libwinapi::_internal::WinAPI;
using ::testing::Return;

class MockWinAPI {
  public:
	MOCK_METHOD(int, get_window_text_length_w, (HWND));
};

TEST(TestWinAPIMock, ValidateWindowTextLength)
{
	MockWinAPI api;

	ON_CALL(api, get_window_text_length_w(0)).WillByDefault(Return(22));
	EXPECT_CALL(api, get_window_text_length_w(0)).Times(1);
	EXPECT_EQ(api.get_window_text_length_w(0), 22);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	auto result = RUN_ALL_TESTS();

	return result;
}
