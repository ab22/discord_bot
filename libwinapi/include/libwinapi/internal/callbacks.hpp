#pragma once

#include <Windows.h>

#include "../defines.hpp"
#include "models.hpp"
#include "win_api.hpp"

namespace libwinapi::internal::callbacks {
	using libwinapi::internal::models::EnumWindowsParam;
	using libwinapi::internal::models::WindowTitle;
	using libwinapi::internal::os_adapters::WinAPI;

	template <typename OS>
	BOOL CALLBACK enum_windows_callback(HWND hwnd, LPARAM lparam)
	{
		auto* params = reinterpret_cast<EnumWindowsParam<OS>*>(lparam);
		auto* os     = params->os;

		try {
			WindowTitle title;
			int         text_length = os->get_window_text_length_w(hwnd);

			if (!os->is_window_visible(hwnd) || text_length == 0)
				return TRUE;

			// Increment required to take the full text of the window title. (?)
			text_length++;
			title.text.resize(text_length);
			title.length = os->get_window_text_w(hwnd, title.text.data(), text_length);

			if (title.length == 0)
				return FALSE;

			params->titles->push_back(std::move(title));
		} catch (...) {
			params->eptr = std::current_exception();
			return FALSE;
		}

		return TRUE;
	}
}
