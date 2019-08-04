#pragma once

#include <string>
#include <vector>

#include "defines.hpp"

namespace libwinapi {
	EXPORT int winapi_magic();
	EXPORT std::vector<std::wstring> get_open_windows();
}
