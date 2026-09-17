//
// Created by daan on 26-5-2026.
//

#ifndef IMPEDANCE_TESTING_UI_HPP
#define IMPEDANCE_TESTING_UI_HPP


class UI{
public:
    static void begin();

    static void serialConnected();

    static void setRGB(bool red, bool green, bool blue);

    static bool calibratePressed();

    static bool sweepPressed();

    static void setCalibrateLED(bool state);
};


#endif //IMPEDANCE_TESTING_UI_HPP
