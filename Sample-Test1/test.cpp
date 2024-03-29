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
}

TEST(FlashMemoryMockTest, NotContantReadValues) {
    FlashMemoryMock flash_mock;
    EXPECT_CALL(flash_mock, read)
        .Times(5)
        .WillOnce(Return(10))
        .WillOnce(Return(10))
        .WillOnce(Return(10))
        .WillOnce(Return(10))
        .WillOnce(Return(8));

    DeviceDriver driver(&flash_mock);
    EXPECT_THROW(driver.read(0x10), std::exception);
}

TEST(FlashMemoryMockTest, ContantReadValues) {
    FlashMemoryMock flash_mock;
    EXPECT_CALL(flash_mock, read)
        .Times(5)
        .WillOnce(Return(100))
        .WillOnce(Return(100))
        .WillOnce(Return(100))
        .WillOnce(Return(100))
        .WillOnce(Return(100));

    DeviceDriver driver(&flash_mock);
    int actual = driver.read(0x10);
    EXPECT_THAT(actual, Eq(100));
}

TEST(FlashMemoryMockTest, AlreadyWritten) {
    FlashMemoryMock flash_mock;
    EXPECT_CALL(flash_mock, read)
        .WillOnce(Return(0xFA));

    DeviceDriver driver(&flash_mock);
    EXPECT_THROW(driver.write(0x10, 10), std::exception);
}


TEST(FlashMemoryMockTest, NotWritten) {
    FlashMemoryMock flash_mock;
    EXPECT_CALL(flash_mock, read)
        .WillOnce(Return(0xFF));
    EXPECT_CALL(flash_mock, write);

    DeviceDriver driver(&flash_mock);
    driver.write(0x10, 10);
}
