//
// Created by daan on 26-5-2026.
//

#ifndef IMPEDANCE_TESTING_STATE_HPP
#define IMPEDANCE_TESTING_STATE_HPP


class State{
public:
    virtual void enter() = 0;
    virtual void update() = 0;

    virtual ~State() {}
};


#endif //IMPEDANCE_TESTING_STATE_HPP
