#pragma once

#include <Windows.h>
#include <string>
#include <vector>

namespace libwinapi::v1::models {
	struct WindowTitle {
		HWND         hwnd;
		std::wstring text;
		int          length;
	};
}
