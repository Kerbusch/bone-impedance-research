//
// Created by daan on 26-5-2026.
//

#include "AD5933Driver.hpp"
#include <Arduino.h>
#include <Wire.h>

#include <AD5933.h>

AD5933Driver ad5933driver;

bool AD5933Driver::begin() {
    Wire.begin(); // Start I2C communication if not already started

    // reset
    if (!AD5933::reset()) {
        return false;
    }

    // configure sweep
    if (!AD5933::setInternalClock(true)) {
        return false;
    }

    if (!AD5933::setStartFrequency(START_FREQ)) {
        return false;
    }

    if (!AD5933::setIncrementFrequency(FREQ_INCR)) {
        return false;
    }

    if (!AD5933::setNumberIncrements(NUM_INCR)) {
        return false;
    }

    if (!AD5933::setPGAGain(PGA_GAIN_X1)) {
        return false;
    }

//    if (!ad5933.setRange(CTRL_OUTPUT_RANGE_4)) {
//        return false;
//    }

    if (!ad5933.setSettlingCycles(200)) {
        return false;
    }

    currentFrequency = START_FREQ;

    // Return true if all initialization steps were successful
    return true;

}

bool AD5933Driver::calibrate(){
//    double gain[NUM_INCR + 1];
//    int phase[NUM_INCR + 1];
//
//    bool success = AD5933::calibrate(
//        gain,
//        phase,
//        REF_RESIST,
//        NUM_INCR + 1
//    );
//
//    if (!success) {
//        return false;
//    }
//
//    gainFactor = gain[0];
//
//    return true;

    if (AD5933::calibrate(gain, phase, REF_RESIST, NUM_INCR+1))
        return true;
    // If calibration fails, return false
    return false;

}

bool AD5933Driver::readPoint(
        int index,
        float& frequency,
        int& real,
        int& imaginary,
        float& magnitude,
        float& impedance
) {

    static bool initialized = false;

    // ============================================
    // INITIALIZE SWEEP
    // ============================================

    if (!initialized) {

        if (!(AD5933::setPowerMode(POWER_STANDBY) &&
              AD5933::setControlMode(CTRL_INIT_START_FREQ) &&
              AD5933::setControlMode(CTRL_START_FREQ_SWEEP))) {

            return false;
        }

        initialized = true;
    }

    // ============================================
    // WAIT FOR VALID DATA
    // ============================================

    unsigned long timeout = millis();

    while (
            !(AD5933::readStatusRegister() & STATUS_DATA_VALID)
            ) {

        if (millis() - timeout > 1000) {

            Serial.println("DATA TIMEOUT");

            return false;
        }
    }

    // ============================================
    // READ COMPLEX DATA
    // ============================================

    if (!AD5933::getComplexData(
            &real,
            &imaginary
    )) {

        return false;
    }

    // ============================================
    // COMPUTE VALUES
    // ============================================

    frequency =
            START_FREQ +
            (index * FREQ_INCR);

    magnitude = sqrt(
            ((float)real * real) +
            ((float)imaginary * imaginary)
    );

    impedance =
            1.0 / (magnitude * gain[index]);

    // ============================================
    // ADVANCE SWEEP
    // ============================================

    if (index < NUM_INCR) {

        if (!AD5933::setControlMode(
                CTRL_INCREMENT_FREQ
        )) {

            return false;
        }

    } else {

        initialized = false;

        AD5933::setPowerMode(
                POWER_STANDBY
        );
    }

    return true;
}

//bool AD5933Driver::runSweep() {
//
//    int real;
//    int imag;
//
//    // Start sweep
//    if (!(AD5933::setPowerMode(POWER_STANDBY) &&
//          AD5933::setControlMode(CTRL_INIT_START_FREQ) &&
//          AD5933::setControlMode(CTRL_START_FREQ_SWEEP))) {
//
//        SerialProtocol::log("SWEEP_INIT_FAILED");
//
//        return false;
//    }
//
//    SerialProtocol::log("SWEEP_START");
//
//    Serial.println("frequency,real,imaginary,magnitude,impedance");
//
//    int i = 0;
//
//    while (
//            (AD5933::readStatusRegister() & STATUS_SWEEP_DONE)
//            != STATUS_SWEEP_DONE
//            ) {
//
//        // Wait for valid data
//        while (
//                !(AD5933::readStatusRegister() & STATUS_VALID_DATA)
//                ) {
//        }
//
//        // Read complex data
//        if (!AD5933::getComplexData(&real, &imag)) {
//
//            SerialProtocol::log("DATA_READ_FAILED");
//
//            return false;
//        }
//
//        float frequency =
//                START_FREQ +
//                (i * FREQ_INCR);
//
//        float magnitude = sqrt(
//                ((float)real * real) +
//                ((float)imag * imag)
//        );
//
//        float impedance =
//                1.0 / (magnitude * gain[i]);
//
//        // CSV output
//        Serial.print(frequency);
//        Serial.print(",");
//
//        Serial.print(real);
//        Serial.print(",");
//
//        Serial.print(imag);
//        Serial.print(",");
//
//        Serial.print(magnitude);
//        Serial.print(",");
//
//        Serial.println(impedance);
//
//        i++;
//
//        // Advance frequency
//        if (!AD5933::setControlMode(
//                CTRL_INCREMENT_FREQ
//        )) {
//
//            SerialProtocol::log("FREQ_INCREMENT_FAILED");
//
//            return false;
//        }
//    }
//
//    SerialProtocol::log("SWEEP_DONE");
//
//    AD5933::setPowerMode(POWER_STANDBY);
//
//    return true;
//}

//void AD5933Driver::frequencySweepRaw() {
//    // Create variables to hold the impedance data and track frequency
//    int real, imag, i = 0, cfreq = START_FREQ/1000;
//
//    // Initialize the frequency sweep
//    if (!(AD5933::setPowerMode(POWER_STANDBY) &&          // place in standby
//          AD5933::setControlMode(CTRL_INIT_START_FREQ) && // init start freq
//          AD5933::setControlMode(CTRL_START_FREQ_SWEEP))) // begin frequency sweep
//    {
//        Serial.println("Could not initialize frequency sweep...");
//    }
//
//    // Perform the actual sweep
//    while ((AD5933::readStatusRegister() & STATUS_SWEEP_DONE) != STATUS_SWEEP_DONE) {
//        // Get the frequency data for this frequency point
//        if (!AD5933::getComplexData(&real, &imag)) {
//            Serial.println("Could not get raw frequency data...");
//        }
//
//        // Print out the frequency data
//        Serial.print(cfreq);
//        Serial.print(": R=");
//        Serial.print(real);
//        Serial.print("/I=");
//        Serial.print(imag);
//
//        // Compute impedance
//        double magnitude = sqrt(pow(real, 2) + pow(imag, 2));
//        double impedance = 1/(magnitude*gain[i]);
//        Serial.print("  |Z|=");
//        Serial.println(impedance);
//
//        // Increment the frequency
//        i++;
//        cfreq += FREQ_INCR/1000;
//        AD5933::setControlMode(CTRL_INCREMENT_FREQ);
//    }
//
//    Serial.println("Frequency sweep complete!");
//
//    // Set AD5933 power mode to standby when finished
//    if (!AD5933::setPowerMode(POWER_STANDBY))
//        Serial.println("Could not set to standby...");
//}