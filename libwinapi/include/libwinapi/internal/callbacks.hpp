#pragma once

#include <Windows.h>

#include "../defines.hpp"
#include "models.hpp"
#include "winapi.hpp"

namespace libwinapi::_internal {
	template <class API>
	class Callbacks {
	  private:
		using EnumWindowsParam = libwinapi::_internal::models::EnumWindowsParam<API>;
		using WindowTitle      = libwinapi::_internal::models::WindowTitle;

	  public:
		static BOOL CALLBACK enum_windows(HWND hwnd, LPARAM lparam)
		{
			auto* params = reinterpret_cast<EnumWindowsParam*>(lparam);
			auto* api    = params->api;

			try {
				WindowTitle title;
				int         text_length = api->get_window_text_length_w(hwnd);

				if (!api->is_window_visible(hwnd) || text_length == 0)
					return TRUE;

				// Increment required to take the full text of the window title. (?)
				text_length++;
				title.text.resize(text_length);
				title.length =
				    api->get_window_text_w(hwnd, title.text.data(), text_length);

				if (title.length == 0)
					return FALSE;

				params->titles->push_back(std::move(title));
			} catch (...) {
				params->eptr = std::current_exception();
				return FALSE;
			}

			return TRUE;
		}
	};
}
