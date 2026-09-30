//
// Created by daan on 26-5-2026.
//

#include "IdleState.hpp"

#include "core/StateMachine.hpp"
#include "ui/UI.hpp"
#include "protocol/SerialProtocol.hpp"

void IdleState::enter(){
    UI::setRGB(false, false, true); // Blue

    SerialProtocol::log("Connect calibration resistor.");
    SerialProtocol::log("Press calibration button.");
}

void IdleState::update() {
    if (UI::calibratePressed()) {
        changeState(StateID::CALIBRATING);
    }
}
