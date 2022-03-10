#pragma once
#include <ESP32Servo.h>

enum Gate_state {
  GATE_CLOSED = 8,
  GATE_OPENED = 90
};

class Gate {
  private:
    Servo *servo;
    const int servoPin = 2;
    bool openGate;
  public:
    Gate(){
      servo = new Servo();
    }

    void setupServo() {
      // Allow allocation of all timers
      ESP32PWM::allocateTimer(0);
      ESP32PWM::allocateTimer(1);
      ESP32PWM::allocateTimer(2);
      ESP32PWM::allocateTimer(3);
      servo->setPeriodHertz(50);    // standard 50 hz servo
      servo->attach(servoPin, 500, 2400); // attaches the servo on pin 18 to the servo object
      servo->write(GATE_CLOSED);
    }

    void open(){
      servo->write(GATE_OPENED);
      delay(6000);
      servo->write(GATE_CLOSED);
    }
};
