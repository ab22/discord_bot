#include <libwinapi/win_service.hpp>

using libwinapi::errors::Win32Error;
using libwinapi::models::WindowInfo;
using libwinapi::services::WinService;

std::optional<std::vector<WindowInfo>> WinService::get_open_windows(Win32Error& err)
{
	return _os.get_open_windows(err);
}
