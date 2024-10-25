#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "adjacency.hpp"

void testMatrixValues() {
  std::fstream fileStream("./distances.txt");
  std::vector<double> testWeights;
  std::string line = "";
  Adjacency* matrix = new Adjacency();
  int i = 1;
  int j = 0; 
  int k = 0;
  int size;


  try {
    if (!fileStream.is_open()) {
      throw std::runtime_error("File couldn't be found");
    }
  }
  catch (const std::runtime_error& e) {
    std::cout << e.what() << std::endl;
  }

  while (getline(fileStream, line)) {
    std::istringstream token(line);
    double weight;

    token >> weight;

    testWeights.insert(testWeights.begin(), weight);
  }

  size = testWeights.size();

  while (k < size) {
    if (matrix->returnTravelTime(i, j) != 0.0) {
      try {
        if (testWeights[k] != matrix->returnTravelTime(i, j) && testWeights[k] != matrix->returnTravelTime(j, i)) {
          double travelTime = matrix->returnTravelTime(i, j);
          throw std::runtime_error("Travel Time aren't the same!\n" 
                                   "Test Weight: " + std::to_string(testWeights[k]) +
                                   "Matrix Weight: " + std::to_string(travelTime));
        }
      }
      catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
      }

      ++k;
    }
    ++i;
    ++j;
  }
}

int main() {
  testMatrixValues();
}