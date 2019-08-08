#include <libwinapi/win_service.hpp>

using libwinapi::errors::Win32Error;
using libwinapi::models::WindowTitle;
using libwinapi::services::WinService;

std::optional<std::vector<WindowTitle>> WinService::get_open_windows(Win32Error& err)
{
	return _winapi.get_open_windows(err);
}
