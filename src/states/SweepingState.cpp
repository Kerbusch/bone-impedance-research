//
// Created by daan on 26-5-2026.
//

#include "SweepingState.hpp"

#include "Arduino.h"

#include "core/StateMachine.hpp"
#include "drivers/AD5933Driver.hpp"
#include "ui/UI.hpp"
#include "protocol/SerialProtocol.hpp"


void SweepingState::enter() {
    UI::setRGB(true, false, false); // Red

    pointIndex = 0;

    SerialProtocol::log("SWEEP_START");
    SerialProtocol::csvHeader();

    lastMeasurement = millis();
}
void SweepingState::update() {
    if (pointIndex > AD5933Driver::NUM_INCR) {

        SerialProtocol::log("SWEEP_DONE");

        changeState(StateID::READY);

        return;
    }

    float frequency;
    int real;
    int imaginary;
    float magnitude;
    float impedance;

    bool success = ad5933driver.readPoint(
            pointIndex,
            frequency,
            real,
            imaginary,
            magnitude,
            impedance
    );

    if (!success) {

        SerialProtocol::log("POINT_READ_FAILED");

        changeState(StateID::READY);

        return;
    }

    // CSV STREAMING
    Serial.print(frequency);
    Serial.print(",");

    Serial.print(real);
    Serial.print(",");

    Serial.print(imaginary);
    Serial.print(",");

    Serial.print(magnitude);
    Serial.print(",");

    Serial.println(impedance);

    pointIndex++;

    delay(50);
}
