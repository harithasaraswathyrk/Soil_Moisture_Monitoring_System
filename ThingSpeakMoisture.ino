#include <ESP8266WiFi.h>
#include <ThingSpeak.h> // Include the ThingSpeak library

// Define the analog pin for the moisture sensor
const int moisturePin = A0;

// ThingSpeak Channel settings
char ssid[] = "Harisowndharya";       // Replace with your Wi-Fi network SSID
char pass[] = "Hari@0601";   // Replace with your Wi-Fi network password
unsigned long channelId = 2521348;  // Replace with your ThingSpeak channel ID
const char *apiKey = "23MH7PYMKBSDI7DM";     // Replace with your ThingSpeak API Key

WiFiClient client;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Connect to Wi-Fi
  connectWiFi();
  
  // Initialize ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  // Read the analog value from the moisture sensor
  int moistureValue = analogRead(moisturePin);

  // Convert the analog value to percentage (assuming 0-1023 range)
  int moisturePercentage = map(moistureValue, 0, 1023, 100, 0);

  // Print the moisture percentage to the serial monitor
  Serial.print("Moisture Level: ");
  Serial.print(moisturePercentage);
  Serial.println("%");

  // Upload moisture percentage to ThingSpeak
  ThingSpeak.setField(1, moisturePercentage);
  int status = ThingSpeak.writeFields(channelId, apiKey);
  if (status == TS_OK_SUCCESS) {
    Serial.println("Data sent to ThingSpeak successfully");
  } else {
    Serial.println("Failed to send data to ThingSpeak");
  }
  delay(5000);
  // Add a delay to prevent flooding the serial monitor
  // delay(300000); // You can adjust this delay as needed
}

void connectWiFi() {
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to Wi-Fi");
}
