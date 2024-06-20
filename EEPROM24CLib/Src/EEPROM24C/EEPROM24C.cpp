#include "EEPROM24C/EEPROM24C.h"
#include "EEPROM24C/EEPROM24CDependencies.h"

using namespace MemoryDevices;


EEPROM24C::EEPROM24C(uint8_t deviceAddress, EnumEeprom24C eeprom24cType)
    : m_DeviceAddress { deviceAddress }, m_Eeprom24cType { eeprom24cType }, 
        m_PageSize { 32 },
        m_NumberOfPages { (m_Eeprom24cType == EEPROM24C_32) ? (uint16_t)512 : (m_Eeprom24cType == EEPROM24C_64) ? (uint16_t)1024 : (uint16_t)512 },
        m_PageShiftSize { 5 }
{
}

bool EEPROM24C::Write(uint16_t page, uint16_t offset, uint8_t *buffer, uint16_t bufferSize)
{
    bool bResult = bufferSize < m_PageSize * m_NumberOfPages;
    if (bResult)
    {
        uint16_t lastPage = page + (bufferSize + offset) / m_PageSize;
        uint16_t bufferIndex = 0;
        for (uint16_t pageNumber = page; pageNumber <= lastPage; pageNumber++)
        {
            uint16_t addressToWrite = pageNumber << m_PageShiftSize | offset;
            uint16_t bytesSizeToBeWritten = m_PageSize;
            if (bufferSize + offset < m_PageSize)
            {
                bytesSizeToBeWritten = bufferSize;
            }
            bResult = _write_to_i2c_memory(m_DeviceAddress, addressToWrite, &buffer[bufferIndex], bytesSizeToBeWritten);
            if (!bResult)
            {
                break;
            }
            bufferSize -= bytesSizeToBeWritten;
            bufferIndex += bytesSizeToBeWritten;
        }
    }
    return bResult;
}

bool EEPROM24C::Read(uint16_t page, uint16_t offset, uint8_t *buffer, uint16_t bufferSize)
{
    bool bResult = bufferSize < m_PageSize * m_NumberOfPages;
    if (bResult)
    {
        uint16_t lastPage = page + (bufferSize + offset) / m_PageSize;
        uint16_t bufferIndex = 0;
        for (uint16_t pageNumber = page; pageNumber <= lastPage; pageNumber++)
        {
            uint16_t addressToRead = pageNumber << m_PageShiftSize | offset;
            uint16_t bytesSizeToBeRead = m_PageSize;
            if (bufferSize + offset < m_PageSize)
            {
                bytesSizeToBeRead = bufferSize;
            }
            bResult = _read_from_i2c_memory(m_DeviceAddress, addressToRead, &buffer[bufferIndex], bytesSizeToBeRead);
            if (!bResult)
            {
                break;
            }
            bufferSize -= bytesSizeToBeRead;
            bufferIndex += bytesSizeToBeRead;
        }
    }
    return bResult;
}
