//
// Created by daan on 26-5-2026.
//

#ifndef IMPEDANCE_TESTING_SWEEPINGSTATE_HPP
#define IMPEDANCE_TESTING_SWEEPINGSTATE_HPP

#include "core/State.hpp"


class SweepingState : public State {
private:
    int pointIndex = 0;
    unsigned long lastMeasurement = 0;

public:
    void enter() override;

    void update() override;
};


#endif //IMPEDANCE_TESTING_SWEEPINGSTATE_HPP
