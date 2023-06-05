#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Project1/DeviceDriver.h"
#include "../Project1/FlashMemoryDevice.h"
#include "../Project1/DeviceDriver.cpp"

using namespace testing;
using namespace std;

class FlashMemoryMock : public FlashMemoryInterface
{
public:
    MOCK_METHOD(unsigned char, read, (long), (override));
    MOCK_METHOD((void), write, (long, unsigned char), (override));
};

TEST(FlashMemoryMockTest, InterfaceTest) {
    FlashMemoryMock flash_mock;
    EXPECT_CALL(flash_mock, read)
        .WillRepeatedly(Return(10));

    //Read
    DeviceDriver driver(&flash_mock);
    unsigned char actual = driver.read((long)0x10);
    cout << actual << endl;
    EXPECT_THAT(actual, Eq(10));

    //Write
    EXPECT_CALL(flash_mock, write)
        .Times(2);

    driver.write(0x10, 2);
    driver.write(0x10, 3);
}