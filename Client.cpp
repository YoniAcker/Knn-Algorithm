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
#include "Command.h"
#include "Update.h"
#include "SocketIO.h"
#include <fstream>
#include "DistanceFuncManager.h"
using namespace std;

int readFromServer(char* buffer, int sock) {
    int i;
    for (i = 0; i < 4096;i++){
        buffer[i] = 0;
        if (buffer[i] == '\0') {
            break;
        }
    }
    int read_bytes = recv(sock, buffer, 4096, 0);
    if (read_bytes == 0) {
        printf("there is no answer from the server\n");
        return 0;
    } else if (read_bytes < 0) {
        printf("problem in listening to the server :(\n");
        return 0;
    }
    return 1;
}

int sendToServer(char* buffer, int sock, string message) {
    int i;
    for (i = 0; i < 4096;i++){
        buffer[i] =0;
        if (buffer[i] == '\0') {
            break;
        }
    }
    strcpy(buffer, message.data());
    int sent_bytes = send(sock, buffer, 4096, 0);
    if (sent_bytes <= 0){
        printf("error in sending the vector :(");
        return 0;
    }
    return 1;
}
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
    char buffer[4096];
    bool flag = true;

    while (true) {
        // read the massage from the server:
        if (flag){
            if (!readFromServer(buffer, sock)) {
                break;
            }
        cout << buffer;
        }
        flag = true;
        string line;
        getline(cin, line);
        while (line.empty()){
            getline(cin, line);
        }
        if (!sendToServer(buffer, sock, line)) {
            break;
        }

        if (line == "1") {
            if (!readFromServer(buffer, sock)) {
                break;
            }
            cout << buffer;
            getline(cin, line);
            fstream readStream(line, ios::in);
            // Checks if the file is found.
            if (!readStream.is_open()) {
                cout << "Could not open the file" << endl;
                sendToServer(buffer, sock, "start");
                continue;
            }
            sendToServer(buffer, sock, "V");
            // Read the file line by line.
            while (getline(readStream, line)) {
                if (!sendToServer(buffer, sock, line)) {
                    break;
                }
                if (!readFromServer(buffer, sock)) {
                    break;
                }
                if (!strcmp(buffer, "invalid file\n")) {
                    break;
                }
            }
            if (!strcmp(buffer, "invalid file\n")) {
                break;
            }
            if (!sendToServer(buffer, sock, "Upload complete.")) {
                break;
            }
            readStream.close();
            if (!readFromServer(buffer, sock)) {
                break;
            }
            cout << buffer;
            if (!readFromServer(buffer, sock)) {
                break;
            }
            cout << buffer;
            getline(cin, line);
            fstream readStreamTest(line, ios::in);
            // Checks if the file is found.
            if (!readStreamTest.is_open()) {
                cout << "Could not open the file" << endl;
                sendToServer(buffer, sock, "start");
            }
            sendToServer(buffer, sock, "V");
            // Read the file line by line.
            while (getline(readStreamTest, line)) {
                if (!sendToServer(buffer, sock, line)) {
                    break;
                }
                if (!readFromServer(buffer, sock)) {
                    break;
                }
                if (!strcmp(buffer, "invalid file\n")) {
                    break;
                }
            }
            if (!sendToServer(buffer, sock, "Upload complete.")) {
                break;
            }
            readStreamTest.close();
            if (!readFromServer(buffer, sock)) {
                break;
            }
            cout << buffer;
            continue;
        }
        if (line == "2") {
            if (!readFromServer(buffer, sock)) {
                printf("error - the server didnt send \n");
                break;
            }
            cout << buffer;
            getline(cin, line);
            if (line.empty()){
                sendToServer(buffer, sock, line);
                continue;
            }

            sendToServer(buffer, sock, line);
            readFromServer(buffer, sock);
            cout<<"read now the buffer: "<<buffer;
            flag = true;
            if (strcmp(buffer, "invalid value for metric") || strcmp(buffer, "invalid value for K")){
                cout<<"valid :)"<<endl;
                flag =false;
            }
            cout<<buffer;

            continue;
        }
        if (line == "3") {
            if (!readFromServer(buffer, sock)) {
                printf("error - the server didn't send \n");
                break;
            }
            cout << buffer;
            continue;
        }
        if (line == "4") {
            if (!readFromServer(buffer, sock)) {
                break;
            }
            if (strcmp(buffer, "V\n")) {
                cout << buffer;
                continue;
            }

            sendToServer(buffer, sock, "V");
            if (!readFromServer(buffer, sock)) {
                break;
            }
            while(strcmp(buffer, "Done.\n")) {
                cout << buffer;
                if(!sendToServer(buffer, sock, "V")) {
                    break;
                }
                if (!readFromServer(buffer, sock)) {
                    break;
                }
            }
            continue;
        }

        if (line == "5") {
            if (!readFromServer(buffer, sock)) {
                break;
            }
            if (strcmp(buffer, "V\n")) {
                cout << buffer;
                continue;
            }
            cout << "Please enter path to the file" << endl;
            getline(cin, line);
            ofstream writeStream(line);
            if (!writeStream.is_open()) {
                cout << "Could not open the file" << endl;
                sendToServer(buffer, sock, "start");
                continue;
            }
            sendToServer(buffer, sock, "V");
            if (!readFromServer(buffer, sock)) {
                break;
            }
            while(strcmp(buffer, "Done.\n")) {
                writeStream << buffer;
                if(!sendToServer(buffer, sock, "V")) {
                    break;
                }
                if (!readFromServer(buffer, sock)) {
                    break;
                }
            }
            writeStream.close();
            continue;
        }
        if (line == "8") {
            break;
        }
    }
    close(sock);
    return 0;
}
