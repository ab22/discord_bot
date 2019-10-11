#pragma once

#include "../internal/winapi.hpp"
#include "../internal/winapi_adapter.hpp"
#include "../defines.hpp"
#include "errors.hpp"

namespace libwinapi::core::services {
	using WinAPI     = _internal::WinAPI;
	using WinService = _internal::adapters::WinAPIAdapter<WinAPI>;
}
