#include "GA.hpp"

// default constructo
GA::GA(int initialTours, int generations, int mutationPercentage, int cities) {
  this->initialTours = initialTours;
  this->generations = generations;
  this->cities = cities;
  this->totalTimeTraveled = 0.0;

  // convert percentage to a number
  double percent = static_cast<double>(mutationPercentage);
  percent = percent / 100;
  this->mutationPercentage = initialTours * percent;

  // random number generator
  std::random_device rd;
  this->rng = std::mt19937(rd());
}

// intializes tours
void GA::initializeTours() {
  for (int i = 0; i < initialTours; ++i) {
    tours.push_back(this->generateTour());
  }
}

// generates a single tour
std::vector<int> GA::generateTour() {
  std::vector<int> tour(cities);

  // initialize tour
  for (int i = 0; i < cities; ++i) {
    tour[i] = i;
  }

  // shuffles tour randomly
  std::shuffle(tour.begin() + 1, tour.end(), rng);
  return tour;
}

// calculates tour distance
double GA::tourDistance(Adjacency& matrix) {
  double travelTime = 0.0;

  // gets the tour distnace
  for (int i = 0; i < path.size() - 1; +i) {
    travelTime += matrix.returnTravelTime(path[i], path[i + 1]);
  }

  travelTime += matrix.returnTravelTime(path[path.size() - 1], path[0]);

  return travelTime;
}

// takes the shortest path 
std::string GA::getShortestPath(Adjacency& matrix) {
  this->initializeTours();
  path.clear();
  minPath = std::numeric_limits<double>::max();
  std::vector<int> eliteTour;

  // algorithm for genetic algorithm
  while(generationCounter < generations) {
    // initializes elite tour
    if (!path.empty()) {
      eliteTour = path;
      tours[0] = eliteTour;
    }

    for (int i = 0; i < tours.size(); ++i) {
      int m = cities - 2;
      while (m >= 0 && tours[i][m] >= tours[i][m + 1]) {
       --m;
      }

      if (m < 0) {
        continue;
      }

      int k = cities - 1;
      while (tours[i][m] >= tours[i][k]) {
        --k;
      }

      std::swap(tours[i][m], tours[i][k]);
      std::reverse(tours[i].begin() + m + 1, tours[i].end());

      // calcluate distance for this tour
      path = tours[i];
      double currentTravelTime = tourDistance(matrix);

      if (currentTravelTime < minPath) {
        minPath = currentTravelTime;
        path = tours[i];
        totalTimeTraveled = currentTravelTime;
      }
    }
      this->mutate();
      
      if (!eliteTour.empty()) {
        tours[0] = eliteTour;
      }
      ++generationCounter;
  }
  
  // returns shortest path
  std::string shortestPath;
  for (int i = 0; i < path.size(); ++i) {
    shortestPath += std::to_string(path[i]) + " ";
  }

  shortestPath += std::to_string(path[0]);
  return shortestPath;
}

// mutates a percentage of the generation
void GA::mutate() {
  std::uniform_int_distribution<int> dist(1, cities - 1);

  for (int i = 0; i < int(mutationPercentage); ++i) {
    int randomIndex1 = dist(rng);
    int randomIndex2 = dist(rng);

    std::swap(tours[randomIndex1], tours[randomIndex2]);
  }
}

// keeps track of the time elapsed
void GA::timer(std::atomic<bool>& running) {
  auto start = std::chrono::high_resolution_clock::now();

  while (running) {
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = now - start;

    // clear previous output and print elapsed time
    std::cout << "\33[2k\rElapsed time: " << std::fixed << std::setprecision(2) << elapsed.count() << " seconds" << std::flush;

    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> totalElapsed = end - start;

  std::cout << std::endl << "\33[2k\rTotal Executation Time: " << totalElapsed.count() << " seconds" << std::endl << std::endl;
}