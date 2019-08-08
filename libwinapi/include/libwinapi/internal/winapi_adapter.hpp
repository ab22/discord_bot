#pragma once

#include "../defines.hpp"
#include "../errors.hpp"
#include "../models.hpp"
#include "callbacks.hpp"
#include "models.hpp"

#include <optional>
#include <vector>

namespace libwinapi::_internal::adapters {
	template <class API>
	class EXPORT WinAPIAdapter {
	  private:
		using EnumWindowsParam = libwinapi::_internal::models::EnumWindowsParam<API>;
		using Win32Error       = libwinapi::errors::Win32Error;
		using WindowTitle      = libwinapi::models::WindowTitle;
		using Callbacks        = libwinapi::_internal::Callbacks<API>;

		API _api;

	  public:
		// Retrieves all opened windows.
		std::optional<std::vector<WindowTitle>> get_open_windows(Win32Error& err)
		{
			std::vector<WindowTitle> titles;
			EnumWindowsParam         params;
			params.eptr   = nullptr;
			params.titles = &titles;

			auto result = _api.enum_windows(
			    Callbacks::enum_windows, reinterpret_cast<LPARAM>(&params));

			if (params.eptr)
				std::rethrow_exception(params.eptr);
			if (result == 0) {
				err.set_error("enumerate windows failed!");
				return std::nullopt;
			}

			return titles;
		}
	};
}
