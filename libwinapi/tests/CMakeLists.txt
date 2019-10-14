set(gtest_force_shared_crt ON CACHE BOOL "Always use msvcrt.dll" FORCE)
add_subdirectory("../vendor/googletest" "../vendor/googletest")

mark_as_advanced(
    BUILD_GMOCK_BUILD_GTEST BUILD_SHARED_LIBS
    gmock_build_tests gtest_build_samples gtest_build_tests
    gmock_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
)

set_target_properties(gtest PROPERTIES FOLDER vendor)
set_target_properties(gtest_main PROPERTIES FOLDER vendor)
set_target_properties(gmock PROPERTIES FOLDER vendor)
set_target_properties(gmock_main PROPERTIES FOLDER vendor)

add_executable(libwinapi_tests
	test.cpp
	api_mocks.hpp
	callback_tests.hpp
	winapi_adapter_tests.hpp
)

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	target_compile_options(libwinapi_tests
		PRIVATE
			/W4
	)
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	target_compile_options(libwinapi_tests
		PRIVATE
			-Wall
			-Wextra
			-Wvla
			-Wno-unused-function
			-Werror-implicit-function-declaration
			-Wno-missing-braces
			-Wno-missing-field-initializers
			-fno-strict-aliasing
			"$<$<CONFIG:Debug>:-O0;-g3;-ggdb>"
	)
else()
	message(FATAL_ERROR "No compiler flags specified for ${CMAKE_CXX_COMPILER_ID}")
endif()

target_link_libraries(libwinapi_tests
	PRIVATE
		libwinapi
		gtest
		gmock
		gtest_main
)

target_include_directories(libwinapi_tests
	PRIVATE
		"${CMAKE_CURRENT_BINARY_DIR}"
		"../include/"
		"../vendor/googletest/googletest/include"
		"${EXPECTED_INCLUDE_PATH}"
)

add_test(
	NAME
		libwinapi_tests
	COMMAND
		libwinapi_tests
)

set_target_properties(libwinapi_tests PROPERTIES FOLDER tests)
