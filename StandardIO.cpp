//
// Created by yonia on 21/01/2023.
//

#include "StandardIO.h"
#include <iostream>

string StandardIO::read() {
    string line;
    getline(cin, line);
    return line;
}

void StandardIO::write(string line) {
    cout << line << endl;
}
