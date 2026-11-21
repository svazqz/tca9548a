#include "mock_i2c.h"
#include <soft_i2c.h>
#include <assert.h>
#include <string.h>

i2c_mock bus_mock;
static i2c_t bus = { 9, 8 };
static size_t input_size;
static int status;

void mock_load(const uint8_t *input, size_t size)
{
    bus_mock = (i2c_mock){ 0 };
    input_size = size;
    status = I2C_OK;
    if (size != 0) {
        assert(size <= sizeof(bus_mock.input));
        memcpy(bus_mock.input, input, size);
    }
}

i2c_t *getBus(void) { return &bus; }
int i2c_status(void) { return status; }

void i2c_start(i2c_t port)
{
    assert(port.scl == bus.scl && port.sda == bus.sda);
    ++bus_mock.starts;
    status = I2C_OK;
}

void i2c_stop(i2c_t port)
{
    (void)port;
    ++bus_mock.stops;
    if (bus_mock.stop_status != I2C_OK)
        status = bus_mock.stop_status;
}

int i2c_send_byte(i2c_t port, uint8_t value)
{
    (void)port;
    assert(bus_mock.write_count < sizeof(bus_mock.writes));
    bus_mock.writes[bus_mock.write_count++] = value;
    return bus_mock.write_count == bus_mock.nack_at_write ? I2C_NACK : I2C_ACK;
}

uint8_t i2c_read_byte(i2c_t port)
{
    (void)port;
    assert(bus_mock.read_count < input_size);
    uint8_t value = bus_mock.input[bus_mock.read_count++];
    if (bus_mock.read_count == bus_mock.fail_at_read)
        status = I2C_BUS_ERROR;
    return value;
}

void i2c_send_bit(i2c_t port, int value)
{
    (void)port;
    assert(bus_mock.reply_count < sizeof(bus_mock.replies) / sizeof(bus_mock.replies[0]));
    if (status == I2C_OK)
        bus_mock.replies[bus_mock.reply_count++] = value;
}
