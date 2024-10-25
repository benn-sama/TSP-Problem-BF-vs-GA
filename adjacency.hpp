#ifndef ADJACENCY_HPP
#define ADJACENCY_HPP

#include <variant>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

class Adjacency {
  private:
    int const ROWS = 20;
    int COLUMNS = 20;
    double** matrix;

  public:
    Adjacency();  // default constructor
    void initializeArray(std::ifstream* ifstream); // initializes matrix
    double returnTravelTime(int fromCity, int toCity); // returns travel time of the specified cities
    void printAll();
    ~Adjacency();
};

#endif