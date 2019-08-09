#pragma once

#include "../defines.hpp"
#include <Windows.h>

namespace libwinapi::v1::errors {
	class EXPORT Win32Error {
	  private:
		bool        _failed;
		DWORD       _code;
		const char* _msg;

	  public:
		Win32Error() noexcept;
		Win32Error(DWORD code, const char* message) noexcept;

		// Returns the Win32 error code. Usually retreived from GetLastError().
		DWORD code() const noexcept;

		// Returns the library specified error message.
		const char* message() const noexcept;

		// Sets the message by the specified parameter. This function will set the
		// error code automatically by calling GetLastError().
		void set_error(const char* message) noexcept;

		// Sets the code and error message.
		void set_error(DWORD code, const char* message) noexcept;

		// Sets the error code to 0, message to nullptr and clears internal error
		// state.
		void clear_error() noexcept;

		// Determines if the class contains an error.
		bool is_error() noexcept;

		// Returns true if the class contains an error.
		explicit operator bool() const noexcept;
	};
}
