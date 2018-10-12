#define DURATION_REST 1501.0f
#define DURATION_AMPLITUDE 600.0f
#define STEERING_PIN A1
#define THROTTLE_PIN A0

SYSTEM_MODE(MANUAL);

float readChannel(int pin) {
  unsigned long duration = pulseIn(pin, HIGH);

  if (abs(duration) < 0.01f) {
    return 0.0f;
  }

  return constrain((duration - DURATION_REST) / DURATION_AMPLITUDE, -1.0f, 1.0);
}

void setup() {
  WiFi.off();

  pinMode(THROTTLE_PIN, INPUT);
  pinMode(STEERING_PIN, INPUT);
  pinMode(D7, OUTPUT);

  Serial1.begin(9600);
}

void loop() {
  float throttle = readChannel(THROTTLE_PIN);
  float steering = readChannel(STEERING_PIN) * -1; // Inverted: left is -1

  Serial.printf("0:%.4f\n", throttle);
  Serial.printf("1:%.4f\n", steering);

  Serial1.printf("0:%.4f\n", throttle);
  Serial1.printf("1:%.4f\n", steering);
}