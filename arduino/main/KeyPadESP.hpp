#pragma once
#include <Keypad.h>
#define ROW_NUM     4 // four rows
#define COLUMN_NUM  4 // three columns

enum Terminal_State {
  PASS_ENTER,
  PASS_RESET,
  PASS_WRITE,
  PASS_PROGRESS
};

class KeyPadESP {
  private:
      Keypad *terminalPad;
      Terminal_State state;
      char keys[ROW_NUM][COLUMN_NUM] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}
      };
  public:
    KeyPadESP(byte *pin_rows, byte *pin_column) {
      this->terminalPad = new Keypad( makeKeymap(this->keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );
      this->state = PASS_WRITE;
    }
    ~KeyPadESP(){
      delete terminalPad;
    }

    char readKey(){
      return terminalPad->getKey();
      this->state = PASS_WRITE;
    }

    bool enterPressed(char pressed){
      this->state = PASS_ENTER;
      return pressed == '#';
    }

    bool resetPassPressed(char pressed){
      this->state = PASS_RESET;
      return pressed == '*';
    }
    
};
