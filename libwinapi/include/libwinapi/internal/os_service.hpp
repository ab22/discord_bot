#pragma once

#include "../defines.hpp"
#include "../errors.hpp"
#include "../models.hpp"
#include "callbacks.hpp"
#include "models.hpp"
#include "win_api.hpp"

#include <optional>
#include <vector>

namespace libwinapi::internal::services {
	template <class OS>
	class EXPORT OSService {
	  private:
		using EnumWindowsParam = libwinapi::internal::models::EnumWindowsParam<OS>;
		using Win32Error       = libwinapi::errors::Win32Error;
		using WindowInfo       = libwinapi::models::WindowInfo;

		OS _os;

	  public:
		// Retrieves all opened windows.
		std::optional<std::vector<WindowInfo>> get_open_windows(Win32Error& err)
		{
			std::vector<WindowInfo> windows;
			EnumWindowsParam        params;
			params.eptr    = nullptr;
			params.windows = &windows;
			params.os      = &_os;

			auto result = _os.enum_windows(
			    libwinapi::internal::callbacks::enum_windows_callback<OS>,
			    reinterpret_cast<LPARAM>(&params));

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
