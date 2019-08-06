#pragma once

#include <Windows.h>

namespace libwinapi::os_adapters {
	class WinOS {
	  public:
		int  get_window_text_length_w(HWND);
		int  get_window_text_w(HWND, LPWSTR, int);
		BOOL enum_windows(WNDENUMPROC, LPARAM);
		BOOL is_window_visible(HWND);
	};
}
