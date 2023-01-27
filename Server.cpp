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
using namespace std;

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
    

    //SocketIO socketIO(sock);
    
   // CLI myCLI(&socketIO);

    
    // Infinity loop for never end listening.
    while (true) {


        printf("Accept client connection\n");
        // Accept client connection.
        int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);
        if (client_sock < 0) {
            cout << "error accepting client" << endl;
            exit(1);
        }
        printf("yay! new client!\n");
        SocketIO sio(client_sock);
        CLI cli(&sio);
        cli.start();
    }
    // If true ever been false...
    close(sock);
    return 0;
}