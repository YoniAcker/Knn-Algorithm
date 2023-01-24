//
// Created by tallavi561 on 1/3/23.
//
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include "InputManager.h"
#include <iostream>
#include <sstream>
#include "DistanceFuncManager.h"
using namespace std;

/**
 * The main function of the client. Get the port number and the ip that the server listen at
   from the command line. Get vectors and other information from the user and send it to the
   server for him to classified them. Then, get the classification from the server and print
   it to the user.
 * @param argc the number of arguments that been given from the command line.
 * @param argv command line arguments.
*/
int main (int argc, char *argv[]) {
    // build the socket:
    const char* ip_address = argv[1];
    // Check if the port number is valid.
    int portNum;
    try {
        portNum = stoi(argv[2]);
    }
    catch (invalid_argument& ia) {
        cout << "Invalid port number" << endl;
        exit(1);
    }
    catch (out_of_range ofRange) {
        cout << "Invalid port number" << endl;
        exit(1);
    }
    const int port_no = portNum;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }
    // connecting to the server:
    struct sockaddr_in sin;
    // reset the sin to 0:
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address);
    sin.sin_port = htons(port_no);
    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        cout << "error connecting to server" << endl;
        exit(1);
    }
next_loop:
    while (true) {
        string line;
        getline(cin, line);
        if (line == "-1"){
            break;
        }
        char* data_addr = &line[0];
        int data_len = strlen(data_addr);
        int sent_bytes = send(sock, data_addr, data_len, 0);
        if (sent_bytes < 0) {
            cout << "invalid input" << endl;
            goto next_loop;
        }
            // read the massage from the server:
        char buffer[4096];
        int expected_data_len = sizeof(buffer);
        int read_bytes = recv(sock, buffer, expected_data_len, 0);
        if (read_bytes == 0) {
                // connection is closed
        } else if (read_bytes < 0) {
                // error
        } else {
            cout << buffer << endl;
        }
    }
    close(sock);
    return 0;
}