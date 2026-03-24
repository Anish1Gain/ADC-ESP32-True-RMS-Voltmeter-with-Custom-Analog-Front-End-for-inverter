//---ESP32 ADC-----

#define ADC_PIN 34
#define VREF 3.3
#define ADC_MAX 4095.0
#define OFFSET 1.65
#define GAIN 5.0
#define N 300

float v_rms = 0;

void setup() {
  Serial.begin(115200);

  analogReadResolution(12);
  analogSetPinAttenuation(ADC_PIN, ADC_11db);// reads till 3.3 V
}

void loop() {

  float sum_sq = 0.0;

  for (int i = 0; i < N; i++) {

    int adc_raw = analogRead(ADC_PIN);

    float v_adc  = (adc_raw / ADC_MAX) * VREF;
    float v_ac   = v_adc - OFFSET;
    float v_real = v_ac * GAIN;

    sum_sq += v_real * v_real;

    // Send waveform value (for Serial Plotter)
    Serial.print(v_real);
    Serial.print(" ");   // Space separates multiple signals

    delayMicroseconds(500);
  }

  v_rms = sqrt(sum_sq / N);

  // Sends plotter rms values in numbers
  Serial.println(v_rms);

  // print rms values realtime to monitor

  Serial.print("Voltage RMS = ");
  Serial.print(v_rms, 2);
  Serial.println(" V");
}
