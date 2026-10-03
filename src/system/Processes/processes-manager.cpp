#include "processes-manager.h"
#include <iostream>
#include <csignal>

bool ProcessesManager::changeState(char action,pid_t pid) {
    int signal = 0;
    switch (action) {
        case 'E':
        case 'e':
            signal = SIGTERM;
            break;
        case 'K':
        case 'k':
            signal = SIGKILL;
            break;
        case 'S':
        case 's':
            signal = SIGSTOP;
            break;
        case 'C':
        case 'c':
            signal = SIGCONT;
            break;
        default:
            return false;
    }
    return kill(pid, signal) == 0;
}
