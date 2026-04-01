# Architecture

## Overview

Open Pulse Oximeter is structured as a modular embedded system with clear
interfaces between hardware access, signal acquisition, signal processing, and
user presentation.

## Main Components

### `src/main.cpp`
Creates the `EventController` and drives the Arduino `setup()` / `loop()` flow.

### `EventController`
The orchestration layer. It manages the device state machine and coordinates:
- LED switching
- photodiode reads
- filtering
- SpO2 computation
- heart-rate computation
- UI refreshes

### `HardwareAbstractionLayer`
Wraps microcontroller-specific behavior such as pin I/O, timing, analog reads,
and analog writes. This is the main portability boundary for new boards.

### `PPGSignalHardwareController`
Provides pulse-oximeter-specific hardware operations:
- set red LED intensity
- set infrared LED intensity
- read photodiode voltage
- fetch current time

### `SignalHistory`
Stores time-series samples used by the processing pipeline. The current
implementation behaves like a simple append-only history for practical test
sizes.

### `FastFourierTransform`
Implements FFT and inverse FFT logic for spectral processing.

### `Filter`
Transforms the signal into the frequency domain, applies passband/stopband
rules, and prepares filtered output.

### `SpO2Calculator`
Calculates an R-value from red and infrared channels and maps it to an SpO2
estimate.

### `HeartRateCalculator`
Uses threshold-based rising-edge counting to estimate beats per minute.

### `Display`
Renders values and a waveform to the ILI9341 TFT display.

## Data Flow

1. `EventController` turns on one LED channel
2. Photodiode voltage is sampled
3. Sample is stored in `SignalHistory`
4. When enough time has elapsed, `Filter` processes the signal
5. `SpO2Calculator` and `HeartRateCalculator` compute metrics
6. `Display` renders the updated values

## State Machine

The device cycles through these states:
- `EventSequenceStarting`
- `RedLedOn`
- `PhotoDetectorReading`
- `InfraRedLedOn`
- `PhotoDetectorReading`
- `SignalIsProcessing`
- `UiIsUpdating`
- `DeviceIdling`
- `EventSequenceEnding`

## Extensibility Points

Good places for contributors to extend the project:
- new sensor boards via `HardwareAbstractionLayer`
- alternate filtering algorithms via `FilterInterface`
- improved physiological models via `SpO2CalculatorInterface` and `HeartRateCalculatorInterface`
- different displays via `DisplayInterface`
- simulation / mock layers for hardware-free testing
