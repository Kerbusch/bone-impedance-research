//
// Created by daan on 26-5-2026.
//

#ifndef IMPEDANCE_TESTING_STATEMACHINE_HPP
#define IMPEDANCE_TESTING_STATEMACHINE_HPP

#include "State.hpp"

enum class StateID {
    IDLE,
    CALIBRATING,
    READY,
    SWEEPING
};

extern State* currentState;

void initializeStates();

void changeState(StateID id);


#endif //IMPEDANCE_TESTING_STATEMACHINE_HPP
