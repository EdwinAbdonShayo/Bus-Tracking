/*
    main.cpp
    Authors: M00909998, M00906834
    Created: 24/03/2024
    Updated: 21/04/2024
*/

#include "bus.h"

int main() {
    // Read bus data from CSV file when starting the program
    readBusDataFromCSV("buses.csv");

    int choice;
    char busNumber[20];

    do {
        std::cout << "\n\n\n\n\n\t\t\t\t\t*********************";
        std::cout << "\n\t\t\t\t\t*     MAIN MENU     *";
        std::cout << "\n\t\t\t\t\t*********************";
        std::cout << "\n\n\n\t\t\t\t\t1. Add Bus";
        std::cout << "\n\t\t\t\t\t2. Search";
        std::cout << "\n\t\t\t\t\t3. Buses Available";
        std::cout << "\n\t\t\t\t\t4. Delete Bus Information"; // New option
        std::cout << "\n\t\t\t\t\t5. Exit";
        std::cout << "\n\n\n\n\n\t\t\t\t\t Enter your choice: ";
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            std::cin.clear(); // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue; // Repeat the loop
        }
        if (choice < 1 || choice > 5) {
            std::cout << "Invalid choice. Please enter a number between 1 and 5." 
            << std::endl;
            continue; // Repeat the loop
        }
        switch (choice) {
        case 1:
            addBus();
            break;
        case 2:
            std::cout << "Enter Bus number: ";
            std::cin >> busNumber;
            searchBus(busNumber);
            break;
        case 3:
            showAvailableBuses();
            break;
        case 4:
            std::cout << "Enter Bus number to delete: ";
            std::cin >> busNumber;
            deleteBusInfo(busNumber); 
            break;
        case 5:
            exit(0);
        }
    } while (true);

    return 0;
}