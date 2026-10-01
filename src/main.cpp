#include <iostream>
#include <ostream>

#include "proc-reader.h"
#include "gpu-reader.h"
#include "motherboard-reader.h"
#include "process-reader.h"
#include "ram-reader.h"

int main()
{
    ProcReader proc;
    MotherboardReader motherboard;
    ProcessReader processes;
    RamReader ram;

    //GPU
    std::cout<<"GPU: "<<std::endl;
    if (GpuReader* gpuReader = GpuFactory::createGpuReader()) {
        gpuReader->readMaxTemp();
        gpuReader->readCurrTemp();

        gpuReader->printModel();
        gpuReader->printMaxTemp();
        gpuReader->printCurrTemp();
    }
    else {
        std::cerr<<"Err: Couldn't find GPU!"<<std::endl;
    }

    //PROCESSOR
    std::cout<<std::endl;
    std::cout<<"CPU: "<<std::endl;
    proc.readModel();
    proc.printModel();

    //RAM
    std::cout<<"RAM: "<<std::endl;
    ram.readModel();
    ram.printModel();

    //MOTHERBOARD
    std::cout<<"MOTHERBOARD: "<<std::endl;
    motherboard.readModel();
    motherboard.printModel();

    //PROCESSES:
    std::cout<<"PROCESSES: "<<std::endl;
    processes.readProcesses();
    processes.printProcesses();

    return 0;
}