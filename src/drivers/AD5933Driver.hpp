//
// Created by daan on 26-5-2026.
//

#ifndef IMPEDANCE_TESTING_AD5933DRIVER_HPP
#define IMPEDANCE_TESTING_AD5933DRIVER_HPP

#include <AD5933.h>

class AD5933Driver {
public:
    // Config
    static constexpr int START_FREQ = 10000;
    static constexpr int FREQ_INCR = 1800;
    static constexpr int NUM_INCR = 50;
    static constexpr int REF_RESIST = 2000;

private:
    AD5933 ad5933;

    int currentFrequency = 0;
    double gainFactor = 0.0;

    double gain[NUM_INCR+1];
    int phase[NUM_INCR+1];

public:
    bool begin();

    bool calibrate();

    bool readPoint(
        int index,
        float& frequency,
        int& real,
        int& imaginary,
        float& magnitude,
        float& impedance
    );

    bool runSweep();

    void frequencySweepRaw();
};

extern AD5933Driver ad5933driver;


#endif //IMPEDANCE_TESTING_AD5933DRIVER_HPP
