#include "GA.hpp"
#include "adjacency.hpp"
#include <atomic>
#include <thread>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <set>
#include <iomanip>
#include <random>

void validateParameters(int populationSize, int generations, int mutationRate) {
    if (populationSize <= 0) {
        throw std::invalid_argument("Population size must be positive");
    }
    if (generations <= 0) {
        throw std::invalid_argument("Number of generations must be positive");
    }
    if (mutationRate < 0 || mutationRate > 100) {
        throw std::invalid_argument("Mutation rate must be between 0 and 100");
    }
}

void validatePath(const std::string& shortestPath, int numCities) {
    std::vector<int> pathNodes;
    std::istringstream iss(shortestPath);
    int node;
    
    while (iss >> node) {
        pathNodes.push_back(node);
    }

    size_t pathLength = pathNodes.size();
    if (pathLength != static_cast<size_t>(numCities + 1)) {
        throw std::runtime_error("Invalid path length: " + 
            std::to_string(pathLength) + " (expected " + 
            std::to_string(numCities + 1) + ")");
    }

    if (pathNodes.front() != pathNodes.back()) {
        throw std::runtime_error("Path does not return to start city");
    }

    std::set<int> visited;
    for (size_t i = 0; i < pathNodes.size() - 1; ++i) {
        if (pathNodes[i] < 0 || pathNodes[i] >= numCities) {
            throw std::runtime_error("Invalid city index: " + std::to_string(pathNodes[i]));
        }
        if (!visited.insert(pathNodes[i]).second) {
            throw std::runtime_error("City visited multiple times: " + std::to_string(pathNodes[i]));
        }
    }
    
    if (visited.size() != static_cast<size_t>(numCities)) {
        throw std::runtime_error("Not all cities were visited");
    }
}

void createTestDataFile(const std::string& filename, int numCities) {
    std::ofstream outFile(filename);
    if (!outFile) {
        throw std::runtime_error("Could not create test data file");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(1.0, 100.0);

    // write upper triangular matrix data
    for (int i = 0; i < numCities - 1; ++i) {
        for (int j = i + 1; j < numCities; ++j) {
            outFile << std::fixed << std::setprecision(2) << dis(gen) << "\n";
        }
    }
    outFile.close();
}

void testGA() {
    try {
        std::cout << "\nRunning GA Tests...\n" << std::endl;
        
        const std::vector<std::tuple<int, int, int>> testCases = {
            {100, 1000, 30},   // Small population, many generations
            {200, 500, 25},    // Medium population, medium generations
            {300, 250, 20}     // Large population, fewer generations
        };

        // Create and use a temporary file for test data
        std::string testDataFile = "test_matrix.txt";
        Adjacency matrix;  // Use default constructor
        int numCities = matrix.getRows(); // Get the fixed size from Adjacency class

        for (const auto& testCase : testCases) {
            int populationSize = std::get<0>(testCase);
            int generations = std::get<1>(testCase);
            int mutationRate = std::get<2>(testCase);

            std::cout << "\nTest Case:" << std::endl;
            std::cout << "Population Size: " << populationSize << std::endl;
            std::cout << "Generations: " << generations << std::endl;
            std::cout << "Mutation Rate: " << mutationRate << "%" << std::endl;
            std::cout << "Number of Cities: " << numCities << std::endl;

            // Validate input parameters
            validateParameters(populationSize, generations, mutationRate);

            // Create test data file and initialize matrix
            createTestDataFile(testDataFile, numCities);
            std::ifstream inFile(testDataFile);
            if (!inFile) {
                throw std::runtime_error("Could not open test data file");
            }
            matrix.initializeArray(&inFile);
            inFile.close();

            // Initialize GA
            GA ga(populationSize, generations, mutationRate, numCities);
            std::atomic<bool> running(true);

            // Create timer thread
            std::thread timerThread(&GA::timer, &ga, std::ref(running));

            // Get shortest path
            std::string shortestPath = ga.getShortestPath(matrix, running);
            
            // Validate the returned path
            validatePath(shortestPath, numCities);

            // Get and validate total travel time
            double totalTime = ga.getTimeTraveled();
            if (totalTime <= 0) {
                throw std::runtime_error("Invalid total travel time: " + std::to_string(totalTime));
            }

            std::cout << "Shortest Path: " << shortestPath << std::endl;
            std::cout << "Total Travel Time: " << std::fixed << std::setprecision(2) 
                      << totalTime << std::endl;
            
            // Wait for timer thread to finish
            if (timerThread.joinable()) {
                timerThread.join();
            }
        }

        // Clean up test file
        std::remove(testDataFile.c_str());
        std::cout << "\nAll test cases passed successfully!" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "\nError in testGA: " << e.what() << std::endl;
        throw;
    }
}

int main() {
      std::cout << "Starting GA Tests..." << std::endl;
      testGA();
      std::cout << "\nAll tests completed successfully." << std::endl;
      return 0;
}