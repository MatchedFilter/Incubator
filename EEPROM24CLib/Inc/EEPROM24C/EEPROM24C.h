#ifndef _MEMORYDEVICES_EEPROM24C_H_
#define _MEMORYDEVICES_EEPROM24C_H_
#include <cinttypes>
namespace MemoryDevices
{

    enum EnumEeprom24C
    {
        EEPROM24C_32,
        EEPROM24C_64,
    };
    
    class EEPROM24C
    {
    public:
        EEPROM24C(uint8_t deviceAddress = 0xA0, EnumEeprom24C eeprom24cType = EEPROM24C_32);
        ~EEPROM24C() = default;
        bool Write(uint16_t page, uint16_t offset, uint8_t *buffer, uint16_t bufferSize);
        bool Read(uint16_t page, uint16_t offset, uint8_t *buffer, uint16_t bufferSize);

    private:
        const uint8_t m_DeviceAddress;
        const EnumEeprom24C m_Eeprom24cType;
        const uint16_t m_PageSize;
        const uint16_t m_NumberOfPages;
        const uint8_t m_PageShiftSize;
        uint8_t m_CurrentPage;
        
    };
} // namespace MemoryDevices

#endif // _MEMORYDEVICES_EEPROM24C_H_
