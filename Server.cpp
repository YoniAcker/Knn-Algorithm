//
// Created by yonia on 29/12/2022.
//

#include "DB.h"
#include "AlgorithmKnn.h"
#include "InputManager.h"
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "CLI.h"
#include "SocketIO.h"
#include <thread>
using namespace std;

void handle_client(int client_sock) {
        SocketIO sio(client_sock);
        CLI cli(&sio);
        cli.start();
    close(client_sock);
}

/***
 int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;
    bind(server_fd, (sockaddr*) &server_address, sizeof(server_address));
    listen(server_fd, 5);
    while (true) {
        sockaddr_in client_address;
        socklen_t client_len = sizeof(client_address);
        int client_fd = accept(server_fd, (sockaddr*) &client_address, &client_len);
        thread client_thread(handle_client, client_fd);
        client_thread.detach();
    }
    return 0;
}
*/


/**
 * The main function of the server. Get the file name to make the db from the command line,
   among with the port number to listen at. The server get vectors, among with information
   such as the distance function to use and the 'k' for the algorithm, and classified them.
 * @param argc the number of arguments that been given from the command line.
 * @param argv command line arguments.
*/
int main(int argc, char *argv[]) {
    // Make the db.

   // DB db(argv[1]);
    // Make the algorithm.
    // AlgorithmKnn algorithmKnn(&db);

    // Check if the port number is valid.
    int portNum;
    try {
        portNum = stoi(argv[1]);
    }

    catch (invalid_argument& ia) {
        cout << "Invalid port number" << endl;
        exit(1);
    }
    catch (out_of_range ofRange) {
        cout << "Invalid port number" << endl;
        exit(1);
    }
    const int server_port = portNum;
    // Make the socket.
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        cout << "error creating socket" << endl;
        exit(1);
    }

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);
    
    
    // Bind the socket to the port.
    if (bind(sock, (struct sockaddr*) &sin, sizeof(sin)) < 0){
        cout << "error binding socket" << endl;
        exit(1);
    }

    printf("hi! you are in the server\n");
    printf("wait, listen in the port:)\n");
    // Make the server listen in the port.
    if (listen(sock, 5) < 0) {
        cout << "error listening to a socket" << endl;
        exit(1);
    }

    printf("lissening to the port sucssesfuly! :)\n");
    
    
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    

    while (true) {
        sockaddr_in client_address;
        socklen_t client_len = sizeof(client_address);
        int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);
        thread client_thread(handle_client, client_sock);
        client_thread.detach();
    }


    // If true ever been false...
    close(sock);
    return 0;
}