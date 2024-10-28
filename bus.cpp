/*
    bus.cpp
    Authors: M00909998, M00906834
    Created: 24/03/2024
    Updated: 21/04/2024
*/

#include "bus.h"

Bus busTable[TABLE_SIZE];

// Function prototypes
void sortBus(Bus* buses, int top, int bottom, int sortBy);
void showAvailableBuses();

// Merge function for MergeSort
void merge(Bus* buses, int top, int mid, int bottom, int sortBy) {
    int n1 = mid - top + 1;
    int n2 = bottom - mid;

    Bus* leftBuses = new Bus[n1];
    Bus* rightBuses = new Bus[n2];

    for (int i = 0; i < n1; i++)
        leftBuses[i] = buses[top + i];
    for (int j = 0; j < n2; j++)
        rightBuses[j] = buses[mid + 1 + j];

    int i = 0, j = 0, k = top;

    while (i < n1 && j < n2) {
        // Custom comparison logic based on the sortBy parameter
        switch (sortBy) {
            case 1: // Sort by BusNo
                if (compareByBusNo(leftBuses[i], rightBuses[j])) {
                    buses[k] = leftBuses[i];
                    i++;
                } else {
                    buses[k] = rightBuses[j];
                    j++;
                }
                break;
            case 2: // Sort by Departure Time
                if (compareByDepartureTime(leftBuses[i], rightBuses[j])) {
                    buses[k] = leftBuses[i];
                    i++;
                } else {
                    buses[k] = rightBuses[j];
                    j++;
                }
                break;
            case 3: // Sort by Arrival Time
                if (compareByArrivalTime(leftBuses[i], rightBuses[j])) {
                    buses[k] = leftBuses[i];
                    i++;
                } else {
                    buses[k] = rightBuses[j];
                    j++;
                }
                break;
        }
        k++;
    }

    while (i < n1) {
        buses[k] = leftBuses[i];
        i++;
        k++;
    }

    while (j < n2) {
        buses[k] = rightBuses[j];
        j++;
        k++;
    }
}

// MergeSort function
void sortBus(Bus* buses, int top, int bottom, int sortBy) {
    if (top < bottom) {
        int mid = top + (bottom - top) / 2;

        sortBus(buses, top, mid, sortBy);
        sortBus(buses, mid + 1, bottom, sortBy);

        merge(buses, top, mid, bottom, sortBy);
    }
}

// Custom comparator functions for sorting
bool compareByBusNo(const Bus& bus1, const Bus& bus2) {
    int busNum1 = atoi(bus1.busn);
    int busNum2 = atoi(bus2.busn);
    return busNum1 < busNum2;
}

bool compareByDepartureTime(const Bus& bus1, const Bus& bus2) {
    return strcmp(bus1.departure, bus2.departure) < 0;
}

bool compareByArrivalTime(const Bus& bus1, const Bus& bus2) {
    return strcmp(bus1.ETA, bus2.ETA) < 0;
}


// Function definitions...

void vline(char ch) {
    for (int i = 100; i > 0; i--)
        std::cout << ch;
}

int hashFunction(const char* busNumber) {
    int hash = 0;
    for (const char* c = busNumber; *c != '\0'; c++) {
        hash = (hash * 23 + *c) % TABLE_SIZE;
    }
    return hash;
}

// Function to validate time format (HH:MM)
bool validateTimeFormat(const char* timeStr) {
    // Check length
    if (strlen(timeStr) != 5)
        return false;

    // Check colon position
    if (timeStr[2] != ':')
        return false;

    // Check hour and minute components
    int hour = atoi(timeStr);
    int minute = atoi(timeStr + 3); // Skip the colon
    if (hour < 0 || hour > 23 || minute < 0 || minute > 59)
        return false;

    return true;
}

void addBus() {
    // Find the largest existing bus number
    int largestBusNumber = 0;
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (atoi(busTable[i].busn) > largestBusNumber) {
            largestBusNumber = atoi(busTable[i].busn);
        }
    }

    // Generate a new bus number by incrementing the largest bus number by 1
    char busNumber[20];
    sprintf(busNumber, "%d", largestBusNumber + 1);

    // Prompt user to input bus details
    char departure[20], driverName[50], currentStation[50], from[50], to[50],
    ETA[20];
    std::cout << "\nBus Departure time (HH:MM): ";
    std::cin.ignore();
    std::cin.getline(departure, sizeof(departure));

    // Validate departure time format
    if (!validateTimeFormat(departure)) {
        std::cout << "Error: Invalid departure time format. Please use HH:MM"
                    << "format." << std::endl;
        return;
    }

    std::cout << "\nEnter Bus Driver's name: ";
    std::cin.getline(driverName, sizeof(driverName));

    // Validate driver name (only alphabets and spaces allowed)
    bool validDriverName = true;
    for (int i = 0; driverName[i] != '\0'; i++) {
        if (!isalpha(driverName[i]) && !isspace(driverName[i])) {
            validDriverName = false;
            break;
        }
    }
    if (!validDriverName) {
        std::cout << "Error: Driver name should only contain alphabets and spaces." 
                    << std::endl;
        return;
    }

    std::cout << "\nCurrent Station: ";
    std::cin.getline(currentStation, sizeof(currentStation));

    std::cout << "\nFrom: ";
    std::cin.getline(from, sizeof(from));

    std::cout << "\nTo: ";
    std::cin.getline(to, sizeof(to));

    std::cout << "\nETA (Estimated Time of Arrival) (HH:MM): ";
    std::cin.getline(ETA, sizeof(ETA));

    // Validate ETA format
    if (!validateTimeFormat(ETA)) {
        std::cout << "Error: Invalid ETA format. Please use HH:MM format." 
                << std::endl;
        return;
    }
    
    // Create Bus object
    Bus bus(busNumber, departure, driverName, currentStation, from, to, ETA);

    // Insert bus information into hash table
    int index = hashFunction(busNumber);
    busTable[index] = bus;

    // Write to CSV
    writeBusDataToCSV("buses.csv");

    // Output the details of the added bus
    std::cout << "\nBus added successfully. Details:\n";
    vline('*');
    std::cout << "\nBus no: \t" << bus.busn
        << "\tDriver: \t" << bus.driver << "\nDeparture: \t"
        << bus.departure << "\tCurrent Station: \t" << bus.currentStation
        << "\tETA: \t" << bus.ETA << "\nFrom: \t" << bus.from
        << "\t\tTo: \t" << bus.to << "\n";
    vline('*');
    std::cout << std::endl;
}

void searchBus(const char* busNumber) {
    // Check if the bus exists in the hash table
    int index = hashFunction(busNumber);
    if (strcmp(busTable[index].busn, "") == 0) {
        std::cout << "Bus not found." << std::endl;
        return;
    }
    
    // Get reference to the bus object (const for read-only)
    const Bus& bus = busTable[index]; 

    // Display bus details
    vline('*');
    std::cout << "\n\tBus no: \t" << bus.busn 
        << "\t\tDriver: \t" << bus.driver << "\n\tDepature time: \t" 
        << bus.departure << "\t\t";

    // Read arrival time from CSV (assuming comma delimiter)
    std::stringstream ss(bus.ETA);
    std::string arrivalTime;
    if (getline(ss, arrivalTime, ',')) {
        std::cout << "Arrival time: \t" << arrivalTime;
    } else {
        // Departure time is empty, display a message
        std::cout << "Arrival time: \t Not Available";
    }

    // Truncate the "To" field if it's too long to avoid overlapping
    size_t maxToFieldLength = 15;
    std::string toField = bus.to;
    if (toField.length() > static_cast<size_t>(maxToFieldLength)) {
        toField = toField.substr(0, maxToFieldLength) + "...";
    }
    std::cout << "\n\tFrom: \t" << bus.from << "\t\tTo: \t" << toField << "\n";
    vline('*');
}

void showAvailableBuses() {
    // Prompt the user for sorting criteria
    std::cout << "How would you like to sort the available buses?" << std::endl;
    std::cout << "1. By BusNo" << std::endl;
    std::cout << "2. By Departure Time" << std::endl;
    std::cout << "3. By Arrival Time" << std::endl;
    std::cout << "Enter your choice: ";
    int choice;
    std::cin >> choice;

    // Array to store available buses
    Bus* availableBuses = new Bus[TABLE_SIZE]; 

    // Iterate through the hash table and collect all buses
    int count = 0;
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (strcmp(busTable[i].busn, "") != 0) {
            availableBuses[count++] = busTable[i];
        }
    }

    // Display available buses
    if (count == 0) {
        std::cout << "No available buses found." << std::endl;
        delete[] availableBuses;
        return;
    }

    // Sort the available buses based on user choice
    switch (choice) {
        case 1:
            sortBus(availableBuses, 0, count - 1, 1);
            break;
        case 2:
            sortBus(availableBuses, 0, count - 1, 2);
            break;
        case 3:
            sortBus(availableBuses, 0, count - 1, 3);
            break;
        default:
            std::cout << "Invalid choice. Sorting by BusNo." << std::endl;
            sortBus(availableBuses, 0, count - 1, 1);
    }

    std::cout << "\nAvailable Buses (sorted):\n" << std::endl;
    for (int i = 0; i < count; ++i) {
        vline('*');
        std::cout << "\nBus no: \t" << availableBuses[i].busn
            << "\tDriver: \t" << availableBuses[i].driver << "\nDeparture: \t"
            << availableBuses[i].departure << "\tCurrent Station: \t" 
            << availableBuses[i].currentStation
            << "\tETA: \t" << availableBuses[i].ETA << "\nFrom: \t" 
            << availableBuses[i].from
            << "\t\tTo: \t" << availableBuses[i].to << "\n";
        vline('*');
        std::cout << std::endl;
    }

    delete[] availableBuses;
}

void deleteBusInfo(const char* busNumber) {
    // Check if the bus exists in the hash table
    int index = hashFunction(busNumber);
    if (strcmp(busTable[index].busn, "") == 0) {
        std::cout << "Bus not found." << std::endl;
        return;
    }

    // Erase the bus from the hash table
    strcpy(busTable[index].busn, "");
    std::cout << "Bus information deleted successfully." << std::endl;

    // Write to CSV
    writeBusDataToCSV("buses.csv");
}

void readBusDataFromCSV(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    bool isFirstRow = true; // Flag to track if it's the first row
    while (getline(file, line)) {
        if (isFirstRow) {
            isFirstRow = false;
            continue;
        }
        std::stringstream ss(line);

        char busNumber[20], departure[20], driverName[50], currentStation[50], 
        from[50], to[50], ETA[20];
        // Read bus information from CSV format
        ss.getline(busNumber, sizeof(busNumber), ',');
        ss.getline(departure, sizeof(departure), ',');
        ss.getline(driverName, sizeof(driverName), ',');
        ss.getline(currentStation, sizeof(currentStation), ',');
        ss.getline(from, sizeof(from), ',');
        ss.getline(to, sizeof(to), ',');
        ss.getline(ETA, sizeof(ETA));
        Bus bus(busNumber, departure, driverName, currentStation, from, to, ETA);
        busTable[hashFunction(busNumber)] = bus;
    }
    file.close();
}

void writeBusDataToCSV(const char* filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error opening file: " << filename << std::endl;
        return;
    }
    
    // Write header
    file << "No.Bus,Departure,Driver,CurrentStation,From,To,ETA\n";

    // Iterate through hash table and write to CSV
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (strcmp(busTable[i].busn, "") != 0) {
            file << busTable[i].busn << "," << busTable[i].departure << "," 
            << busTable[i].driver << "," << busTable[i].currentStation << "," 
            << busTable[i].from << "," << busTable[i].to << "," << busTable[i].ETA 
            << std::endl;
        }
    }
    file.close();
}