#pragma once

#include "defines.hpp"

#include <optional>
#include <vector>

namespace libwinapi::services {
	using libwinapi::errors::Win32Error;
	using libwinapi::models::WindowInfo;

	template <class OS>
	struct EnumWindowsParam {
		std::vector<WindowInfo>* windows;
		std::exception_ptr       eptr;
		OS*                      os;
	};

	template <class OS>
	BOOL CALLBACK enum_windows_callback(HWND hwnd, LPARAM lparam)
	{
		auto* params = reinterpret_cast<EnumWindowsParam<OS>*>(lparam);
		auto* os     = params->os;

		try {
			WindowInfo info;
			int        title_length = os->get_window_text_length_w(hwnd);
			int        chars_copied = 0;

			if (!os->is_window_visible(hwnd) || title_length == 0)
				return TRUE;

			// Increment required to take the full text of the window title. (?)
			title_length++;
			info.title.resize(title_length);
			chars_copied = os->get_window_text_w(hwnd, info.title.data(), title_length);

			if (chars_copied == 0)
				return FALSE;

			params->windows->push_back(std::move(info));
		} catch (...) {
			params->eptr = std::current_exception();
			return FALSE;
		}

		return TRUE;
	}

	template <class OS>
	class EXPORT OSService {
	  private:
		OS _os;

	  public:
		// Retrieves all opened windows.
		std::optional<std::vector<WindowInfo>> get_open_windows(Win32Error& err)
		{
			std::vector<WindowInfo> windows;
			EnumWindowsParam<OS>    params;
			params.eptr    = nullptr;
			params.windows = &windows;
			params.os      = &_os;

			auto result = _os.enum_windows(
			    enum_windows_callback<OS>, reinterpret_cast<LPARAM>(&params));

			if (params.eptr)
				std::rethrow_exception(params.eptr);
			if (result == 0) {
				err.set_error("enumerate windows failed!");
				return std::nullopt;
			}

			return windows;
		}
	};
}
