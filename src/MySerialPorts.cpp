#include "MySerialPorts.hpp"
#include <iostream>


void MySerialPorts::init() noexcept{
    chosen_port = -1;
    open_port = -1;
    confirm = true;
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

void MySerialPorts::send_data(Rotors& rotors){
    if(chosen_port != -1){
        if(open_port != chosen_port){
            close_open_port();
            sp_open(port_list[chosen_port], SP_MODE_WRITE);
            open_port = chosen_port;
            sp_set_baudrate(port_list[open_port], 9600);
            rotors.setIdle();
        }

        auto port = port_list[open_port];

        if(sp_output_waiting(port) == 0){

            // const char signal = 'A';
            // sp_nonblocking_write(port, &signal, 1);
            
            unsigned char data[4];
            for(int i = 0; i < (int)sizeof(data); i++)
                data[i] = (unsigned char)(rotors[i] * 255);
            sp_nonblocking_write(port, data, 4);
            // std::cout <<
            //     "s1: " << static_cast<int>(data[0]) << " , " <<
            //     "s2: " << static_cast<int>(data[1]) << " , " <<
            //     "s3: " << static_cast<int>(data[2]) << " , " <<
            //     "s4: " << static_cast<int>(data[3]) << std::endl;
            // confirm = false;
        }

        // if(!confirm){
        //     unsigned char data[4];
        //     sp_nonblocking_read(port, data, 1);
        //     if(static_cast<char>(data[0]) == 'B'){
        //         sp_nonblocking_read(port, data, 4);
        //         std::cout <<
        //             "r1: " << static_cast<int>(data[0]) << " , " <<
        //             "r2: " << static_cast<int>(data[1]) << " , " <<
        //             "r3: " << static_cast<int>(data[2]) << " , " <<
        //             "r4: " << static_cast<int>(data[3]) << std::endl;
        //         confirm = true;
        //     }
        // }
        
    }
}

void MySerialPorts::close_open_port(){
    if(open_port != -1) sp_close(port_list[open_port]);
}
