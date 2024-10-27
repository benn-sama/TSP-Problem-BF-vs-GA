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
  std::atomic<bool> timeout(false);
  std::string shortestPath;

  // Capture running and timeout in the lambda
  std::thread timerThread([&bruteForce, &running, &timeout]() { bruteForce.timer(running, timeout); });

  matrix.initializeArray(&fileStream);

  shortestPath = bruteForce.getShortestPath(matrix, 10, running);

  timerThread.join();

  std::cout << "Shortest path: " << shortestPath << std::endl;
}

int main() {
  testBF();
  return 0;
}