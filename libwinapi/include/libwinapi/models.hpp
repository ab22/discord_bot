#pragma once

#include <Windows.h>
#include <string>
#include <vector>

namespace libwinapi::models {
	struct WindowInfo {
		HWND         hwnd;
		std::wstring title;
	};
}
