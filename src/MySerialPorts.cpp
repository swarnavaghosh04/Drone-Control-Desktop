#include "MySerialPorts.hpp"
#include <iostream>


void MySerialPorts::init() noexcept{
    chosen_port = -1;
    open_port = -1;
    enum sp_return result = sp_list_ports(&port_list);
    if(result != SP_OK) std::cout << "sp_list_ports() failed!" << std::endl;
}

void MySerialPorts::end() noexcept{
    sp_free_port_list(port_list);
    close_open_port();
}

MySerialPorts::MySerialPorts() noexcept{
    init();
}

MySerialPorts::~MySerialPorts() noexcept{
    end();
}

void MySerialPorts::refresh_port_list(){
    end();
    init();
}

void MySerialPorts::send_data(float rotors[]){
    if(chosen_port != -1){
        if(open_port != chosen_port){
            close_open_port();
            sp_open(port_list[chosen_port], SP_MODE_WRITE);
            open_port = chosen_port;
            sp_set_baudrate(port_list[open_port], 9600);
            rotors[0] = 0.f;
            rotors[1] = 0.f;
            rotors[2] = 0.f;
            rotors[3] = 0.f;
        }

        auto port = port_list[open_port];
        if(sp_output_waiting(port) == 0){
            unsigned char data = (unsigned char)(rotors[3] * 255);
            sp_nonblocking_write(port, &data, sizeof(data));
        }
        
    }
}

void MySerialPorts::close_open_port(){
    if(open_port != -1) sp_close(port_list[open_port]);
}
