#ifndef MOCK_I2C_H
#define MOCK_I2C_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    size_t starts, stops, write_count, read_count, reply_count;
    size_t nack_at_write, fail_at_read;
    uint8_t writes[64], input[260];
    int replies[260];
    int stop_status;
} i2c_mock;

extern i2c_mock bus_mock;
void mock_load(const uint8_t *input, size_t size);

#endif
