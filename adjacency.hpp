#ifndef ADJACENCY_HPP
#define ADJACENCY_HPP

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <utility>

class Adjacency {
  private:
    int const ROWS = 20;
    int const COLUMNS = 20;
    double** matrix;

  public:
    Adjacency();                                       // default constructor
    void initializeArray(std::ifstream* ifstream);     // initializes matrix
    double returnTravelTime(int fromCity, int toCity); // returns travel time of the specified cities
    void printAll();                                   // prints all weights for testing purposes
    int getRows();                                     // getter of ROWS
    int getColumns();                                  // getter of COLUMNS
    ~Adjacency();                                      // deconstructor
};

#endif