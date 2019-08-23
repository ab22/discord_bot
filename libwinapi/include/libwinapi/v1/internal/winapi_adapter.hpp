#pragma once

#include "../core/errors.hpp"
#include "../core/models.hpp"
#include "../defines.hpp"
#include "callbacks.hpp"
#include "models.hpp"

#include <optional>
#include <vector>

namespace libwinapi::v1::_internal::adapters {
	template <class API>
	class EXPORT WinAPIAdapter {
	  private:
		using EnumWindowsParam = models::EnumWindowsParam<API>;
		using Win32Error       = v1::core::errors::Win32Error;
		using WindowTitle      = v1::core::models::WindowTitle;
		using Callbacks        = _internal::Callbacks<API>;

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
