//
// Created by yonia on 24/01/2023.
//

#ifndef EX4_SOCKETIO_H
#define EX4_SOCKETIO_H
#include "DefaultIO.h"

/**
 * This class represents IO system with the client side.
*/
class SocketIO: public DefaultIO {
private:
    int client_sock;
    char buffer[4096] = "";
    int expected_data_len = sizeof(buffer);
public:
    explicit SocketIO (int sock);
    string read() override;
    void write(string line) override;
};


#endif //EX4_SOCKETIO_H
