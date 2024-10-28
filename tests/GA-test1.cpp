/*
 * File: GA-test1.cpp
 * Description: This file contains a test function for the GA (Genetic Algorithm) class.
 *              It initializes an adjacency matrix from a file and verifies
 *              the correctness of the shortest path calculation using the Genetic Algorithm.
 * 
 * Usage: The testGA function reads travel times from "distances.txt", starts a timer,
 *        and calculates the shortest path using the Genetic Algorithm. The results
 *        are printed to the console.
 */

#include "GA.hpp"
#include "adjacency.hpp"
#include <atomic>
#include <thread>
#include <iostream>
#include <fstream>

void testGA() {
  GA geneticAlgorithm(100, 1000, 30, 10); // Using reasonable default values
  Adjacency matrix;
  std::ifstream fileStream("./distances.txt");
  std::atomic<bool> running(true);
  std::string shortestPath;

  std::cout << "Starting GA Tests" << std::endl << std::endl;
  
  std::thread timerThread([&geneticAlgorithm, &running]() { geneticAlgorithm.timer(running); });

  matrix.initializeArray(&fileStream);

  shortestPath = geneticAlgorithm.getShortestPath(matrix, running);

  timerThread.join();

  std::cout << std::endl << "Shortest path: " << shortestPath << std::endl;
  std::cout << "Total travel time: " << geneticAlgorithm.getTimeTraveled() << std::endl;
}

int main() {
  testGA();
  return 0;
}