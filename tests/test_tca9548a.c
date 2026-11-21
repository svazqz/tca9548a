#include "mock_i2c.h"
#include <tca9548a.h>
#include <assert.h>

int main(void)
{
    for (unsigned int channel = 0; channel < 8; ++channel) {
        unsigned int address = 0x70 + channel;
        mock_load(NULL, 0);
        assert(setMuxChecked(address, channel));
        assert(bus_mock.starts == 1 && bus_mock.stops == 1 && bus_mock.write_count == 2);
        assert(bus_mock.writes[0] == address * 2 && bus_mock.writes[1] == (1U << channel));
    }

    mock_load(NULL, 0);
    assert(!setMuxChecked(0x6f, 0) && !setMuxChecked(0x78, 0));
    assert(!setMuxChecked(0x70, 8));
    setMux(0x70, 8);
    assert(bus_mock.starts == 0);

    for (size_t write = 1; write <= 2; ++write) {
        mock_load(NULL, 0);
        bus_mock.nack_at_write = write;
        assert(!setMuxChecked(0x70, 0));
        assert(bus_mock.write_count == write && bus_mock.stops == 1);
    }

    mock_load(NULL, 0);
    bus_mock.stop_status = I2C_BUS_ERROR;
    assert(!setMuxChecked(0x70, 0));

    mock_load(NULL, 0);
    setMux(0x70, 5);
    assert(bus_mock.writes[1] == 0x20 && bus_mock.stops == 1);
    return 0;
}
