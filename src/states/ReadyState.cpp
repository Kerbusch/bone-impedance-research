//
// Created by daan on 26-5-2026.
//

#include "ReadyState.hpp"

#include "ui/UI.hpp"
#include "protocol/SerialProtocol.hpp"
#include "core/StateMachine.hpp"

void ReadyState::enter() {
    UI::setRGB(false, true, false); // Green

    SerialProtocol::log("READY_FOR_SWEEP");
    SerialProtocol::log("Press sweep button.");
}

void ReadyState::update() {
    if (UI::sweepPressed()) {
        changeState(StateID::SWEEPING);
    }
}
