#include "BF.hpp"

BF::BF() {}

// finds shortest path
std::string BF::getShortestPath(Adjacency& matrix, int cities, std::atomic<bool>& running) {
    // initialize path with cities in orders
    path.clear();
    for (int i = 1; i <= cities; ++i) {
        path.push_back(i);
    }
    
    minPath = std::numeric_limits<double>::max();
    totalTimeTraveled = 0.0;
    
    while (running) {
        // find position m where path[m] < path[m+1]
        int m = cities - 2;
        while (m >= 0 && path[m] > path[m + 1]) {
            --m;
        }
        
        // if no such position found, we've tried all permutations
        if (m < 0) {
          break;
        }
        
        // find position k where path[k] > path[m]
        int k = cities - 1;
        while (path[m] > path[k]) {
            --k;
        }
        
        // swap elements at positions m and k
        std::swap(path[m], path[k]);
        
        // reverse the sequence from position m+1 to end
        int p = m + 1;
        int q = cities - 1;
        while(p < q) {
            std::swap(path[p], path[q]);
            ++p;
            --q;
        }
        
        // calculate total travel time for this path
        double currentTime = 0;
        for(int i = 0; i < cities - 1; i++) {
            currentTime += matrix.returnTravelTime(path[i] - 1, path[i + 1] - 1);
        }
        currentTime += matrix.returnTravelTime(path[cities-  1] - 1, path[0] - 1); // Return to start
        
        // update if this is the shortest path found
        if (currentTime < minPath) {
            minPath = currentTime;
            totalTimeTraveled = currentTime;
        }
    }
    
    // convert final path to string
    std::string result;
    for(int city : path) {
        result += std::to_string(city) + " ";
    }
    result += std::to_string(path[0]); // return to start
    
    running = false;
    return result;
}

// elapsed time
void BF::timer(std::atomic<bool>& running) {
  auto start = std::chrono::high_resolution_clock::now();

  while (running) {
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = now - start;

    // clear previous output and print elapsed time
    std::cout << "\33[2k\rElapsed time: " << std::fixed << std::setprecision(2) << elapsed.count() << " seconds" << std::flush;

    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  auto end = std::chrono::high_resolution_clock::now();
  std:: chrono::duration<double> totalElapsed = end - start;

  std::cout << "\33[2k\rTotal Execution Time: " << totalElapsed.count() << " seconds" << std::endl;
}

double BF::getTotalTimeTraveled() {
    return this->totalTimeTraveled;
}