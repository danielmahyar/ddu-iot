/*
  Daniel Cargar Mahyar @Vocast CEO

  Arduino code for IoT projcet DDU
*/

#include <Arduino.h>
#include "KeyPadESP.hpp"
#include "Database.hpp"
#include "Gate.hpp"
#include <LiquidCrystal_I2C.h>

Database db = Database();
Gate gate = Gate();

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

void setup() {
  Serial.begin(115200);
  gate.setupServo();
  db.setupCon();
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
  if (db.conReady()) {
    char keyFromUser = terminalPad.readKey();
    if (keyFromUser) {
//      lcd.clear();
//      lcd.setCursor(0, 0);
      if (terminalPad.enterPressed()) {
        Serial.println(code);
        String code1 = db.getHouse1Code();
        String code2 = db.getHouse2Code();
        int checkPass = handleCheckPassword(code, code1, code2);
        if(checkPass != 0){
          Serial.println("You have entered the correct");
          Serial.println(checkPass);
        } else {
          Serial.println("Wrong passwords");
        }
        code = "";
      } else if (terminalPad.resetPassPressed()) {
        code = "";
      } else {
        code += keyFromUser;
//        lcd.print(code);
        Serial.println(keyFromUser);
      }
    }
  } else {
    lcd.setCursor(0,0);
  }
}

int handleCheckPassword(String USER_CODE, String HOUSE_1, String HOUSE_2){
  if(USER_CODE == HOUSE_1)
    return 1;
  else if (USER_CODE == HOUSE_2)
    return 2;
  else
    return 0;
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
