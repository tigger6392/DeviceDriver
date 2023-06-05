#include "DeviceDriver.h"
#include <Windows.h> //Sleep(200) -> 200ms
#include <cstdio>

DeviceDriver::DeviceDriver(FlashMemoryInterface* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    return (int)(m_hardware->read(address));
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}