#pragma once

#include "defines.hpp"
#include "errors.hpp"
#include "internal/winapi.hpp"
#include "internal/winapi_adapter.hpp"

#include <optional>
#include <vector>

namespace libwinapi::services {
	using WinAPI     = libwinapi::_internal::WinAPI;
	using WinService = libwinapi::_internal::adapters::WinAPIAdapter<WinAPI>;
}
