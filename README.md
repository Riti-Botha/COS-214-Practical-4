# TaskForge Build and Execution Instructions

## Team members
* Riti Botha
* Deon Steenkamp
* Connor Human

## Docker Environment Setup

* The project builds and runs inside a Docker environment to avoid installing project-specific dependencies directly on the host machine like the system working on a Windows machine but not on Linux.
* Build the provided Docker image from your terminal:
`docker build -t taskforge-env .`
* Run and enter the interactive container:
`docker run -it --rm -v "$(pwd)":/workspace -w /workspace taskforge-env bash`

## 2. Compilation

* The project must be built using the provided Makefile.
* The Makefile is configured to compile the project using the `-std=c++11` flag.
* To compile the source code, run:
`make`


## 3. Program Execution

* The compilation process produces a final executable named `taskforge`.
* To execute the program, run:
`./taskforge`


## 4. Debugging and Memory Investigation

* The Docker environment provides GDB and Valgrind to investigate the system.
* To debug the executable using GDB, run:
`gdb ./taskforge`
* To verify that the implementation does not contain definitely-lost memory leaks, run the following Valgrind command:
`valgrind --leak-check=full --show-leak-kinds=all ./taskforge`
