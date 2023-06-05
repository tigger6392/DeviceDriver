#include "DeviceDriver.h"
#include <Windows.h> //Sleep(200) -> 200ms
#include <cstdio>
#include <exception>
#include <stdexcept>

DeviceDriver::DeviceDriver(FlashMemoryInterface* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int firstTry = (int)m_hardware->read(address);
    Sleep(200);
    for (int i = 1; i < 5; i++)
    {
        if (firstTry != (int)m_hardware->read(address))
        {
            throw std::exception("Not constant read value!!");
        }
        Sleep(200);
    }
    return firstTry;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}