#include "v1/v1_tests.hpp"

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	auto result = RUN_ALL_TESTS();

	return result;
}
