#pragma once

#include "../models.hpp"

namespace libwinapi::internal::models {
	using libwinapi::models::WindowTitle;

	template <class OS>
	struct EnumWindowsParam {
		std::vector<WindowTitle>* titles;
		std::exception_ptr        eptr;
		OS*                       os;
	};
}
