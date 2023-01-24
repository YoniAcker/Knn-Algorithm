//
// Created by yonia on 24/01/2023.
//

#include "SocketIO.h"
#include <stdexcept>
#include <sys/socket.h>

/**
 * Constructor.
 @param sock the socket to the client.
*/
SocketIO::SocketIO(int sock) {
    client_sock = sock;
}

/**
 * Get line from the client.
 @return line of input.
*/
string SocketIO::read() {
    int read_bytes = recv(client_sock, buffer, expected_data_len, 0);
    if (read_bytes < 0) {
        throw invalid_argument("invalid input");
    }
    return buffer;
}

/**
 * Send line to the client.
 @param line to send.
*/
void SocketIO::write(string line) {
    line += "\n";
    int sent_bytes = send(client_sock, buffer, expected_data_len, 0);
    if (sent_bytes < 0) {
        throw invalid_argument("invalid input");
    }
}
