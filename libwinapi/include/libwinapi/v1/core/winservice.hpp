#pragma once

#include "../internal/winapi.hpp"
#include "../internal/winapi_adapter.hpp"
#include "defines.hpp"
#include "errors.hpp"

namespace libwinapi::v1::core::services {
	using WinAPI     = v1::_internal::WinAPI;
	using WinService = v1::_internal::adapters::WinAPIAdapter<WinAPI>;
}
