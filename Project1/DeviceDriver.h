#pragma once
#include "FlashMemoryDevice.h"

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryInterface* hardware);
    int read(long address);
    void write(long address, int data);

protected:
    FlashMemoryInterface* m_hardware;
};