#include <iostream>
#include <ostream>

#include "console.h"
#include "proc-reader.h"
#include "gpu-reader.h"
#include "motherboard-reader.h"
#include "process-reader.h"
#include "processes-manager.h"
#include "ram-reader.h"

int main()
{
    //INTERFACE
    std::cout<<
        "Welcome to linux system monitor app made by Olaf Karabin and Weronika Pucuła.\n"
    <<std::endl;

    bool running = true;
    while (running){
        std::cout<<
            "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
            "Please specify what you wish to do:\n"
            "\t1-Display hardware (model, temperature, memory)\n"
            "\t2-Display running processes\n"
            "\t3-Enter process management mode\n"
            "\t4-Exit the system manager\n"
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

            case '3':{
                while (true){
                    Console::clearScreen();

                    ProcessReader processes;

                    processes.readProcesses();
                    processes.printProcesses();

                    std::cout<< "\nEntering process management mode:\n"
                                "To modify a process' state, please enter the action character and the process PID.\n"
                                "Currently supported actions are:\n"
                                "\tE - send a SIGTERM signal (a polite termination request)\n"
                                "\tK - send a SIGKILL signal (forceful shutdown)\n"
                                "\tS - send a SIGSTOP signal (stop a process, putting it to sleep)\n"
                                "\tC - send a SIGCONT signal (wake up a sleeping process)\n"
                                "If you want to quit this mode, type \"Q\".\n"
                    <<std::endl;

                    char action;
                    pid_t pid;

                    std::cout<<"\nAction: ";
                    std::cin>>action;
                    if (action == 'Q' || action == 'q'){
                        Console::clearScreen();
                        break;
                    }
                    std::cout<<"Process ID (PID): ";
                    std::cin>>pid;
                    if (!ProcessesManager::changeState(action, pid)){
                        std::cerr<<"\nFailed to change the state of the process.\n"<<std::endl;
                    }
                    else{
                        std::cout<<"\nSuccessfully changed the state of the process.\n"<<std::endl;
                    }
                }
                break;
            }

            case '4':{
                running = false;
                std::cout<<"Bye!"<<std::endl;
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