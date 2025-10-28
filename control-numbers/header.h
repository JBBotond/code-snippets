//
// Created by boti on 10/28/25.
//

#ifndef CODE_SNIPPETS_HEADER_H
#define CODE_SNIPPETS_HEADER_H
//own defines
#define COMMAND_FORWARD 0
#define COMMAND_BACKWARD 1
#define COMMAND_RIGHT 2
#define COMMAND_LEFT 3
#define COMMAND_BRAKE 4
#define COMMAND_CHANGE_MODE 5



void controlNumbers(int n, int &command, int &value) {
    command = -1;
    value = -1;
    if (n >= 1 && n <= 100) {
        command = COMMAND_FORWARD;
        value = n;
    } else if (n >= 101 && n <= 200) {
        command = COMMAND_BACKWARD;
        value = n - 100;
    } else if (n >= 201 && n <= 300) {
        command = COMMAND_RIGHT;
        value = n - 200;
    } else if (n >= 301 && n <= 400) {
        command = COMMAND_LEFT;
        value = n - 300;
    } else if (n == 401) {
        command = COMMAND_BRAKE;
        value = 0;
    } else if (n > 401 && n <= 10000) {
        command = COMMAND_CHANGE_MODE;
        value = 0;
    }
}

#endif //CODE_SNIPPETS_HEADER_H