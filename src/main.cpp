#include "FlightPlanner.h"
#include "Graph.h"
#include <Graph.h>
#include <iostream>

using namespace std;
/////USE THIS TO TEST ./bin/flightplanner

int main() {
    Graph g;

    loadAirports(g, "data/airports.txt");
    loadRoutes(g, "data/routes.txt");

    std::string start, dest;
    int pref;

    std::cout << "Starting Airport Code(Ex:SFO): ";
    std::cin >> start;

    std::cout << "Destination airport code(ex: SFO): ";
    std::cin >> dest;

    std::cout << "Preference? \n "
              << "1 = Cheapest Price \n"
              << "2 = Fastest Time \n"
              << "3 = Least Amoutn of stops \n"
              << "Choice: ";
    std::cin >> pref;

    FlightResults result = computePath(g, start, dest, pref);
    if (result.path.size() == 0) {
        std::cout << "No routes found";
        return 0;
    }

    std::cout << "--Flight--Plan--\n";
    std::cout << "Path: ";
    for (int i = 0; i < result.path.size(); i++)
        std::cout << result.path[i] << " ";
    std::cout << "\n";

    std::cout << "Total Price: " << result.totalPrice << "\n";
    std::cout << "Total Time: " << result.totalTime << "\n";
    std::cout << "Total Stops: " << result.stops << "\n";
}