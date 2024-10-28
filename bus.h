/*
    bus.h
    Authors: M00909998, M00906834
    Created: 25/03/2024
    Updated: 21/04/2024
*/

#ifndef BUS_H
#define BUS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <limits>

const int TABLE_SIZE = 10000;

// Class to represent a bus
class Bus {
public:
    char busn[20];
    char departure[20];
    char driver[50];
    char currentStation[50];
    char from[50];
    char to[50];
    char ETA[20];

    // Default constructor
    Bus() {}

    // Constructor
    Bus(const char* busNum, const char* depart, const char* driverName, 
        const char* currentSta, const char* fromLoc, const char* toLoc,
        const char* eta) {
        strncpy(busn, busNum, sizeof(busn) - 1);
        strncpy(departure, depart, sizeof(departure) - 1);
        strncpy(driver, driverName, sizeof(driver) - 1);
        strncpy(currentStation, currentSta, sizeof(currentStation) - 1);
        strncpy(from, fromLoc, sizeof(from) - 1);
        strncpy(to, toLoc, sizeof(to) - 1);
        strncpy(ETA, eta, sizeof(ETA) - 1);
    }
};

// Hash table to store bus information
extern Bus busTable[TABLE_SIZE];

// Function declarations
void vline(char ch);
int hashFunction(const char* busNumber);
void emptyBus(Bus& bus);
void addBus();
void searchBus(const char* busNumber);
void showAvailableBuses();
void deleteBusInfo(const char* busNumber);
void readBusDataFromCSV(const char* filename);
void writeBusDataToCSV(const char* filename);
bool compareBuses(const Bus& bus1, const Bus& bus2);
void sortBus(Bus* buses, int top, int bottom, int sortBy);
void merge(Bus* buses, int top, int mid, int bottom, int sortBy);
bool validateTimeFormat(const char* timeStr);

// Custom comparator functions for sorting
bool compareByBusNo(const Bus& bus1, const Bus& bus2);
bool compareByDepartureTime(const Bus& bus1, const Bus& bus2);
bool compareByArrivalTime(const Bus& bus1, const Bus& bus2);

#endif