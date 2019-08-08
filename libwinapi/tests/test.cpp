#include "gmock/gmock.h"
#include <libwinapi/lib.hpp>

using libwinapi::_internal::WinAPI;

class MockPacketStream {
  public:
	MOCK_METHOD(size_t, NumberOfPackets, (), (const));
};

TEST(TestMagicalNumber, ValidateMagicNumber)
{
	int magic_number = 11 * 2;

	EXPECT_EQ(magic_number, 22);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	auto result = RUN_ALL_TESTS();

	return result;
}
