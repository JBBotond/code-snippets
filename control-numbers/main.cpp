//
// Created by boti on 10/28/25.
//
#include <iostream>
#include "header.h"

int main() {
    int number;
    std::cin >> number;
    int command = 0, value = 0;
    controlNumbers(number, command, value);
    std::cout << "Command num: " << command <<
        " Value num: " << value;
}