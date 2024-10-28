/*
 * File: BF-test1.cpp
 * Description: This file contains a test function for the BF (Brute Force) class.
 *              It initializes an adjacency matrix from a file and verifies
 *              the correctness of the shortest path calculation using the Brute Force algorithm.
 * 
 * Usage: The testBF function reads travel times from "distances.txt", starts a timer,
 *        and calculates the shortest path using the Brute Force algorithm. The results
 *        are printed to the console.
 */

#include "BF.hpp"
#include "adjacency.hpp"
#include <atomic>
#include <thread>
#include <iostream>
#include <fstream>

void testBF() {
  BF bruteForce;
  Adjacency matrix;
  std::ifstream fileStream("./distances.txt");
  std::atomic<bool> running(true);
  std::string shortestPath;

  std::cout << "Starting BF Tests" << std::endl << std::endl;
  // Capture running and timeout in the lambda
    std::cout << "here";
  std::thread timerThread([&bruteForce, &running]() { bruteForce.timer(running); });

  matrix.initializeArray(&fileStream);

  shortestPath = bruteForce.getShortestPath(matrix, 10, running);

  timerThread.join();



  std::cout << std::endl <<"Shortest path: " << shortestPath << std::endl;
}

int main() {
  testBF();
  return 0;
}