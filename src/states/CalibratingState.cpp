//
// Created by daan on 26-5-2026.
//

#include "Arduino.h"

#include "CalibratingState.hpp"

#include "ui/UI.hpp"
#include "drivers/AD5933Driver.hpp"
#include "protocol/SerialProtocol.hpp"
#include "core/StateMachine.hpp"

void CalibratingState::enter() {
    UI::setRGB(true, false, false); // Red

    UI::setCalibrateLED(true);

    SerialProtocol::log("CALIBRATION_START");

    bool success = ad5933driver.calibrate();

    UI::setCalibrateLED(false);

    if (success) {
        SerialProtocol::log("CALIBRATION_DONE");
        changeState(StateID::READY);
    } else {
        SerialProtocol::log("CALIBRATION_FAILED");
        changeState(StateID::IDLE);
    }
}

void CalibratingState::update() {}