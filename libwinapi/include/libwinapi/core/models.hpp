#pragma once

#include <Windows.h>
#include <string>
#include <vector>

namespace libwinapi::core::models {
	struct WindowTitle {
		HWND         hwnd;
		std::wstring text;
		int          length;
	};
}
