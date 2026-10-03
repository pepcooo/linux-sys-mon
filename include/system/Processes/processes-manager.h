#pragma once
#include <cstdint>
#include <csignal>

class ProcessesManager {
    public:
    static bool changeState(char action, pid_t pid);

};

