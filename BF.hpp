/*
 * File: BF.hpp, BF.cpp
 * Description: This header file defines the BF (Brute Force) class, which provides
 *              methods to calculate the shortest path between cities using a brute force algorithm.
 * 
 * Usage: The BF class provides methods to calculate the shortest path, measure elapsed time,
 *        and get the total travel time. It uses an adjacency matrix to store travel times
 *        between cities and a vector to keep track of the path.
 */

#ifndef BF_HPP
#define BF_HPP

#include <vector>
#include <string>
#include <sstream>
#include <string>
#include <chrono>
#include <thread>
#include <atomic>
#include <iomanip>

#include "adjacency.hpp"


class BF {
  private:
    double elapsedTime;
    double minPath;
    double totalTimeTraveled = 0.0;
    std::vector<int> path; // keeps track of path
  public:
    BF(); // default constructor
    std::string getShortestPath(Adjacency& matrix, int cities, std::atomic<bool>& running); // returns shortest path
    void timer(std::atomic<bool>& running); // elapsed time
    double getTimeElapsed(); // returns time elapsed
    double getTotalTimeTraveled(); // returns OPT
};

#endif