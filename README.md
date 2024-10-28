# Bus Tracking System

**********************************************************************************
## Project Overview

The **Bus Tracking System** is a console-based application designed to manage bus information, enabling users to add, search, delete, and display bus details in an organized way. Developed collaboratively by Iman, Lisa, Chima, Razeen, and Edwin, this project implements a modular structure with separate files for core functionalities, unit tests, and compilation settings.

**********************************************************************************
## File Structure

- **main.cpp**: Contains the main function and provides the user interface for interacting with the Bus Tracking System.
- **bus.cpp**: Implements functions for bus operations, including adding, searching, deleting, and displaying bus information.
- **bus.h**: Header file defining the Bus class and function prototypes used in `bus.cpp`.
- **test.cpp**: Contains unit tests for verifying various functionalities within the Bus Tracking System.
- **Makefile**: Configuration file for compiling the source code and generating executable files.

**********************************************************************************
## Installation

1. **Clone the Repository**
   - Clone the repository from Bitbucket (Note: The repository is read-only; direct modifications are restricted).
   - Command: `git clone <Bitbucket-link>`

2. **Navigate to the Project Directory**
   - Move to the project directory in your terminal.
   - Command: `cd BusTrackingSystem`

3. **Compile the Project**
   - Use the `make` command to compile the source code and create the executable files.
   - Command: `make`

4. **Run the Program**
   - Execute the main application to interact with the Bus Tracking System.
   - Command: `./bustracking`

**********************************************************************************
## Usage

Upon running the main executable (`./bustracking`), users are presented with a menu offering several options:

- **Add a Bus**: Enter details to add a new bus to the system.
- **Search for a Bus**: Look up a specific bus by entering its ID.
- **Display Available Buses**: View all buses currently stored in the system.
- **Delete Bus Information**: Remove a bus from the system.

To verify functionality, unit tests are included and can be run with the `./testbus` command:
- Command: `./testbus`

The system will display test results, ensuring that core features are functioning as expected.

**********************************************************************************
## Credits

This project was developed by a team including <a href="https://github.com/Imaan-Hayfaa">Iman<a>, <a href="https://github.com/LGEaston">Lisa<a>, <a href="https://github.com/Chima200057">Chima<a>, <a href="https://github.com/razeen46">Razeen<a>, and <a href="https://edwinshayo.com">Edwin<a>. Our collaborative efforts resulted in a robust, user-friendly Bus Tracking System designed for seamless user interaction and effective bus management.
