#include "adjacency.hpp"
#include <stdexcept>

// defaule constructor
Adjacency::Adjacency() {
      matrix = new double*[ROWS];

      for (int i = 0; i < ROWS; ++i) {
          matrix[i] = new double[COLUMNS];
          // Initialize all elements to 0.0
          for (int j = 0; j < COLUMNS; ++j) {
              matrix[i][j] = 0.0;
          }
      }
}

// initializes matrix with data from a file assuming each line ONLY contains a double
void Adjacency::initializeArray(std::ifstream* fileStream) {
    std::string line;
    
    // Read upper triangular part of the matrix 
    for (int i = 0; i < ROWS - 1; ++i) {
        for (int j = i + 1; j < COLUMNS; ++j) {
            if (!std::getline(*fileStream, line)) {
                throw std::runtime_error("Incomplete matrix data in file");
            }
            
            // tokenizes values from the file and assigns it into a double
            std::istringstream iss(line);
            double value;
            if (!(iss >> value)) {
                throw std::runtime_error("Invalid number format in file");
            }
            
            // Set both symmetric positions
            matrix[i][j] = value;
            matrix[j][i] = value;
        }
    }
}

// returns travel time (edge of adjacent vertexes)
double Adjacency::returnTravelTime(int fromCity, int toCity) {
    // also checks out of bounds
    if (fromCity < 0 || fromCity >= ROWS || toCity < 0 || toCity >= COLUMNS) {
      return 0.0;
    }
    
    return matrix[fromCity][toCity];
}

// prints all weights for each edge to verify if it is correct
void Adjacency::printAll() {
  for (int i = 0; i < this->ROWS; ++i) {
    for (int j = 0; j < this->COLUMNS; ++j) {
      std::cout << "[" << i << "]" << "[" << j << "]" << " = " << this->matrix[i][j] << std::endl;
    }
  }
}

// returns row count
int Adjacency::getRows() {
  return this->ROWS;
}

// returns column count
int Adjacency::getColumns() {
  return this->COLUMNS;
}

// destructor for memory cleanup
Adjacency::~Adjacency() {
  for (int i = 0; i < ROWS; ++i) {
    delete[] matrix[i];
  }
  
  delete[] matrix;
}
