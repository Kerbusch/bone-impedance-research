//
// Created by daan on 26-5-2026.
//

#ifndef IMPEDANCE_TESTING_READYSTATE_HPP
#define IMPEDANCE_TESTING_READYSTATE_HPP

#include "core/State.hpp"

class ReadyState : public State {
public:
    void enter() override;

    void update() override;
};


#endif //IMPEDANCE_TESTING_READYSTATE_HPP
