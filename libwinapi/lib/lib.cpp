#include <Windows.h>
#include <exception>

#include <libwinapi/lib.hpp>

using WindowInfo = libwinapi::models::WindowInfo;
using Win32Error = libwinapi::errors::Win32Error;

struct EnumWindowsParam {
	std::vector<WindowInfo>* windows;
	std::exception_ptr       eptr;
};

BOOL CALLBACK enum_windows_callback(HWND hwnd, LPARAM lparam)
{
	auto* params = reinterpret_cast<EnumWindowsParam*>(lparam);

	try {
		WindowInfo info;
		int        title_length = GetWindowTextLengthW(hwnd);

		if (!IsWindowVisible(hwnd) || title_length == 0)
			return TRUE;

		info.title.resize(title_length + 1);
		GetWindowTextW(hwnd, info.title.data(), title_length + 1);
		params->windows->push_back(std::move(info));
	} catch (...) {
		params->eptr = std::current_exception();
		return FALSE;
	}

	return TRUE;
}

std::optional<std::vector<WindowInfo>> libwinapi::get_open_windows(Win32Error& err)
{
	std::vector<WindowInfo> windows;
	EnumWindowsParam        params;
	params.eptr    = nullptr;
	params.windows = &windows;

	auto result = EnumWindows(enum_windows_callback, reinterpret_cast<LPARAM>(&params));

	if (params.eptr)
		std::rethrow_exception(params.eptr);
	if (result == 0) {
		err.set_error("enumerate windows failed!");
		return std::nullopt;
	}

	return windows;
}
