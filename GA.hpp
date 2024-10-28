/*
 * File: GA.hpp, GA.cpp
 * Description: This header file defines the GA (Genetic Algorithm) class, which provides
 *              methods to calculate the shortest path between cities using a genetic algorithm.
 * 
 * Usage: The GA class provides methods to initialize tours, generate a single tour, evaluate tours,
 *        mutate tours, calculate the shortest path, measure elapsed time, and get the total travel time.
 *        It uses an adjacency matrix to store travel times between cities and vectors to keep track of
 *        the population of tours and the shortest path.
 */

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
    int cities; // number of cities
    std::vector<int> path; // shortest path
    std::vector<std::vector<int>> tours; // population of tours
    std::mt19937 rng; // random number generator
    int generationCounter;
    double totalElapsed;

  public:
    GA(int initialTours, int generations, int mutationPercentage, int cities); // paramaterized constructor
    std::string getShortestPath(Adjacency& matrix, std::atomic<bool>& running); // returns shortest path
    void initializeTours(); // inserts tours
    std::vector<int> generateTour(); // generates a single tour
    double tourDistance(Adjacency& matrix);
    void evaluateTours(Adjacency& matrix);
    void mutate(); // mutates a certain amount of tours
    void timer(std::atomic<bool>& running); // elapsed time
    double getTimeElapsed(); // returns time elapsed
    double getTimeTraveled(); // returns timeTraveled
};

#endif
