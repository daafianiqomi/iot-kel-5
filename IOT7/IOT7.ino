#define TRIG_PIN  13
#define ECHO_PIN  12
#define WATER_SENSOR_PIN  35   // Pin untuk sensor air analog
#define VIBRATION_PIN 37

long duration;
int distance;
int waterValue;

void setup() { 
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(VIBRATION_PIN, OUTPUT);
}

void loop() {
  // Mengukur jarak menggunakan HC-SR04
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) {
    distance = -1;
  } else {
    distance = (duration * 0.034) / 2;
  }

  Serial.print("Jarak: ");
  if (distance == -1) {
    Serial.println("Tidak terdeteksi");
  } else {
    Serial.print(distance);
    Serial.println(" cm");
  }

  // Membaca nilai analog dari sensor air
  waterValue = analogRead(WATER_SENSOR_PIN);
  Serial.print("Nilai Sensor Air: ");
  Serial.println(waterValue);

  if (waterValue > 500) { // Threshold sesuai hasil pengujian
    Serial.println("Air terdeteksi!");
  } else {
    Serial.println("Tidak ada air.");
  }

  // Mengaktifkan motor getar jika ada objek atau air
  if ((distance != -1 && distance >= 30 && distance <= 40) || waterValue > 500) {
    digitalWrite(VIBRATION_PIN, HIGH);
    Serial.println("Motor getar aktif.");
  } else {
    digitalWrite(VIBRATION_PIN, LOW);
    Serial.println("Motor getar mati.");
  }

  delay(500);
}
