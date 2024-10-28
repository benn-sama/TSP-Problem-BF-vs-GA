/*
 * File: main.cpp
 * Description: This file contains the main function for the TSP Solver, which compares
 *              the performance of the Genetic Algorithm (GA) and Brute Force (BF) algorithms
 *              in solving the Traveling Salesman Problem (TSP).
 * 
 * Usage: The program prompts the user for input parameters such as the number of cities,
 *        initial tours, generations, and mutation rate. It then initializes the adjacency
 *        matrices from files and runs both the GA and BF algorithms to find the shortest path.
 *        The results, including the shortest path and total travel time, are printed to the console.
 */

#include <iostream>
#include <iomanip>
#include <thread>
#include <atomic>
#include <fstream>
#include <limits>
#include "GA.hpp"
#include "BF.hpp"
#include "adjacency.hpp"

bool getValidInput(const std::string& prompt, int& value, int minValue = 0) {
  std::cout << prompt;
  if (!(std::cin >> value) || value < minValue) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Error: Please enter a valid number (minimum " << minValue << ")\n";
  return false;
  }
  return true;
}

int main() {
  int numCities = -1;
  int initialTours = -1;
  int generations = -1;
  int mutationRate = -1;

  std::cout << "TSP Solver - GA vs Brute Force Comparison\n\n";

  // get valid inputs
  while (numCities < 0) {
    if (!getValidInput("Enter number of cities: ", numCities, 1)) continue;
  }

  while (initialTours < 0) {
    if (!getValidInput("Enter number of initial tours for GA: ", initialTours, 1)) continue;
  }

  while (generations < 0) {
    if (!getValidInput("Enter number of generations for GA: ", generations, 1)) continue;
  }

  while (mutationRate < 0 || mutationRate > 100) {
    if (!getValidInput("Enter mutation rate (0-100): ", mutationRate, 0)) continue;
    if (mutationRate > 100) {
      std::cout << "Error: Mutation rate must be between 0 and 100\n";
      mutationRate = -1;
    }
  }

  // load distance matrix
  Adjacency matrix;
  std::ifstream fileStream("./distances.txt");

  if (!fileStream.is_open()) {
    std::cerr << "Error: Could not open distances file.\n";
    return 1;
  }

  matrix.initializeArray(&fileStream);

  std::cout << "\nRunning algorithms for " << numCities << " cities...\n\n";

  // run Brute Force
  std::cout << "Running Brute Force algorithm...\n";
  std::atomic<bool> runningBF(true);
  BF bruteForce;
  std::thread timerThread1([&bruteForce, &runningBF]() { bruteForce.timer(runningBF); });
  std::string bfTour = bruteForce.getShortestPath(matrix, numCities, runningBF);
  double bfTime = bruteForce.getTotalTimeTraveled();
  timerThread1.join();

  // run Genetic Algorithm
  std::cout << "\nRunning Genetic Algorithm...\n";
  std::atomic<bool> runningGA(true);
  GA geneticAlgorithm(initialTours, generations, mutationRate, numCities);
  std::thread timerThread2([&geneticAlgorithm, &runningGA]() { geneticAlgorithm.timer(runningGA); });
  std::string gaTour = geneticAlgorithm.getShortestPath(matrix, runningGA);
  double gaTime = geneticAlgorithm.getTimeTraveled();
  timerThread2.join();
    
  // Calculate GA percentage of optimal
  double percentOfOptimal = (gaTime / bfTime) * 100.0;

  // Final summary output
  std::cout << "\nResults:\n";
  std::cout << "----------------------------------------\n";
  std::cout << "Cities: " << numCities << "\n\n";

  std::cout << "Brute Force:\n";
  std::cout << "  Optimal cost: " << std::fixed << std::setprecision(1) << bfTime << "\n";
  std::cout << "  Time taken: " << bruteForce.getTimeElapsed() << " seconds\n\n";

  std::cout << "Genetic Algorithm:\n";
  std::cout << "  Cost found: " << std::fixed << std::setprecision(1) << gaTime << "\n";
  std::cout << "  Time taken: " << geneticAlgorithm.getTimeElapsed() << " seconds\n\n";

  std::cout << "GA produced " << std::fixed << std::setprecision(1) 
            << percentOfOptimal << "% of optimal\n";

  return 0;
}