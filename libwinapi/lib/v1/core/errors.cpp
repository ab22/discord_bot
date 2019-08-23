#include <libwinapi/v1/core/errors.hpp>

using libwinapi::v1::core::errors::Win32Error;

Win32Error::Win32Error() noexcept
    : _failed(false)
    , _code(0)
    , _msg(nullptr)
{
}

Win32Error::Win32Error(DWORD code, const char* message) noexcept
    : _failed(true)
    , _code(code)
    , _msg(message)
{
}

DWORD Win32Error::code() const noexcept
{
	return _code;
}

const char* Win32Error::message() const noexcept
{
	return _msg;
}

void Win32Error::set_error(const char* message) noexcept
{
	set_error(GetLastError(), message);
}

void Win32Error::set_error(DWORD code, const char* message) noexcept
{
	_failed = true;
	_code   = code;
	_msg    = message;
}

void Win32Error::clear_error() noexcept
{
	_failed = false;
	_code   = 0;
	_msg    = nullptr;
}

bool Win32Error::is_error() noexcept
{
	return _failed;
}

Win32Error::operator bool() const noexcept
{
	return _failed;
}
