#ifndef ROTORS__H
#define ROTORS__H

struct Rotors{


    union{
        struct{float r1, r2, r3, r4;};
        float rotors[4];
    };
    float master;
    float master_shadow;

    Rotors() noexcept;
    float& operator[](int index);
    void setIdle() noexcept;
    void process() noexcept;
};

#endif