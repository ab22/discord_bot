#pragma once

#include <optional>
#include <string>
#include <vector>

#include "defines.hpp"
#include "errors.hpp"
#include "models.hpp"

namespace libwinapi {
	// Retrieves all opened windows.
	EXPORT std::optional<std::vector<models::WindowInfo>>
	       get_open_windows(errors::Win32Error&);
}
