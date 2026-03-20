#define TRIG_PIN 2   // D4
#define ECHO_PIN 4   // D2
#define RELAY_PIN 14 // D5

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  
  // Safety: Force OFF at start
  digitalWrite(RELAY_PIN, HIGH); 
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2;

  // DEBUG: See what the sensor is doing
  Serial.print("Distance: ");
  Serial.println(distance);

  // TRIGGER: Only pump if distance is between 3cm and 12cm
  // This ignores '0' which is usually a sensor error
  if (distance > 3 && distance <= 12) {
    Serial.println("Hand Detected!");
    digitalWrite(RELAY_PIN, LOW);  // Turn ON
    delay(800);                    // Spray
    digitalWrite(RELAY_PIN, HIGH); // Turn OFF
    delay(1000);                   // Cooldown
  } else {
    digitalWrite(RELAY_PIN, HIGH); // Keep it OFF
  }
  delay(100);
}
