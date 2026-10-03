#include <iostream>
#include <ostream>

#include "console.h"
#include "proc-reader.h"
#include "gpu-reader.h"
#include "motherboard-reader.h"
#include "process-reader.h"
#include "ram-reader.h"

int main()
{
    //INTERFACE
    std::cout<<
        "Welcome to linux system monitor app made by Olaf Karabin and Weronika Pucuła.\n"
    <<std::endl;

    while (true){
        std::cout<<
            "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
            "Please specify what you wish to do:\n"
            "\t1-Display hardware (model, temperature, memory)\n"
            "\t2-Display running processes\n"
        <<std::endl;

        char command;
        std::cin>>command;
        switch (command){
            case '1':{
                Console::clearScreen();
                std::cout<<"Currently displaying hardware:"<<std::endl;

                /*
                 * Reading the computer's hardware.
                 */

                ProcReader proc;
                proc.readModel();

                MotherboardReader motherboard;
                motherboard.readModel();

                RamReader ram;
                ram.readModel();

                GpuReader* gpuReader = GpuFactory::createGpuReader();
                if (gpuReader){
                    gpuReader->readMaxTemp();
                }
                else {
                    std::cerr<<"Err: Couldn't find GPU!"<<std::endl;
                }

                std::cout<<std::endl;

                /*
                 * Printing the read hardware.
                 */

                std::cout<<"CPU: "<<std::endl;
                proc.printModel();

                if (gpuReader){
                    std::cout<<"GPU: "<<std::endl;
                    gpuReader->readCurrTemp();
                    gpuReader->printModel();
                    gpuReader->printMaxTemp();
                    gpuReader->printCurrTemp();
                }

                std::cout<<"RAM: "<<std::endl;
                ram.printModel();

                std::cout<<"MOTHERBOARD: "<<std::endl;
                motherboard.printModel();

                break;
            }

            case '2':{
                Console::clearScreen();
                std::cout<<"Displaying running processes:"<<std::endl;

                ProcessReader processes;
                processes.readProcesses();
                processes.printProcesses();

                break;
            }

            default:{
                Console::clearScreen();
                std::cerr<<"Unknown command. Try again."<<std::endl;
                break;
            }
        }
    }

    return 0;
}