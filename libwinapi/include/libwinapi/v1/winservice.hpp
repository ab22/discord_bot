#pragma once

#include "defines.hpp"
#include "errors.hpp"
#include "internal/winapi.hpp"
#include "internal/winapi_adapter.hpp"

namespace libwinapi::v1::services {
	using WinAPI     = v1::_internal::WinAPI;
	using WinService = v1::_internal::adapters::WinAPIAdapter<WinAPI>;
}
