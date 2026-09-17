#include <Arduino.h>
#include <Wire.h>

#include "protocol/SerialProtocol.hpp"
#include "ui/UI.hpp"
#include "core/StateMachine.hpp"
#include "drivers/AD5933Driver.hpp"

void setup() {
    SerialProtocol::begin();
    Wire.begin();
    UI::begin();
    ad5933driver.begin();
    initializeStates();
    changeState(StateID::IDLE);
}

void loop() {
    if (currentState != nullptr) {
        currentState->update();
    }
}