#pragma once

#include "defines.hpp"
#include "errors.hpp"
#include "internal/winapi.hpp"
#include "internal/winapi_adapter.hpp"

#include <optional>
#include <vector>

namespace libwinapi::services {
	class EXPORT WinService {
	  private:
		using Win32Error    = libwinapi::errors::Win32Error;
		using WinAPI        = libwinapi::_internal::WinAPI;
		using WinAPIAdapter = libwinapi::_internal::adapters::WinAPIAdapter<WinAPI>;

		WinAPIAdapter _winapi;

	  public:
		// Returns all open windows that are visible and have a title.
		std::optional<std::vector<models::WindowTitle>> get_open_windows(Win32Error& err);
	};
}
