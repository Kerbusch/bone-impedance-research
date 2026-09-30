//
// Created by daan on 26-5-2026.
//

#ifndef IMPEDANCE_TESTING_CALIBRATINGSTATE_HPP
#define IMPEDANCE_TESTING_CALIBRATINGSTATE_HPP

#include "core/State.hpp"

class CalibratingState : public State {
private:
    unsigned long startTime = 0;
    bool started  = false;

public:
    void enter() override;

    void update() override;
};


#endif //IMPEDANCE_TESTING_CALIBRATINGSTATE_HPP
