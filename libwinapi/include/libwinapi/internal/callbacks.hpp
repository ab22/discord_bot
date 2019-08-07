#pragma once

#include <Windows.h>

#include "../defines.hpp"
#include "models.hpp"
#include "win_api.hpp"

namespace libwinapi::internal::callbacks {
	using libwinapi::internal::models::EnumWindowsParam;
	using libwinapi::internal::models::WindowInfo;
	using libwinapi::internal::os_adapters::WinAPI;

	template <typename OS>
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
}
