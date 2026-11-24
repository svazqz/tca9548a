# ![TCA9548A Driver](docs/readme/banner.svg)

A C driver for the TCA9548A I²C multiplexer. `setMuxChecked()` reports invalid addresses, invalid channels, and failed bus transactions.

[![Validation](https://github.com/svazqz/tca9548a/actions/workflows/ci.yml/badge.svg?branch=main)](https://github.com/svazqz/tca9548a/actions/workflows/ci.yml)

[Quick start](#quick-start) · [Validation](#validation) · [Project layout](#project-layout)

## Quick start

Use Git, a C11 compiler, and Make. The first build initializes the pinned `soft_i2c` submodule.

```sh
make
```

The driver archive is `build/libtca9548a.a`. Build the bundled `soft_i2c` library with WiringPi installed on the Raspberry Pi. Link both archives into your app and initialize the bus with `setupI2C()`.

## Validation

The same Docker command used by GitHub Actions runs the unit tests with
sanitizers and enforces at least 95% line coverage for the production driver.

```sh
git submodule update --init
docker run --rm --network none \
  --mount "type=bind,source=$PWD,target=/src,readonly" \
  gcc:14-bookworm sh /src/tests/run-container-tests.sh tca9548a
```

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

## License

Original project code is available under the [MIT License](LICENSE). Third-party components retain their own terms.
