#ifndef MYSERIALPORTS__H
#define MYSERIALPORTS__H

#include <libserialport.h>
#include "Rotors.hpp"

struct MySerialPorts{

    sp_port** port_list;
    int chosen_port;
    int open_port;
    bool confirm;

    MySerialPorts() noexcept;
    ~MySerialPorts() noexcept;
    void init() noexcept;
    void end() noexcept;
    void refresh_port_list();
    void send_data(Rotors& rotors);
    void close_open_port();

};

#endif