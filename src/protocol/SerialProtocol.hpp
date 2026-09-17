//
// Created by daan on 26-5-2026.
//

#ifndef IMPEDANCE_TESTING_SERIALPROTOCOL_HPP
#define IMPEDANCE_TESTING_SERIALPROTOCOL_HPP


class SerialProtocol{
public:
    static void begin();

    static void log(const char* msg);

    static void csvHeader();

    static void csvRow(
            float frequency,
            int real,
            int imaginary,
            float magnitude
    );
};


#endif //IMPEDANCE_TESTING_SERIALPROTOCOL_HPP
