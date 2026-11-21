#include <tca9548a.h>

bool setMuxChecked(unsigned int address, unsigned int channel)
{
    if (address < 0x70 || address > 0x77 || channel >= 8)
        return false;

    i2c_t bus = *getBus();
    i2c_start(bus);
    bool selected = i2c_send_byte(bus, (uint8_t)((address << 1) | I2C_WRITE)) == I2C_ACK &&
                    i2c_send_byte(bus, (uint8_t)(1U << channel)) == I2C_ACK;
    i2c_stop(bus);
    return selected && i2c_status() == I2C_OK;
}

void setMux(unsigned int address, unsigned int channel)
{
    (void)setMuxChecked(address, channel);
}
