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