#pragma once

// Define EXPORT for any platform
#if defined _WIN32 || defined __CYGWIN__
	#ifdef WIN_EXPORT
	    // Exporting
		#ifdef __GNUC__
			#define EXPORT __attribute__((dllexport))
		#else
			#define EXPORT __declspec(dllexport)
		#endif
	#else
		#ifdef __GNUC__
			#define EXPORT __attribute__((dllimport))
		#else
			#define EXPORT __declspec(dllimport)
		#endif
	#endif
#else
	#if __GNUC__ >= 4
		#define EXPORT __attribute__((visibility("default")))
	#else
		#define EXPORT
	#endif
#endif
