#include "Rotors.hpp"
#include <stdexcept>

Rotors::Rotors() noexcept{
    setIdle();
}

float& Rotors::operator[] (int index){
    return rotors[index];
}

void Rotors::setIdle() noexcept{
    r1 = 0.f;
    r2 = 0.f;
    r3 = 0.f;
    r4 = 0.f;
    master = 0.f;
    master_shadow = 0.f;
}

void Rotors::process() noexcept{

    if(master != master_shadow){

        float diff = master - master_shadow;
        master_shadow = master;
        
        const float r1_temp = r1 + diff;
        const float r2_temp = r2 + diff;
        const float r3_temp = r3 + diff;
        const float r4_temp = r4 + diff;

        const bool valid_configuration =
            r1_temp >= 0 && r1_temp <= 1.f &&
            r2_temp >= 0 && r2_temp <= 1.f &&
            r3_temp >= 0 && r3_temp <= 1.f &&
            r4_temp >= 0 && r4_temp <= 1.f;
        
        if(valid_configuration){
            r1 = r1_temp;
            r2 = r2_temp;
            r3 = r3_temp;
            r4 = r4_temp;
        }
    }
}
