//
// Created by daan on 26-5-2026.
//

#ifndef IMPEDANCE_TESTING_IdleState_HPP
#define IMPEDANCE_TESTING_IdleState_HPP

#include "core/State.hpp"

class IdleState : public State {
public:
    void enter() override;

    void update() override;
};


#endif //IMPEDANCE_TESTING_IdleState_HPP
