#include "include/file_reader.h"
#include <fstream>
#include <sstream>
#include <iostream>

FileReader::FileReader(const std::string& filename) : filename(filename) {}

std::vector<std::pair<std::string, bool>> FileReader::readFile() {
    std::vector<std::pair<std::string, bool>> dataVector; // Vector to store the values

    std::ifstream inputFile(filename); // Open the file
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return dataVector;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string key;
        std::string boolStr;

        // Read string and boolean separated by comma
        if (std::getline(iss, key, ',') && std::getline(iss, boolStr, ',')) {
            // Convert boolean string to bool, allow for all forms of true
            bool value = (boolStr == "true" || boolStr == "1" || boolStr == "TRUE" || boolStr == "True");
            // Emplace the pair directly into the vector
            dataVector.emplace_back(key, value);
        }
    }

    inputFile.close(); // Close the file
    return dataVector;
}
