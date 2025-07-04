// Motion Sensors
int g_motion = 2;     // Garden
int b_motion = 3;     // Bedroom
int l_motion = 5;     // Living Room
int H_motion = 9;     // Hallway
int k_motion = 10;     // Kitchen
int o_motion = 11;    // Outside

// Temperature Sensors (Analog Inputs)
int b_temp = A0;      // Bedroom temperature sensor
int l_temp = A1;      // Living room temperature sensor

// Gas Sensor
int k_gas = 12;       // Kitchen gas sensor (digital pin)

// Light Control Pins (PWM-capable)
int g_light = 44;     // Garden light
int b_light = 45;     // Bedroom light
int l_light = 46;     // Living room light
int H_light = 6;      // Hallway light
int k_light = 7;      // Kitchen light
int o_light = 8;      // Outside light

// Relays
int b_relay = 22;     // Bedroom air conditioner
int l_relay = 23;     // Living room air conditioner
int H_relay = 24;     // Hallway air conditioner
int k_relay = 25;     // Kitchen gas alarm

void setup() {
  Serial.begin(9600);

  // Garden
  pinMode(g_motion, INPUT);
  pinMode(g_light, OUTPUT);

  // Bedroom
  pinMode(b_motion, INPUT);
  pinMode(b_temp, INPUT);
  pinMode(b_light, OUTPUT);
  pinMode(b_relay, OUTPUT);

  // Living Room
  pinMode(l_motion, INPUT);
  pinMode(l_temp, INPUT);
  pinMode(l_light, OUTPUT);
  pinMode(l_relay, OUTPUT);

  // Hallway
  pinMode(H_motion, INPUT);
  pinMode(H_light, OUTPUT);
  pinMode(H_relay, OUTPUT);

  // Kitchen
  pinMode(k_motion, INPUT);
  pinMode(k_light, OUTPUT);
  pinMode(k_gas, INPUT);
  pinMode(k_relay, OUTPUT);

  // Outside
  pinMode(o_motion, INPUT);
  pinMode(o_light, OUTPUT);
}

void loop() {
  // GARDEN
  int gmotion = digitalRead(g_motion);
  if (gmotion == HIGH) {
    digitalWrite(g_light, HIGH);   // Motion detected → dim light
  } else {
    digitalWrite(g_light, LOW);     // No motion → lights off
  }

  // BEDROOM
  int bmotion = digitalRead(b_motion);
  if (bmotion == HIGH) {
    digitalWrite(b_light, HIGH);
  } else {
    digitalWrite(b_light, LOW);
  }

  float btemp = (analogRead(b_temp) * 5.0 * 100.0) / 1024.0;  // Convert analog to °C
  if (btemp > 25) {
    digitalWrite(b_relay, HIGH);  // Temp high → AC ON
  } else {
    digitalWrite(b_relay, LOW);   // Temp low → AC OFF
  }

  // LIVING ROOM
  int lmotion = digitalRead(l_motion);
  if (lmotion == HIGH) {
    digitalWrite(l_light, HIGH);
  } else {
    digitalWrite(l_light, LOW);
  }

  float ltemp = (analogRead(l_temp) * 5.0 * 100.0) / 1024.0;
  if (ltemp > 25) {
    digitalWrite(l_relay, HIGH);
    digitalWrite(H_relay, HIGH);  // Turn hallway AC on with living room
  } else {
    digitalWrite(l_relay, LOW);
    digitalWrite(H_relay, LOW);
  }

  // HALLWAY
  int hmotion = digitalRead(H_motion);
  if (hmotion == HIGH) {
    digitalWrite(H_light, HIGH);
  } else {
    digitalWrite(H_light, LOW);
  }

  // KITCHEN
  int kmotion = digitalRead(k_motion);
  if (kmotion == HIGH) {
    digitalWrite(k_light, HIGH);
  } else {
    digitalWrite(k_light, LOW);
  }

  int kgas = digitalRead(k_gas);
  if (kgas == LOW) {
    digitalWrite(k_relay, HIGH);  // Gas leak → trigger alarm
  } else {
    digitalWrite(k_relay, LOW);   // Safe
  }

  // OUTSIDE
  int omotion = digitalRead(o_motion);
  if (omotion == HIGH) {
    digitalWrite(o_light, HIGH);
  } else {
    digitalWrite(o_light,LOW);
  }

  delay(10); // Final delay to smooth execution
}
