#ifndef MYSERIALPORTS__H
#define MYSERIALPORTS__H

#include <libserialport.h>

struct MySerialPorts{

    sp_port** port_list;
    int chosen_port;
    int open_port;

    MySerialPorts() noexcept;
    ~MySerialPorts() noexcept;
    void init() noexcept;
    void end() noexcept;
    void refresh_port_list();
    void send_data(float rotors[]);
    void close_open_port();

};

#endif