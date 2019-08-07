#pragma once

#include "defines.hpp"
#include "errors.hpp"
#include "internal/os_service.hpp"
#include "internal/win_api.hpp"

#include <optional>
#include <vector>

namespace libwinapi::services {
	using libwinapi::errors::Win32Error;
	using libwinapi::internal::os_adapters::WinAPI;
	using libwinapi::internal::services::OSService;

	class EXPORT WinService {
	  private:
		OSService<WinAPI> _os;

	  public:
		// Returns all open windows that are visible and have a title.
		std::optional<std::vector<models::WindowInfo>> get_open_windows(Win32Error& err);
	};
}
