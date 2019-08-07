#include <libwinapi/internal/win_api.hpp>

using libwinapi::internal::os_adapters::WinAPI;

int WinAPI::get_window_text_length_w(HWND hwnd)
{
	return GetWindowTextLengthW(hwnd);
}

int WinAPI::get_window_text_w(HWND hwnd, LPWSTR str, int max_count)
{
	return GetWindowTextW(hwnd, str, max_count);
}

BOOL WinAPI::enum_windows(WNDENUMPROC proc, LPARAM lparam)
{
	return EnumWindows(proc, lparam);
}

BOOL WinAPI::is_window_visible(HWND hwnd)
{
	return IsWindowVisible(hwnd);
}
