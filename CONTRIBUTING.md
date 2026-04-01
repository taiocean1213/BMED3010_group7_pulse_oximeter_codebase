# Contributing

Thanks for your interest in improving Open Pulse Oximeter.

## Ways to Contribute

- Fix bugs or improve reliability
- Add support for new hardware platforms
- Improve signal processing or clinical accuracy
- Improve documentation, examples, or onboarding
- Add tests and CI coverage

## Development Setup

### Prerequisites
- PlatformIO CLI or PlatformIO IDE
- Python 3

### Install
```bash
git clone https://github.com/taiocean1213/open-pulse-oximeter.git
cd open-pulse-oximeter
```

### Run tests
```bash
pio test -e native
```

### Build firmware
```bash
pio run -e due
```

## Code Style

- Follow existing Google-style C++ formatting
- Keep interfaces in `include/` and implementations in `lib/`
- Prefer small, focused pull requests
- Add or update tests when changing core behavior
- Document public interfaces clearly

## Pull Request Process

1. Create a branch from `main`
2. Make your changes in small commits
3. Run `pio test -e native`
4. Update docs if behavior changed
5. Open a pull request using the PR template

## Suggested Contribution Areas

- Better SpO2 calibration models
- Support for more displays or sensors
- Improved FFT/filter performance
- BLE / Wi-Fi streaming
- Better hardware simulation for tests
- Documentation and tutorial videos

## Reporting Bugs

Please use the GitHub bug report template and include:
- board / sensor details
- expected vs actual behavior
- logs, screenshots, or waveforms if available
- reproduction steps
