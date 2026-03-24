# ADC-ESP32-True-RMS-Voltmeter-with-Custom-Analog-Front-End-for-inverter
This project is a complete hardware and software solution designed to safely measure and process AC voltages using an ESP32 microcontroller. Because the ESP32’s Analog-to-Digital Converter (ADC) can only handle positive voltages up to 3.3V, the custom analog circuit acts as a critical interface. It conditions a $\pm 5V$ AC input signal by scaling and shifting it into a safe $0V$ to $3.3V$ window. The ESP32 firmware then samples this conditioned signal, reconstructs the original waveform digitally, and calculates the True RMS voltage in real-time.

System Architecture & Key Features
1. Analog Front-End (Hardware Conditioning)

Attenuation & DC Biasing: The core of the circuit uses an op-amp (U5) in an inverting configuration to step down the incoming 5V AC signal. A precise 1.24V DC reference is established using a voltage divider (R1, R2) and buffered by a voltage follower (U1). This reference biases the U5 op-amp, shifting the bipolar AC signal entirely above ground so the ESP32 can safely read the full wave without clipping.

Overvoltage Protection: To safeguard the microcontroller, a 1k current-limiting resistor (R5) is paired with BAT54 Schottky clamping diodes (U3, U4). This arrangement ensures that if the input unexpectedly spikes, the voltage delivered to the ADC pin will safely clamp to the 3.3V rail or ground.


2. Digital Signal Processing (ESP32 Firmware)

High-Speed Sampling: The ESP32 reads the conditioned analog signal with a 12-bit resolution, taking a sample every 500 microseconds to capture the waveform accurately.

Waveform Reconstruction: The firmware mathematically removes the mid-rail DC offset (OFFSET = 1.65) that was introduced by the hardware and applies a digital multiplier (GAIN = 5.0) to scale the signal back to its original amplitude for accurate calculations.

True RMS Calculation: Instead of a simple peak-to-peak estimation, the code squares each instantaneous voltage reading, sums them over a set period (N = 300 samples), and calculates the square root of the average. This provides an accurate Root Mean Square (RMS) voltage, which is then printed to the Serial Monitor.
