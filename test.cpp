/*
    test.cpp
    Author: M00934573
    Created: 18/04/2024
    Updated: 21/04/2024
*/
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "bus.h"
#include <sstream>
#include <vector>
#include <cstring>
#include <fstream>
#include <cstdio>
#include <iostream>

namespace test
{
    void addBusForTesting(const std::string &busNumber, const char *driver,
			  const char *departure, const char *ETA,
			  const char *from, const char *to)
    {
        Bus bus;
        strcpy(bus.busn, busNumber.c_str()); // Copy busNumber to bus.busn
        strcpy(bus.driver, driver);
        strcpy(bus.departure, departure);
        strcpy(bus.ETA, ETA);
        strcpy(bus.from, from);
        strcpy(bus.to, to);
        // emptyBus(bus); // Initialize all seats to "Empty"
        busTable[hashFunction(busNumber.c_str())] = bus; // Store in busTable
    }

    std::string showAvailableBuses()
    {
        std::stringstream buffer;
        // Redirect cout to buffer
        std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

        bool found = false;
        // Iterate through busTable to find available buses
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (strcmp(busTable[i].busn, "") != 0) {
                found = true;
                std::cout << "Bus no: " << busTable[i].busn
                          << " From: " << busTable[i].from
                          << " To: " << busTable[i].to
                          << " Departs at: " << busTable[i].departure
			  << std::endl;
            }
        }

        if (!found) {
            std::cout << "No available buses found." << std::endl;
        }

        std::cout.rdbuf(old); // Restore cout
        // Return the output for validation in tests
        return buffer.str();
    }

    void addBus(const std::string &busNumber, const char *driver,
		const char *departure, const char *ETA,
		const char *from, const char *to)
    {
        Bus bus;
        strcpy(bus.busn, busNumber.c_str());
        strcpy(bus.driver, driver);
        strcpy(bus.departure, departure);
        strcpy(bus.ETA, ETA);
        strcpy(bus.from, from);
        strcpy(bus.to, to);
        // emptyBus(bus); // Initialize all seats to "Empty"
        busTable[hashFunction(busNumber.c_str())] = bus;
    }

    // Helper function to clear busTable
    void clearBusTable()
    {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            strcpy(busTable[i].busn, "");
        }
    }

    // Function to delete a bus from the busTable
    void deleteBusInfo(const std::string &busNumber)
    {
        int index = hashFunction(busNumber.c_str());
        if (strcmp(busTable[index].busn, "") != 0) {
            strcpy(busTable[index].busn, "");
            std::cout << "Bus information deleted successfully." << std::endl;
        } else {
            std::cout << "Bus not found." << std::endl;
        }
    }
    // Function to sorting buses
    void fillBusData() {
        clearBusTable();
        addBusForTesting("123", "Driver A", "10:00",
			 "14:00", "City X", "City Y");
        addBusForTesting("456", "Driver B", "09:30",
			 "13:30", "City Y", "City Z");
        addBusForTesting("789", "Driver C", "08:00",
			 "12:00", "City Z", "City X");
    }

    std::vector<Bus> performSort(int sortBy) {
        std::vector<Bus> sortedBuses;
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (strcmp(busTable[i].busn, "") != 0) {
                sortedBuses.push_back(busTable[i]);
            }
        }
        int count = sortedBuses.size();
        sortBus(sortedBuses.data(), 0, count - 1, sortBy);
        return sortedBuses;
    }
  
    // For searchBus() function
    // Function to capture console output during tests
    std::string captureBusSearchOutput(const std::string& busNumber) {
        std::streambuf* originalCoutStreamBuf = std::cout.rdbuf();
        std::ostringstream capturedOutput;
        std::cout.rdbuf(capturedOutput.rdbuf());

        // Perform search
        searchBus(busNumber.c_str());

        // Restore original buffer before returning captured output
        std::cout.rdbuf(originalCoutStreamBuf);
        return capturedOutput.str();
    }
}

TEST_CASE("Add bus information", "[addBus]")
{
    // Clear the bus table before each test to ensure a clean state
    test::clearBusTable();

    SECTION("Add a valid bus")
    {
        test::addBus("1234", "John Doe", "10:00", "15:00", "City A", "City B");

        REQUIRE(strcmp(busTable[hashFunction("1234")].busn, "") != 0);
        Bus &bus = busTable[hashFunction("1234")];
        REQUIRE(strcmp(bus.driver, "John Doe") == 0);
        REQUIRE(strcmp(bus.departure, "10:00") == 0);
        REQUIRE(strcmp(bus.ETA, "15:00") == 0);
        REQUIRE(strcmp(bus.from, "City A") == 0);
        REQUIRE(strcmp(bus.to, "City B") == 0);
    }
}

// Helper function to add a bus for testing
void setupTestData()
{
    Bus bus;
    strcpy(bus.busn, "1234");
    strcpy(bus.driver, "John Doe");
    strcpy(bus.departure, "10:00");
    strcpy(bus.ETA, "15:00");
    strcpy(bus.from, "City A");
    strcpy(bus.to, "City B");
    // emptyBus(bus);
    busTable[hashFunction("1234")] = bus; // Manually add bus to the table
}

TEST_CASE("Delete bus information", "[deleteBusInfo]")
{
    // Clear the bus table before each test to ensure a clean state
    test::clearBusTable(); 

    SECTION("Deleting an existing bus")
    {
        // Setup test data with one bus
        test::addBus("1234", "John Doe", "10:00", "15:00", "City A", "City B");

        // Ensure the bus exists before deletion
        REQUIRE(strcmp(busTable[hashFunction("1234")].busn, "") != 0);

        // Attempt to delete the bus
        test::deleteBusInfo("1234");

        // Check if the bus is successfully deleted
        REQUIRE(strcmp(busTable[hashFunction("1234")].busn, "") == 0);
    }

    SECTION("Attempting to delete a non-existing bus")
    {
        // Attempt to delete a bus that doesn't exist
        test::deleteBusInfo("9999");

        // Check that nothing has changed in the busTable
        REQUIRE(strcmp(busTable[hashFunction("9999")].busn, "") == 0);
    }
}
TEST_CASE("sortBus function", "[sortBus]") {
    test::fillBusData();
    SECTION("Sort by Bus Number") {
        auto sortedBuses = test::performSort(1);
        REQUIRE(strcmp(sortedBuses[0].busn, "123") == 0);
        REQUIRE(strcmp(sortedBuses[1].busn, "456") == 0);
        REQUIRE(strcmp(sortedBuses[2].busn, "789") == 0);
    }

    SECTION("Sort by Departure Time") {
        auto sortedBuses = test::performSort(2);
        REQUIRE(strcmp(sortedBuses[0].departure, "08:00") == 0);
        REQUIRE(strcmp(sortedBuses[1].departure, "09:30") == 0);
        REQUIRE(strcmp(sortedBuses[2].departure, "10:00") == 0);
    }

    SECTION("Sort by Arrival Time") {
        auto sortedBuses = test::performSort(3);
        REQUIRE(strcmp(sortedBuses[0].ETA, "12:00") == 0);
        REQUIRE(strcmp(sortedBuses[1].ETA, "13:30") == 0);
        REQUIRE(strcmp(sortedBuses[2].ETA, "14:00") == 0);
    }
}

// Testing for showAvailableBUs() function
TEST_CASE("showAvailableBuses function", "[showAvailableBuses]") {
    // Clear the bus table and add test data
    test::clearBusTable();
    test::addBusForTesting("100", "Driver One", "08:00",
			   "12:00", "Station A", "Station B");
    test::addBusForTesting("200", "Driver Two", "09:00",
			   "13:00", "Station B", "Station C");

    SECTION("Display all available buses") {
        std::string expectedOutput = 
            "Bus no: 100 From: Station A To: Station B Departs at: 08:00\n"
            "Bus no: 200 From: Station B To: Station C Departs at: 09:00\n";

        REQUIRE(test::showAvailableBuses() == expectedOutput);
    }

    SECTION("No available buses") {
        test::clearBusTable(); // Ensure there are no buses
        std::string expectedOutput = "No available buses found.\n";
        REQUIRE(test::showAvailableBuses() == expectedOutput);
    }
}


TEST_CASE("merge function", "[merge]") {
    // Setup pre-sorted arrays for testing the merge
    std::vector<Bus> leftBuses = {
        Bus("123", "10:00", "Driver A", "", "City A", "City B", "13:00"),
        Bus("234", "09:30", "Driver B", "", "City C", "City D", "12:30")
    };
    std::vector<Bus> rightBuses = {
        Bus("345", "11:00", "Driver C", "", "City E", "City F", "14:00"),
        Bus("456", "12:00", "Driver D", "", "City G", "City H", "15:00")
    };

    // Combine left and right into one larger vector for merging
    std::vector<Bus> resultBuses = leftBuses;
    resultBuses.insert(resultBuses.end(), rightBuses.begin(), rightBuses.end());

    // Perform the merge on the result array
     // Assuming sort by bus number
    merge(resultBuses.data(), 0, leftBuses.size() - 1,
	  resultBuses.size() - 1, 1); 

    // Check if the result array is sorted correctly
    REQUIRE(strcmp(resultBuses[0].busn, "123") == 0);
    REQUIRE(strcmp(resultBuses[1].busn, "234") == 0);
    REQUIRE(strcmp(resultBuses[2].busn, "345") == 0);
    REQUIRE(strcmp(resultBuses[3].busn, "456") == 0);
}

// compare Tests: compareByBusNo, compareByDepartureTime
// and compareByArrivalTime
TEST_CASE("compareByBusNo", "[comparator]") {
    Bus bus1("123", "10:00", "Driver A", "", "City A", "City B", "13:00");
    Bus bus2("456", "09:30", "Driver B", "", "City C", "City D", "12:30");

    SECTION("Bus number comparison where first is less") {
        REQUIRE(compareByBusNo(bus1, bus2) == true);
    }

    SECTION("Bus number comparison where first is greater") {
        REQUIRE(compareByBusNo(bus2, bus1) == false);
    }
}

TEST_CASE("compareByDepartureTime", "[comparator]") {
    Bus bus1("123", "08:00", "Driver A", "", "City A", "City B", "13:00");
    Bus bus2("456", "09:30", "Driver B", "", "City C", "City D", "12:30");

    SECTION("Departure time comparison where first departs earlier") {
        REQUIRE(compareByDepartureTime(bus1, bus2) == true);
    }

    SECTION("Departure time comparison where first departs later") {
        REQUIRE(compareByDepartureTime(bus2, bus1) == false);
    }
}

TEST_CASE("compareByArrivalTime", "[comparator]") {
    Bus bus1("123", "10:00", "Driver A", "", "City A", "City B", "11:00");
    Bus bus2("456", "09:30", "Driver B", "", "City C", "City D", "14:00");

    SECTION("Arrival time comparison where first arrives earlier") {
        REQUIRE(compareByArrivalTime(bus1, bus2) == true);
    }

    SECTION("Arrival time comparison where first arrives later") {
        REQUIRE(compareByArrivalTime(bus2, bus1) == false);
    }
}

// Testing readBusDataFromCSV and writeBusDataToCSV
TEST_CASE("CSV file write and read", "[file_io]") {
    const std::string testFileName = "test_buses.csv";

    // Setup - clear the bus table and remove any existing test file
    test::clearBusTable();
    std::remove(testFileName.c_str());  // Ensure there's no leftover test file

    SECTION("Write to CSV and then read from CSV") {
        // Add some buses to the bus table
        test::addBusForTesting("123", "Driver A", "10:00",
			       "13:00", "City A", "City B");
        test::addBusForTesting("456", "Driver B", "09:30",
			       "12:30", "City C", "City D");

        // Write these buses to a CSV file
        writeBusDataToCSV(testFileName.c_str());

        // Clear the bus table to simulate a fresh start
        test::clearBusTable();

        // Read the data back from the CSV
        readBusDataFromCSV(testFileName.c_str());

        // Verify that the data read matches the data written
        REQUIRE(strcmp(busTable[hashFunction("123")].busn, "123") == 0);
        REQUIRE(strcmp(busTable[hashFunction("456")].busn, "456") == 0);
        REQUIRE(strcmp(busTable[hashFunction("123")].driver, "Driver A") == 0);
        REQUIRE(strcmp(busTable[hashFunction("456")].from, "City C") == 0);

        // Cleanup - remove the test file to avoid clutter
        std::remove(testFileName.c_str());
    }
}

// Testing for the searchBus() function
TEST_CASE("searchBus function", "[searchBus]") {
    test::clearBusTable();  // Clear the bus table before each test

    SECTION("Searching for an existing bus") {
        test::addBusForTesting("1234", "John Doe", "10:00", "15:00",
			       "City A", "City B");
        std::string output = test::captureBusSearchOutput("1234");
        REQUIRE(output.find("1234") != std::string::npos);
        REQUIRE(output.find("John Doe") != std::string::npos);
        REQUIRE(output.find("No bus found") == std::string::npos);
    }

    SECTION("Attempting to search for a non-existing bus") {
        std::string output = test::captureBusSearchOutput("9999");
        REQUIRE(output.find("Bus not found") != std::string::npos);
    }
}

// Testing for hashFunction() function
TEST_CASE("hashFunction", "[hash]") {
    SECTION("Consistency check") {
        REQUIRE(hashFunction("12345") == hashFunction("12345"));
    }

    SECTION("Different inputs should hash differently") {
        // If collisions are rare, this test should usually pass.
        REQUIRE(hashFunction("12345") != hashFunction("54321"));
    }
}
 // Ensure that the function is included properly from the bus.cpp
extern void vline(char ch); 

TEST_CASE("vline function produces correct output", "[vline]") {
    // Save old buf
    std::streambuf* originalCoutStreamBuf = std::cout.rdbuf(); 
    std::ostringstream capturedOutput;
    // Redirect std::cout to capturedOutput
    std::cout.rdbuf(capturedOutput.rdbuf()); 

    // Call the function to test
    vline('*');
    
    // Restore std::cout to its original buffer
    std::cout.rdbuf(originalCoutStreamBuf);
    
    // Expect 100 '*' characters
    std::string expectedLine(100, '*'); 
    REQUIRE(capturedOutput.str() == expectedLine);

    SECTION("Check the length of the output") {
        REQUIRE(capturedOutput.str().length() == 100);
    }
}

// Testing for validateTimeFormat() function
TEST_CASE("validateTimeFormat function", "[time_validation]") {
    SECTION("Valid time formats") {
        REQUIRE(validateTimeFormat("12:34") == true);
        REQUIRE(validateTimeFormat("00:00") == true);
        REQUIRE(validateTimeFormat("23:59") == true);
    }

    SECTION("Invalid time formats - incorrect lengths") {
        REQUIRE(validateTimeFormat("1234") == false);
        REQUIRE(validateTimeFormat("12:345") == false);
        REQUIRE(validateTimeFormat("1:34") == false);
    }

    SECTION("Invalid time formats - missing or incorrect colon position") {
        REQUIRE(validateTimeFormat("12345") == false);
        REQUIRE(validateTimeFormat("12;34") == false);
        REQUIRE(validateTimeFormat("1234:") == false);
    }

    SECTION("Invalid time formats - out of range values") {
        // '24' is not a valid hour in a 24-hour format
        REQUIRE(validateTimeFormat("24:00") == false);
	// '60' is not a valid minute
        REQUIRE(validateTimeFormat("12:60") == false); 
        REQUIRE(validateTimeFormat("-01:00") == false);
        REQUIRE(validateTimeFormat("00:-01") == false);
    }
}
