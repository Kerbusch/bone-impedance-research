//
// Created by daan on 26-5-2026.
//

#include "SerialProtocol.hpp"
#include "Arduino.h"

#include "ui/UI.hpp"

void SerialProtocol::begin() {
    Serial.begin(115200);
//    while (!Serial) {
//        // Not blocking
//    }

    UI::serialConnected();

    Serial.println("SYSTEM_READY");
}

void SerialProtocol::log(const char* msg) {
    Serial.println(msg);
}

void SerialProtocol::csvHeader() {
    Serial.println("frequency,real,imaginary,magnitude");
}

void SerialProtocol::csvRow(float frequency, int real, int imaginary, float magnitude) {
    Serial.print(frequency);
    Serial.print(",");

    Serial.print(real);
    Serial.print(",");

    Serial.print(imaginary);
    Serial.print(",");

    Serial.println(magnitude);
}
