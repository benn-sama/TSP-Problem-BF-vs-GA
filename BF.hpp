#ifndef BF_HPP
#define BF_HPP

#include <vector>
#include <string>
#include <sstream>
#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include <atomic>
#include <iomanip>

#include "adjacency.hpp"


class BF {
  private:
    double minPath;
    double totalTimeTraveled = 0.0;
    std::vector<int> path;
  public:
    BF(); // default constructor
    std::string getShortestPath(Adjacency& matrix, int cities, std::atomic<bool>& running); // returns shortest path
    void timer(std::atomic<bool>& running, std::atomic<bool>& timeout);
};

#endif