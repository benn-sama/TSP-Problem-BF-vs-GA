#include "GA.hpp"

GA::GA(int initialTours, int generations, int mutationPercentage, int cities) {
    this->initialTours = initialTours;
    this->generations = generations;
    this->cities = cities;
    this->totalTimeTraveled = 0.0;
    this->generationCounter = 0;

    // convert percentage to number of mutations
    this->mutationPercentage = static_cast<int>(initialTours * (mutationPercentage / 100.0));

    // initialize random number generator
    std::random_device rd;
    this->rng = std::mt19937(rd());
}

void GA::initializeTours() {
    tours.clear();
    tours.reserve(initialTours);
    
    // generate initial population of tours
    for (int i = 0; i < initialTours; ++i) {
        tours.push_back(generateTour());
    }
}

std::vector<int> GA::generateTour() {
    std::vector<int> tour(cities);
    for (int i = 0; i < cities; ++i) {
        tour[i] = i;
    }
    // keep first city fixed, then shuffle rest
    std::shuffle(tour.begin() + 1, tour.end(), rng);
    return tour;
}

double GA::tourDistance(Adjacency& matrix) {
    double distance = 0.0;
    
    // calculate tour distance including return to start
    for (int i = 0; i < cities - 1; ++i) {
        distance += matrix.returnTravelTime(path[i], path[i + 1]);
    }
    distance += matrix.returnTravelTime(path[cities - 1], path[0]);
    
    return distance;
}

void GA::evaluateTours(Adjacency& matrix) {
    double bestDistance = std::numeric_limits<double>::max();
    int bestTourIndex = 0;

    for (int i = 0; i < tours.size(); ++i) {
        path = tours[i];
        double currentDistance = tourDistance(matrix);
        
        if (currentDistance < bestDistance) {
            bestDistance = currentDistance;
            bestTourIndex = i;
            totalTimeTraveled = currentDistance;
        }
    }

    // store the best tour
    path = tours[bestTourIndex];
    minPath = bestDistance;
}

void GA::mutate() {
    std::uniform_int_distribution<int> tourDist(1, tours.size() - 1); // skip elite tour

    // perform mutations
    for (int i = 0; i < mutationPercentage; ++i) {
        int tourIndex = tourDist(rng);
        
        int m = cities - 2;
        while (m >= 1 && tours[tourIndex][m] > tours[tourIndex][m + 1]) {
            m = m - 1;
        }
        
        int k = cities - 1;
        while (m >= 1 && tours[tourIndex][m] > tours[tourIndex][k]) {
            k = k - 1;
        }
        
        if (m >= 1) {
            std::swap(tours[tourIndex][m], tours[tourIndex][k]);
            
            int p = m + 1;
            int q = cities - 1;
            while (p < q) {
                std::swap(tours[tourIndex][p], tours[tourIndex][q]);
                ++q;
                --p;
            }
        }
    }
}

std::string GA::getShortestPath(Adjacency& matrix, std::atomic<bool>& running) {
    initializeTours();
    path.clear();
    minPath = std::numeric_limits<double>::max();
    std::vector<int> eliteTour;
    generationCounter = 0;

    while (generationCounter < generations && running) {
        // evaluate current generation
        evaluateTours(matrix);
        
        // store elite tour
        eliteTour = path;
        
        // create next generation
        mutate();
        
        // preserve elite tour
        tours[0] = eliteTour;
        
        ++generationCounter;
    }
    
    // format result path
    std::string result;
    for (int city : path) {
        result += std::to_string(city) + " ";
    }
    result += std::to_string(path[0]); // add return to start
    
    running = false;
    return result;
}

// keeps track of time
void GA::timer(std::atomic<bool>& running) {
    auto start = std::chrono::high_resolution_clock::now();
    
    while (running) {
        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration<double>(now - start);
        
        std::cout << "\33[2K\rElapsed time: " << std::fixed 
                 << std::setprecision(2) << elapsed.count() 
                 << " seconds" << std::flush;
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto totalElapsed = std::chrono::duration<double>(end - start);
    
    std::cout << std::endl << "\33[2K\rTotal Execution Time: " 
              << totalElapsed.count() << " seconds" << std::endl << std::endl;
}

double GA::getTimeTraveled() {
    return totalTimeTraveled;
}