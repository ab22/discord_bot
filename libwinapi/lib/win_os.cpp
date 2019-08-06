#include <libwinapi/win_os.hpp>

using libwinapi::os_adapters::WinOS;

int WinOS::get_window_text_length_w(HWND hwnd)
{
	return GetWindowTextLengthW(hwnd);
}

int WinOS::get_window_text_w(HWND hwnd, LPWSTR str, int max_count)
{
	return GetWindowTextW(hwnd, str, max_count);
}

BOOL WinOS::enum_windows(WNDENUMPROC proc, LPARAM lparam)
{
	return EnumWindows(proc, lparam);
}

BOOL WinOS::is_window_visible(HWND hwnd)
{
	return IsWindowVisible(hwnd);
}
