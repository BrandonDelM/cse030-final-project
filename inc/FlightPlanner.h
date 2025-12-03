#ifndef FLIGHTPLANNER_H
#define FLIGHTPLANNER_H

#include "Graph.h"
#include <string>
#include <vector>

struct FlightResults {
    std::vector<std::string> path;
    double totalPrice;
    double totalTime;
    int stops;
};

struct RouteRecord {
    std::string src;
    std::string dest;
    double price;
    double time;
    std::string routes;
};

void loadAirports(Graph &g, const std::string &filename);
void loadRoutes(Graph &g, const std::string &filename);

FlightResults computePath(Graph &g, const std::string &start,
                          const std::string &dest, int preference);

#endif
