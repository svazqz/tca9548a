#ifndef TCA9548A_H
#define TCA9548A_H

#include <soft_i2c.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Returns false on an invalid address, channel, or bus failure. */
bool setMuxChecked(unsigned int address, unsigned int channel);
void setMux(unsigned int address, unsigned int channel);

#ifdef __cplusplus
}
#endif

#endif
