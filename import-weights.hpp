#ifndef IMPORT_WEIGHTS_HPP
#define IMPORT_WEIGHTS_HPP

#include <sstream>
#include <fstream>
#include <vector>

class Import {
  private:
    std::istringstream iss;
    std::ifstream      inFile;
  public:
    Import(std::vector<std::pair<int, double>>*); // constructor
};

#endif