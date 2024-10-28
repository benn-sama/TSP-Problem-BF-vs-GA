/*
 * File: adjacency-test1.cpp
 * Description: This file contains a test function for the Adjacency class.
 *              It initializes an adjacency matrix from a file and verifies
 *              the correctness of the travel times between cities.
 * 
 * Usage: The testMatrixValues function reads travel times from "distances.txt"
 *        and checks specific values to ensure they match expected results.
 *        If any value does not match, an error message is printed.
 */

#include <iostream>
#include <fstream>
#include <stdexcept>  // Include for std::runtime_error

#include "adjacency.hpp"

void testMatrixValues() {
    Adjacency* matrix = new Adjacency();
    std::ifstream inFile("./distances.txt");  // Correctly create and open the ifstream

    if (!inFile.is_open()) {
        std::cerr << "File couldn't be found" << std::endl;
        return;
    }
    matrix->initializeArray(&inFile);  // Pass the pointer to ifstream

    try {
        if (matrix->returnTravelTime(0, 0) != 0.0) {
            throw std::runtime_error("[0][0] is not 0.0!\nValue: " + std::to_string(matrix->returnTravelTime(0, 0)));
        }

        if (matrix->returnTravelTime(1, 0) != 25.410000) {
            throw std::runtime_error("[1][0] is not 25.410000!\nValue: " + std::to_string(matrix->returnTravelTime(1, 0)));
        }

        if (matrix->returnTravelTime(2, 0) != 109.670000) {
            throw std::runtime_error("[2][0] is not 109.670000!\nValue: " + std::to_string(matrix->returnTravelTime(2, 0)));
        }

        if (matrix->returnTravelTime(4, 2) != 95.350000) {
            throw std::runtime_error("[4][3] is not 95.350000!\nValue: " + std::to_string(matrix->returnTravelTime(4, 2)));
        }
    }
    catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    delete matrix;
}

int main() {
    testMatrixValues();
}