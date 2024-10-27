#ifndef GA_HPP
#define GA_HPP

#include <chrono>
#include <thread>
#include <string>
#include <iomanip>
#include <vector>
#include <random>
#include <algorithm>
#include "adjacency.hpp"

class GA {
  private:
    int initialTours; // amount of inital tours
    int generations; // amount of generations to mutate
    double mutationPercentage; // percentage of mutations per generation
    double totalTimeTraveled; // opt
    double minPath; // holds min path
    int cities;
    std::vector<int> path; // shortest path
    std::vector<std::vector<int>> tours; // population of tours
    std::mt19937 rng; // random number generator
    int generationCounter;

  public:
    GA(int initialTours, int generations, int mutationPercentage, int cities); // paramaterized constructor
    std::string getShortestPath(Adjacency& matrix, std::atomic<bool>& running); // returns shortest path
    void initializeTours(); // inserts tours
    std::vector<int> generateTour(); // generates a single tour
    double tourDistance(Adjacency& matrix);
    void evaluateTours(Adjacency& matrix);
    void mutate(); // mutates a certain amount of tours
    void timer(std::atomic<bool>& running); // elapsed time
    double getTimeTraveled();
};

#endif
