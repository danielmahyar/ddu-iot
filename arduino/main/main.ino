/*
  Daniel Cargar Mahyar @Vocast CEO

  Arduino code for IoT projcet DDU
*/

#include <Arduino.h>
#include <ESP32Servo.h>
#include "KeyPadESP.hpp"
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <LiquidCrystal_I2C.h>

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

//Keypad
#define ROW_NUM     4 // four rows
#define COLUMN_NUM  4 // three columns

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

Servo gate;
int servoPin = 2;
bool openGate;
const int GATE_CLOSED_POS = 8;
const int GATE_OPEN_POS = 90;

unsigned long sendDataPrevMillis = 0;
float floatValue;
bool signupOK = false;

// set the LCD number of columns and rows
const int lcdColumns = 16;
const int lcdRows = 2;

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x3F, lcdColumns, lcdRows);

byte pin_rows[ROW_NUM] = {12, 14, 27, 26}; // GIOP18, GIOP5, GIOP17, GIOP16 connect to the row pins
byte pin_column[COLUMN_NUM] = {25, 33, 32, 35};  // GIOP4, GIOP0, GIOP2 connect to the column pins
KeyPadESP terminalPad = KeyPadESP(pin_rows, pin_column);

String code;
String correctCode;

void setup() {
  Serial.begin(115200);
  setupServo();
  setupFirebase();
  setupLcdScreen();
}

/*
    Pseudo Code:
    if key != NO_KEY:
      if key == #:
        String codes[] = getHouseCodeFirebase(); //Only acces to internet
        for(auto firebaseCode : codes):
          if firebaseCode == code:
            openGate();
      else
        code += key;
    else
      screen("Welcome");
*/
void loop() {
  char keyFromUser = terminalPad.readKey();
  if(keyFromUser){
    Serial.println(keyFromUser);
  }
  
//  if (firebaseReadyCheck()) {
//    char keyFromUser = terminalPad.getKey();
//    if (keyFromUser) {
//      lcd.clear();
//      lcd.setCursor(0, 0);
//      if (keyFromUser == '#') {
//        Serial.println(code);
//        if (code == correctCode) {
//          lcd.clear();
//          lcd.print("Opened");
//          lcd.setCursor(0, 1);
//          lcd.print("Velkommen luder");
//          gate.write(GATE_OPEN_POS);
//          delay(5000);
//          gate.write(GATE_CLOSED_POS);
//          Serial.println("Correct");
//          code = "";
//          lcd.clear();
//
//        } else {
//          code = "";
//          Serial.println("Wrong");
//          lcd.clear();
//          lcd.print("Wrong");
//        }
//
//      } else if (keyFromUser == '*') {
//        code = "";
//      } else {
//        code += keyFromUser;
//        lcd.print(code);
//        Serial.println(keyFromUser);
//      }
//    }
//  } else {
//    lcd.setCursor(0,0);
//  }
}

void setupFirebase() {
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
  } else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

}

bool firebaseReadyCheck() {
  return (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0));
}

void setupServo() {
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  gate.setPeriodHertz(50);    // standard 50 hz servo
  gate.attach(servoPin, 500, 2400); // attaches the servo on pin 18 to the servo object
  gate.write(GATE_CLOSED_POS);
}

void setupLcdScreen() {
  // initialize LCD
  lcd.init();
  // turn on LCD backlight
  lcd.backlight();
}

// Function to scroll text
// The function acepts the following arguments:
// row: row number where the text will be displayed
// message: message to scroll
// delayTime: delay between each character shifting
// lcdColumns: number of columns of your LCD
void scrollText(int row, String message, int delayTime, int lcdColumns) {
  for (int i = 0; i < lcdColumns; i++) {
    message = " " + message;
  }
  message = message + " ";
  for (int pos = 0; pos < message.length(); pos++) {
    lcd.setCursor(0, row);
    lcd.print(message.substring(pos, pos + lcdColumns));
    delay(delayTime);
  }
}
