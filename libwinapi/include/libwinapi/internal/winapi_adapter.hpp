#pragma once

#include "../core/errors.hpp"
#include "../core/models.hpp"
#include "../defines.hpp"
#include "callbacks.hpp"
#include "models.hpp"

#include <optional>
#include <vector>

namespace libwinapi::_internal::adapters {
	template <class API>
	class WinAPIAdapter {
	  private:
		using EnumWindowsParam = models::EnumWindowsParam<API>;
		using Win32Error       = core::errors::Win32Error;
		using WindowTitle      = core::models::WindowTitle;
		using Callbacks        = _internal::Callbacks<API>;

	  public:
		API _api;

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
