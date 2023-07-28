#include <WiFi.h>
#include <FirebaseESP32.h>

// Firebase configuration
#define FIREBASE_HOST "smart-car-parking-78e97-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "OpSv8an45mlPgUA4ke5uJSVFivZMQ7ypyz29Zgh7"
#define WIFI_SSID "asrathore"
#define WIFI_PASSWORD "Aditya@9460"

// IR Sensor Pins
#define SENSOR_1_PIN 15
#define SENSOR_2_PIN 2
#define SENSOR_3_PIN 4

// Variables to store sensor values
int sensor1Value = 0;
int sensor2Value = 0;
int sensor3Value = 0;

// Number of available slots
int slots_filled = 0;

// Initialize Firebase
FirebaseData firebaseData;
FirebaseJson json;

void setup() {
  // Set up IR sensors
  pinMode(SENSOR_1_PIN, INPUT);
  pinMode(SENSOR_2_PIN, INPUT);
  pinMode(SENSOR_3_PIN, INPUT);

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  // Initialize Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  // Read sensor values
  sensor1Value = digitalRead(SENSOR_1_PIN);
  sensor2Value = digitalRead(SENSOR_2_PIN);
  sensor3Value = digitalRead(SENSOR_3_PIN);

  // Update Firebase
  json.clear();
  json.add("sensor_1", sensor1Value);
  json.add("sensor_2", sensor2Value);
  json.add("sensor_3", sensor3Value);
  Firebase.setJSON(firebaseData, "/parking", json);

  // Calculate available slots
  slots_filled = 3 - sensor1Value - sensor2Value - sensor3Value;

  // Update Firebase with available slots
  Firebase.setInt(firebaseData, "/slots_filled",  slots_filled);

  delay(1000);
}