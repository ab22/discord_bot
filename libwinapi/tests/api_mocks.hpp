#include <gmock/gmock.h>
#include <libwinapi/lib.hpp>

using libwinapi::_internal::WinAPI;

namespace libtests {
	class MockWinAPI {
	  public:
		MOCK_METHOD(int, get_window_text_length_w, (HWND));
		MOCK_METHOD(int, get_window_text_w, (HWND, LPWSTR, int));
		MOCK_METHOD(BOOL, enum_windows, (WNDENUMPROC, LPARAM));
		MOCK_METHOD(BOOL, is_window_visible, (HWND));
	};
}
