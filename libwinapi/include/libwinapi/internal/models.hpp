#pragma once

#include "../core/models.hpp"

namespace libwinapi::_internal::models {
	using core::models::WindowTitle;

	template <class API>
	struct EnumWindowsParam {
		std::vector<WindowTitle>* titles;
		std::exception_ptr        eptr;
		API*                      api;
	};
}
