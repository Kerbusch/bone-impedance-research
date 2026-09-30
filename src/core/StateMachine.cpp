//
// Created by daan on 26-5-2026.
//

#include "StateMachine.hpp"

#include "states/IdleState.hpp"
#include "states/CalibratingState.hpp"
#include "states/ReadyState.hpp"
#include "states/SweepingState.hpp"

State* currentState = nullptr;

// State Objects
IdleState idleState;
CalibratingState calibrationState;
ReadyState readyState;
SweepingState sweepingState;

// Initialize
void initializeStates() {
    currentState = &idleState;
}

// change state
void changeState(StateID id) {
    switch (id) {
        case StateID::IDLE:
            currentState = &idleState;
            break;

        case StateID::CALIBRATING:
            currentState = &calibrationState;
            break;

        case StateID::READY:
            currentState = &readyState;
            break;

        case StateID::SWEEPING:
            currentState = &sweepingState;
            break;
    }

    currentState->enter();
}
