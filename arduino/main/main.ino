/*
  Daniel Cargar Mahyar @Vocast CEO

  Arduino code for IoT projcet DDU
*/

#include <Arduino.h>
#include <ESP32Servo.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
#include "Securer.hpp"

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "Daniel - iPhone"
#define WIFI_PASSWORD "Daddyyyy"

// Insert Firebase project API Key
#define API_KEY "AIzaSyCEVmy83es4KlCdI3qKDmXr5eDln0EIRrQ"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://ddu-iot-default-rtdb.europe-west1.firebasedatabase.app/" 

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

Servo gate;
int servoPin = 2;

unsigned long sendDataPrevMillis = 0;
bool openGate;
float floatValue;
bool signupOK = false;

void setup() {
  Serial.begin(115200);
  setupServo() ;
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
  if (Firebase.RTDB.getFloat(&fbdo, "/gate/open")) {
    if (fbdo.dataType() == "boolean") {
      openGate = fbdo.boolData();
      if(openGate == true){
        gate.write(90);
      } else {
         gate.write(8);
      }
      Serial.println(floatValue);
    }
  }
  else {
    Serial.println(fbdo.errorReason());
    gate.write(8);
  }
  
}

void setupServo(){
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  gate.setPeriodHertz(50);    // standard 50 hz servo
  gate.attach(servoPin, 500, 2400); // attaches the servo on pin 18 to the servo object
}
