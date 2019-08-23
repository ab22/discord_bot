#pragma once

#include "../core/models.hpp"

namespace libwinapi::v1::_internal::models {
	using v1::core::models::WindowTitle;

	template <class API>
	struct EnumWindowsParam {
		std::vector<WindowTitle>* titles;
		std::exception_ptr        eptr;
		API*                      api;
	};
}
