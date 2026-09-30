//
// Created by daan on 26-5-2026.
//

#include "UI.hpp"
#include "Arduino.h"

// Pin definitions
#define SerialLED          2
#define CalibrateLED       3
#define StatusLED_RED      4
#define StatusLED_GREEN    5
#define StatusLED_BLUE     6

#define CalibrateButton    7
#define SweepButton        8

// Initialize the UI
void UI::begin() {
    // Set pin modes for buttons
    pinMode(CalibrateButton, INPUT_PULLUP);
    pinMode(SweepButton, INPUT_PULLUP);

    // Set pin modes for LEDs
    pinMode(SerialLED, OUTPUT);
    pinMode(CalibrateLED, OUTPUT);

    pinMode(StatusLED_RED, OUTPUT);
    pinMode(StatusLED_GREEN, OUTPUT);
    pinMode(StatusLED_BLUE, OUTPUT);

    digitalWrite(SerialLED, LOW);

    setRGB(false, false, false);
}

void UI::serialConnected(){
    digitalWrite(SerialLED, HIGH);
}

void UI::setRGB(bool red, bool green, bool blue) {
    digitalWrite(StatusLED_RED, red ? HIGH : LOW);
    digitalWrite(StatusLED_GREEN, green ? HIGH : LOW);
    digitalWrite(StatusLED_BLUE, blue ? HIGH : LOW);
}

bool UI::calibratePressed() {
    static bool lastState = HIGH;

    bool current = digitalRead(CalibrateButton);

    bool pressed = (lastState == HIGH && current == LOW);

    lastState = current;

    return pressed;
}

bool UI::sweepPressed() {
    static bool lastState = HIGH;

    bool current = digitalRead(SweepButton);

    bool pressed = (lastState == HIGH && current == LOW);

    lastState = current;

    return pressed;
}

void UI::setCalibrateLED(bool state) {
    digitalWrite(CalibrateLED, state ? HIGH : LOW);
}