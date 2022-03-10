/*
  Rui Santos
  Complete project details at our blog.
    - ESP32: https://RandomNerdTutorials.com/esp32-firebase-realtime-database/
    - ESP8266: https://RandomNerdTutorials.com/esp8266-nodemcu-firebase-realtime-database/
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
  Based in the RTDB Basic Example by Firebase-ESP-Client library by mobizt
  https://github.com/mobizt/Firebase-ESP-Client/blob/main/examples/RTDB/Basic/Basic.ino
*/

#include <Arduino.h>
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "Waoo4920_8DSY"
#define WIFI_PASSWORD "wtkm4348"

// Insert Firebase project API Key
#define API_KEY "AIzaSyCEVmy83es4KlCdI3qKDmXr5eDln0EIRrQ"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://ddu-iot-default-rtdb.europe-west1.firebasedatabase.app/"

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int intValue;
float floatValue;
bool signupOK = false;
String code {"321"};
void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  }
  else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  if (firebaseReadyCheck()) {
    sendDataPrevMillis = millis();
    if (Firebase.RTDB.getString(&fbdo, "/houses/house-1/password")) {
      if (fbdo.dataType() == "string") {
        String stringData = fbdo.stringData();
        Serial.println(stringData);
        if (stringData == code) {
          Serial.println("Code was correct, opening gate");
        } else {
          Serial.println("Code was wrong, trying other password");
          if (Firebase.RTDB.getString(&fbdo, "/houses/house-2/password")) {
            String stringData2 = fbdo.stringData();
            Serial.println(stringData2);
            if (stringData2 == code) {
              Serial.println("Code was correct, opening gate");
            } else {
              Serial.println("Wrong passwords. Reseting");
            }
          }
        }

      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }
  }
}

bool firebaseReadyCheck() {
  return (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0));
}
