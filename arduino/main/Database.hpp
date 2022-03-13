#pragma once
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"
// Insert your network credentials
#define WIFI_SSID "Waoo4920_8DSY"
#define WIFI_PASS "wtkm4348"

// Insert Firebase project API Key
#define API_KEY "AIzaSyCEVmy83es4KlCdI3qKDmXr5eDln0EIRrQ"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://ddu-iot-default-rtdb.europe-west1.firebasedatabase.app/"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

class Database {
  private:
    bool signupOK;
    unsigned long sendDataPrevMillis = 0;
  public:
    Database() {
      this->signupOK = false;
    }

    void setupCon() {
      WiFi.begin(WIFI_SSID, WIFI_PASS);
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
      } else {
        Serial.printf("%s\n", config.signer.signupError.message.c_str());
      }

      /* Assign the callback function for the long running token generation task */
      config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

      Firebase.begin(&config, &auth);
      Firebase.reconnectWiFi(true);
    }

    bool conReady() {
      return (Firebase.ready() && signupOK);
    }

    String getHouse1Code() {
        Serial.println("Getting data for house 1: ");
        if (Firebase.RTDB.getString(&fbdo, "/houses/house-1/password")) {
          if (fbdo.dataType() == "string") {
            String stringData = fbdo.stringData();
            Serial.println(stringData);
            return stringData;
          } else {
            String nul = "";
            return nul;
          }
        } else {
          Serial.println(fbdo.errorReason());
          String nul = "";
          return nul;
        }

    }

    String getHouse2Code() {
        Serial.println("Getting data for house 2: ");
        if (Firebase.RTDB.getString(&fbdo, "/houses/house-2/password")) {
          if (fbdo.dataType() == "string") {
            String stringData = fbdo.stringData();
            Serial.println("Getting data for house 2: ");
            Serial.println(stringData);
            return stringData;
          } else {
            String nul = "";
            return nul;
          }
        } else {
          Serial.println(fbdo.errorReason());
          String nul = "";
          return nul;
        }
    }
};
