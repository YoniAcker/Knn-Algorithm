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
    DB db(argv[1]);
    // Make the algorithm.
    AlgorithmKnn algorithmKnn(&db);
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
    // Make the server listen in the port.
    if (listen(sock, 5) < 0) {
        cout << "error listening to a socket" << endl;
        exit(1);
    }
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    // Infinity loop for never end listening.
    while (true) {
        // Accept client connection.
        int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);
        if (client_sock < 0) {
            cout << "error accepting client" << endl;
            exit(1);
        }
        char buffer[4096];
        int expected_data_len = sizeof(buffer);
        string answer;
        int k;
        char distanceFunc[4];
        vector<double> input;
        // Get data from the client.
        int read_bytes = recv(client_sock, buffer, expected_data_len, 0);
        // Get new information until the client end the connection.
        while (read_bytes != 0) {
            if (read_bytes < 0) {
                cout << "error getting message" << endl;
                read_bytes = recv(client_sock, buffer, expected_data_len, 0);
                continue;
            }
            // Check if the input valid.
            try {
                input = InputManager::vectorCheck(buffer, distanceFunc, &k);
                answer = algorithmKnn.vectorClassification(input, distanceFunc, k);
            }
            catch (invalid_argument& ia) {
                answer = "invalid input\n";
            }
            // Copy the answer to char array.
            strncpy(buffer, answer.data(), answer.size());
            // Send the answer to the client.
            int sent_bytes = send(client_sock, buffer, read_bytes, 0);
            if (sent_bytes < 0) {
                cout << "error sending message" << endl;
            }
            read_bytes = recv(client_sock, buffer, expected_data_len, 0);
        }
        // Delete the input vector.
        vector<double>().swap(input);
    }
    // If true ever been false...
    close(sock);
    return 0;
}