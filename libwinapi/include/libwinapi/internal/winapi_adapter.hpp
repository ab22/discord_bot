#pragma once

#include "../core/errors.hpp"
#include "../core/models.hpp"
#include "../defines.hpp"
#include "callbacks.hpp"
#include "models.hpp"

#include <tl/expected.hpp>
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
		tl::expected<std::vector<WindowTitle>, Win32Error> get_open_windows()
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
				auto code = _api.get_last_error();
				auto err  = Win32Error(code, "enumerate windows failed");

				return tl::make_unexpected(std::move(err));
			}

			return titles;
		}
	};
}
