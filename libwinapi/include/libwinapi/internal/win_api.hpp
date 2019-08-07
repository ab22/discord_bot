#pragma once

#include "../defines.hpp"
#include <Windows.h>

namespace libwinapi::internal::os_adapters {
	class WinAPI {
	  public:
		int  get_window_text_length_w(HWND);
		int  get_window_text_w(HWND, LPWSTR, int);
		BOOL enum_windows(WNDENUMPROC, LPARAM);
		BOOL is_window_visible(HWND);
	};
}
