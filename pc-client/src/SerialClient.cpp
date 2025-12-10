#include "SerialClient.h"
#include <iostream>

SerialClient::SerialClient(const std::string& portName, DWORD baudRate)
    : hSerial(INVALID_HANDLE_VALUE), connected(false)
{
    // Example portName: "COM3" or "\\\\.\\COM3"
    std::string fullPortName = portName;
    if (portName.rfind("\\\\.\\", 0) != 0) {
        fullPortName = "\\\\.\\" + portName;
    }

    hSerial = CreateFileA(
        fullPortName.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0,
        nullptr,
        OPEN_EXISTING,
        0,
        nullptr
    );

    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: cannot open serial port " << fullPortName << "\\n";
        connected = false;
        return;
    }

    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error: GetCommState failed\\n";
        CloseHandle(hSerial);
        hSerial = INVALID_HANDLE_VALUE;
        connected = false;
        return;
    }

    dcbSerialParams.BaudRate = baudRate;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity   = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error: SetCommState failed\\n";
        CloseHandle(hSerial);
        hSerial = INVALID_HANDLE_VALUE;
        connected = false;
        return;
    }

    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout         = 50;
    timeouts.ReadTotalTimeoutConstant    = 50;
    timeouts.ReadTotalTimeoutMultiplier  = 10;
    timeouts.WriteTotalTimeoutConstant   = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(hSerial, &timeouts)) {
        std::cerr << "Error: SetCommTimeouts failed\\n";
        CloseHandle(hSerial);
        hSerial = INVALID_HANDLE_VALUE;
        connected = false;
        return;
    }

    connected = true;
}

SerialClient::~SerialClient() {
    if (hSerial != INVALID_HANDLE_VALUE) {
        CloseHandle(hSerial);
    }
}

bool SerialClient::isConnected() const {
    return connected;
}

bool SerialClient::readByte(uint8_t& byte) {
    if (!connected) {
        return false;
    }

    DWORD bytesRead = 0;
    BOOL status = ReadFile(
        hSerial,
        &byte,
        1,
        &bytesRead,
        nullptr
    );

    if (!status) {
        // read error
        return false;
    }

    return (bytesRead == 1);
}
