# Linux System Monitor
Console based system monitor for Linux.

# Current Features
- Hardware enumeration
- Process display and management

# Installation 
Simply clone the repository and build the executable, preferably with CMake: 
```
git clone https://github.com/pepcooo/linux-sys-mon.git
cd linux-sys-mon
cmake -B build -S . && cmake --build build
```
After that, the ```linux-sys-mon``` executable will be in the ```build``` catalogue.

# Prerequisites
All you need to have installed is ```cmake``` in order to compile the monitor, version 3.3 or higher. 
> [!IMPORTANT]
> For hardware enumeration, you ought to run the tool with superuser privileges.
> Otherwise, you may not obtain all the information, as the program requires them to read all the hardware info from system files.
