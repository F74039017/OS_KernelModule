Process Kernel Module
===================

Operating System Homework 2<br>
Simple command line utility. Provide a kernel module (klsp.c) and user program (ulsp.c)<br><br>

kernel module can print all processes or show parent and child processes with given pid.<br>
User program can print the proc file named "lsproc".

Environment
-------------
- OS: Ubuntu 12.04.3 LTS
- Compiler: gcc version 4.6.3
- Kernel Version: 3.8.0-29-generic

Compile
------------
- Use `make`command.

Usage
-----------
*Kernel module* :
It provide two commands, showall and parentchild.<br>
showall => insmod klsp.ko command="showall"<br>
parentchild => insmod klsp.ko command="parentchild" pid="??"<br>

*User Program* :
./procprint
