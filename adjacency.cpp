#include "adjacency.hpp"
#include <stdexcept>

Adjacency::Adjacency() {
      matrix = new double*[ROWS];
      for (int i = 0; i < ROWS; ++i) {
          matrix[i] = new double[COLUMNS];
          // Initialize all elements to infinity or a sentinel value
          for (int j = 0; j < COLUMNS; ++j) {
              matrix[i][j] = 0.0;
          }
      }
}

void Adjacency::initializeArray(std::ifstream* fileStream) {
    std::string line;
    
    // Read upper triangular part of the matrix
    for (int i = 0; i < ROWS - 1; ++i) {
        for (int j = i + 1; j < COLUMNS; ++j) {
            if (!std::getline(*fileStream, line)) {
                throw std::runtime_error("Incomplete matrix data in file");
            }
            
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

double Adjacency::returnTravelTime(int fromCity, int toCity) {
    if (fromCity < 0 || fromCity >= ROWS || toCity < 0 || toCity >= COLUMNS) {
    }
    
    return matrix[fromCity][toCity];
}

void Adjacency::printAll() {
  for (int i = 0; i < this->ROWS; ++i) {
    for (int j = 0; j < this->COLUMNS; ++j) {
      std::cout << "[" << i << "]" << "[" << j << "]" << " = " << this->matrix[i][j] << std::endl;
    }
  }
}

// Destructor for memory cleanup
Adjacency::~Adjacency() {
  for (int i = 0; i < ROWS; ++i) {
    delete[] matrix[i];
  }
  delete[] matrix;
}
