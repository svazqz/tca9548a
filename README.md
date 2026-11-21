# ![TCA9548A Driver](docs/readme/banner.svg)

A C driver for the TCA9548A I²C multiplexer. `setMuxChecked()` reports invalid addresses, invalid channels, and failed bus transactions.

[Quick start](#quick-start) · [Validation](#validation) · [Project layout](#project-layout)

## Quick start

Use Git, a C11 compiler, and Make. The first build initializes the pinned `soft_i2c` submodule.

```sh
make
```

The driver archive is `build/libtca9548a.a`. Build the bundled `soft_i2c` library with WiringPi installed on the Raspberry Pi. Link both archives into your app and initialize the bus with `setupI2C()`.

## Validation

```sh
make test
```

The tests simulate I²C and run without connected hardware. Checks cover channels 0–7, addresses 0x70–0x77, and failed transactions.

## Project layout

| Path | Purpose |
| --- | --- |
| [`include/`](include/) | Public C interface |
| [`src/`](src/) | Driver implementation |
| [`tests/`](tests/) | Mock-bus unit tests |
| [`soft_i2c/`](soft_i2c/) | Pinned GPIO-based I²C submodule |
