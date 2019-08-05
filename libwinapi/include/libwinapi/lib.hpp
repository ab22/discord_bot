#pragma once

#include <string>
#include <vector>

#include "defines.hpp"
#include "models.hpp"

namespace libwinapi {
	EXPORT std::vector<models::WindowInfo> get_open_windows();
}
