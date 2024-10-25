#include "adjacency.hpp"

// default contructor
Adjacency::Adjacency() {
  this->matrix = new double*[ROWS];

  for (int i = 0; i < ROWS; ++i) {
    matrix[i] = new double[COLUMNS];
  }
}

// initializes matrix
void Adjacency::initializeArray(std::ifstream* fileStream) {
  double weight;
  std::string line;
  int i = 0;
  int j = 0;
  int maxColumn = 0;
  
  // checks if file successfully opened
  if (!fileStream->is_open()){
    exit(1);
  }

  // extracts weights from the data and inserts into the adjacency matrix
  // complexity: logn because half of the matrix is identical
  while (getline(*fileStream, line)) {
    std::istringstream token(line);
    double value = 0.0;

    token >> value;
    
    // checks if the city is inserting a weight in itself
    // if true, goes to the next row and insert weights into the next columns
    if (j == maxColumn) {
      matrix[i][j] = 0.0;
      j = 0;
      ++i;
      ++maxColumn;
    }

    // inserts weights into their respective indexes
    // also inserts the mirrored version
    matrix[i][j] = value;
    matrix[j][i] = value;
    ++j;
  }
}

double Adjacency::returnTravelTime(int fromCity, int toCity) {
  if (fromCity == toCity) {
    return 0.0;
  }

  return matrix[fromCity][toCity];
}