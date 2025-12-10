#pragma once

#include <string>
#include <cstdint>
#include <windows.h>

/*
  SerialClient

  Minimal wrapper around a Windows serial port (COMx).
  It handles opening the port, configuring baud rate,
  reading bytes and closing the handle.
*/

class SerialClient {
public:
    SerialClient(const std::string& portName, DWORD baudRate = CBR_115200);
    ~SerialClient();

    bool isConnected() const;
    bool readByte(uint8_t& byte);

private:
    HANDLE hSerial;
    bool connected;
};
