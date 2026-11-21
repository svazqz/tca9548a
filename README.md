# tca9548a

Eight-channel I²C multiplexer driver. setMuxChecked returns false on invalid input or bus failure. Valid device addresses are 0x70 through 0x77 and channels are numbered 0 through 7.

Run make to initialize the pinned soft_i2c submodule if needed and build build/libtca9548a.a. Run make test for host-side tests with a simulated I²C bus.

For Raspberry Pi applications, build soft_i2c from the submodule with WiringPi installed. Link libtca9548a.a before libsoft_i2c.a, followed by -lwiringPi. Initialize the default bus with setupI2C before calling the driver.
