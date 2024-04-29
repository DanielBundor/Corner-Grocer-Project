#include <iostream>
#include <fstream>
#include <map>

// Function to load data from a file into a map
void loadFileData(const std::string& fileName, std::map<std::string, int>& frequencyMap) {
    // Open the input file
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()) { // Check if file opening failed
        std::cerr << "Error: Unable to open file " << fileName << std::endl;
        exit(1); // Exit the program with error code 1
    }

    std::string item;
    // Read each item from the file and update its frequency in the map
    while (inputFile >> item) {
        frequencyMap[item]++;
    }

    // Close the input file
    inputFile.close();
}

// Function to print the frequency of each item in the map
void printFrequency(const std::map<std::string, int>& frequencyMap) {
    for (const auto& pair : frequencyMap) {
        std::cout << pair.first << " " << pair.second << std::endl;
    }
}

// Function to print a histogram representing the frequency of each item
void printHistogram(const std::map<std::string, int>& frequencyMap) {
    for (const auto& pair : frequencyMap) {
        std::cout << pair.first << " ";
        // Print asterisks corresponding to the frequency of the item
        for (int i = 0; i < pair.second; ++i) {
            std::cout << "*";
        }
        std::cout << std::endl;
    }
}

// Function to save the frequency data to a file
void saveFrequencyData(const std::string& fileName, const std::map<std::string, int>& frequencyMap) {
    // Open the output file
    std::ofstream outputFile(fileName);
    if (!outputFile.is_open()) { // Check if file opening failed
        std::cerr << "Error: Unable to create output file " << fileName << std::endl;
        return; // Return without saving if file creation failed
    }

    // Write each item and its frequency to the output file
    for (const auto& pair : frequencyMap) {
        outputFile << pair.first << " " << pair.second << std::endl;
    }

    // Close the output file
    outputFile.close();
}

int main() {
    std::map<std::string, int> frequencyMap;
    // Load data from the input file into the frequency map
    loadFileData("CS210_Project_Three_Input_File.txt", frequencyMap);

    int choice;
    do {
        // Display the menu options
        std::cout << "\nMENU\n";
        std::cout << "1. Search for item\n";
        std::cout << "2. Print frequency of all items\n";
        std::cout << "3. Print histogram\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string searchItem;
            // Prompt the user to enter the item to search for
            std::cout << "Enter the item to search for: ";
            std::cin >> searchItem;
            auto it = frequencyMap.find(searchItem);
            // Check if the item exists in the frequency map
            if (it != frequencyMap.end()) {
                std::cout << "Frequency of " << searchItem << ": " << it->second << std::endl;
            }
            else {
                std::cout << "Item not found." << std::endl;
            }
            break;
        }
        case 2:
            // Print the frequency of all items
            printFrequency(frequencyMap);
            break;
        case 3:
            // Print a histogram representing the frequency of all items
            printHistogram(frequencyMap);
            break;
        case 4:
            std::cout << "Exiting program..." << std::endl;
            // Save the frequency data to a backup file
            saveFrequencyData("frequency.dat", frequencyMap);
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 4);

    return 0;
}