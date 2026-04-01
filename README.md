# Open Pulse Oximeter

[![CI](https://github.com/taiocean1213/BMED3010_group7_pulse_oximeter_codebase/actions/workflows/ci.yml/badge.svg)](https://github.com/taiocean1213/BMED3010_group7_pulse_oximeter_codebase/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg)](CONTRIBUTING.md)
[![GitHub Sponsors](https://img.shields.io/badge/Sponsor-GitHub%20Sponsors-ea4aaa)](https://github.com/sponsors/taiocean1213)

An open-source, Arduino Due-based **pulse oximeter** that measures **SpO2 (blood oxygen saturation)** and **heart rate** in real time using photoplethysmography (PPG) signals. Built with a modular C++ architecture, FFT-based signal filtering, and a clean hardware abstraction layer.

---

## Features

- **Real-time SpO2 and heart rate monitoring** using red and infrared LED PPG signals
- **FFT-based digital signal filtering** with configurable passbands and stopbands
- **Modular, interface-driven architecture** -- every component is swappable via abstract base classes
- **TFT display output** showing SpO2, heart rate, and live PPG waveform
- **Hardware abstraction layer** enabling easy porting to other microcontrollers
- **Comprehensive unit tests** using GoogleTest (runs natively without hardware)
- **PlatformIO build system** with support for both Arduino Due and native (desktop) targets

## Hardware Requirements

| Component | Specification |
|-----------|--------------|
| Microcontroller | Arduino Due (AT91SAM3X8E, 84 MHz) |
| Display | ILI9341 TFT LCD (SPI) |
| Red LED | Standard red LED for PPG |
| Infrared LED | IR LED for PPG |
| Photodiode | For detecting transmitted/reflected light |
| Temperature Sensor | MLX90614 (optional) |

### Pin Configuration

| Signal | Pin |
|--------|-----|
| TFT CS | 10 |
| TFT DC | 8 |
| TFT RST | 9 |

## Architecture

```
+------------------+     +-------------------------+     +----------------+
|   Main Loop      |---->|   EventController       |---->|    Display     |
|   (setup/loop)   |     |   (State Machine)       |     |    (ILI9341)   |
+------------------+     +-------------------------+     +----------------+
                              |           |
                    +---------+-----------+---------+
                    |                               |
              +-----v------+               +-------v--------+
              | PPGSignal   |               | Signal         |
              | Hardware    |               | Processing     |
              | Controller  |               | Pipeline       |
              +-----+------+               +-------+--------+
                    |                               |
              +-----v------+          +-------------+-------------+
              | Hardware    |          |             |             |
              | Abstraction |    +-----v----+  +----v-----+ +----v--------+
              | Layer       |    |  Filter  |  | SpO2     | | HeartRate   |
              | (Arduino)   |    |  (FFT)   |  | Calc     | | Calculator  |
              +---------+---+    +----------+  +----------+ +-------------+
                        |
                  +-----v------+
                  | Signal     |
                  | History    |
                  | (Ring Buf) |
                  +------------+
```

The system operates as a **state machine** cycling through:
1. **RedLedOn** -- Activate red LED
2. **PhotoDetectorReading** -- Read photodiode voltage
3. **InfraRedLedOn** -- Activate infrared LED
4. **PhotoDetectorReading** -- Read photodiode voltage again
5. **SignalIsProcessing** -- FFT filter + SpO2/HR calculation
6. **UiIsUpdating** -- Refresh display
7. **DeviceIdling** -- Wait for next sampling period

See [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md) for detailed documentation.

## Quick Start

### Prerequisites

- [PlatformIO CLI](https://docs.platformio.org/en/latest/core/installation.html) or [PlatformIO IDE for VS Code](https://platformio.org/install/ide?install=vscode)

### Clone and Build

```bash
git clone https://github.com/taiocean1213/BMED3010_group7_pulse_oximeter_codebase.git
cd BMED3010_group7_pulse_oximeter_codebase
```

#### Build for Arduino Due (requires hardware)

```bash
pio run -e due
```

#### Build and Run Tests (no hardware needed)

```bash
pio test -e native
```

#### Upload to Arduino Due

```bash
pio run -e due --target upload
```

### Static Analysis

```bash
pio check -e due
```

## Project Structure

```
.
├── include/                    # Interface (abstract base class) headers
│   ├── biomedical_metrics/     # HeartRateCalculator & SpO2Calculator interfaces
│   ├── event_controller/       # EventController interface
│   ├── hardware_driver_apis/   # Hardware abstraction layer interface
│   ├── ppg_signal_io/          # PPG signal controller interface
│   ├── signal_filter/          # Filter & FFT interfaces
│   ├── signal_history/         # Signal history interface
│   └── user_interface/         # Display interface
├── lib/                        # Implementation modules
│   ├── Display/                # ILI9341 TFT display driver
│   ├── EventController/        # Main state machine controller
│   ├── FastFourierTransform/   # FFT implementation (Cooley-Tukey)
│   ├── Filter/                 # FFT-based bandpass/stopband filter
│   ├── HardwareAbstractionLayer/  # Arduino hardware abstraction
│   ├── HeartRateCalculator/    # Heart rate from rising edge detection
│   ├── PPGSignalHardwareController/ # LED & photodiode control
│   ├── SignalHistory/          # Signal sample ring buffer
│   └── SpO2Calculator/         # SpO2 from R-value calculation
├── src/
│   └── main.cpp                # Arduino entry point (setup/loop)
├── test/
│   └── test_gtest/             # GoogleTest unit tests
├── docs/
│   └── ARCHITECTURE.md         # Detailed architecture documentation
├── .github/
│   ├── workflows/ci.yml        # GitHub Actions CI
│   ├── ISSUE_TEMPLATE/         # Bug report & feature request templates
│   ├── PULL_REQUEST_TEMPLATE.md
│   └── FUNDING.yml             # Sponsorship links
├── platformio.ini              # PlatformIO project configuration
├── CONTRIBUTING.md             # Contributor guidelines
├── CODE_OF_CONDUCT.md          # Community standards
├── SECURITY.md                 # Vulnerability reporting
└── LICENSE                     # MIT License
```

## Contributing

We welcome contributions of all kinds! Whether you're fixing a bug, adding a feature, improving documentation, or porting to new hardware -- we'd love your help.

Please read our [Contributing Guide](CONTRIBUTING.md) to get started.

### Good First Issues

Look for issues labeled [`good first issue`](https://github.com/taiocean1213/BMED3010_group7_pulse_oximeter_codebase/labels/good%20first%20issue) to find beginner-friendly tasks.

### Areas Where We Need Help

- Porting to ESP32, STM32, or Raspberry Pi Pico
- Bluetooth/Wi-Fi data streaming
- Mobile app for real-time monitoring
- Clinical validation and accuracy improvements
- PCB design for a compact form factor
- Documentation and tutorials

## Funding

If you find this project useful, please consider supporting its development:

- [GitHub Sponsors](https://github.com/sponsors/taiocean1213)

Your support helps us dedicate more time to improving accuracy, adding features, and maintaining the project.

## How It Works

### SpO2 Measurement
The pulse oximeter alternates between red and infrared LEDs. By measuring the ratio of absorbed light at these two wavelengths, it calculates the **R-value**, which maps to blood oxygen saturation (SpO2) using Beer-Lambert law principles.

### Heart Rate Detection
Heart rate is determined by counting **rising edges** in the filtered PPG signal that cross a dynamic threshold (set at 90% of the signal's min-max range), then extrapolating to beats per minute.

### Signal Processing Pipeline
Raw PPG signals pass through an **FFT-based bandpass filter** that:
1. Transforms the signal to the frequency domain
2. Zeros out frequency components outside the passband
3. Transforms back to the time domain via inverse FFT

## License

This project is licensed under the MIT License -- see the [LICENSE](LICENSE) file for details.

## Acknowledgments

This project originated as a biomedical engineering course project and has been open-sourced to benefit the maker, research, and medical device communities.
