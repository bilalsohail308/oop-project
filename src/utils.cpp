#include "../include/Utils.h"
#include <fstream>
#include <sstream>

// Function to generate a unique ID
std::string generateUniqueId() {
    const std::string idFilePath = "../assets/unique_id_counter.txt";
    static int counter = 0;

    std::ifstream inFile(idFilePath);
    if (inFile.is_open()) {
        inFile >> counter;
        inFile.close();
    } else {
        counter = 0;
    }

    std::ofstream outFile(idFilePath, std::ios::trunc);
    if (outFile.is_open()) {
        outFile << (counter + 1);
        outFile.close();
    }

    std::stringstream ss;
    ss << "ITEM-" << ++counter;
    return ss.str();
}
