#include <libwinapi/lib.hpp>
#include <Windows.h>

// using namespace libwinapi;

int libwinapi::winapi_magic()
{
    return 22;
}

BOOL CALLBACK enum_windows_callback(HWND hwnd, LPARAM lparam)
{
    int title_length = GetWindowTextLengthW(hwnd);
    std::wstring title;

    if (!IsWindowVisible(hwnd) || title_length == 0)
        return TRUE;

    title.resize(title_length);
    GetWindowTextW(hwnd, title.data(), title_length);

    auto* windows = reinterpret_cast<std::vector<std::wstring>*>(lparam);
    windows->push_back(std::move(title));

    return TRUE;
}

std::vector<std::wstring> libwinapi::get_open_windows()
{
    std::vector<std::wstring> windows;
    EnumWindows(enum_windows_callback, reinterpret_cast<LPARAM>(&windows));

    return windows;
}
