#pragma once

#include "../models.hpp"

namespace libwinapi::internal::models {
	using libwinapi::models::WindowInfo;

	template <class OS>
	struct EnumWindowsParam {
		std::vector<WindowInfo>* windows;
		std::exception_ptr       eptr;
		OS*                      os;
	};
}
