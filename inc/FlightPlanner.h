#ifndef FLIGHTPLANNER_H
#define FLIGHTPLANNER_H

#include "Graph.h"
#include <ArrayList.h>

struct FlightResults {
    ArrayList<std::string> path;
    double totalPrice;
    double totalTime;
    int stops;
};

    void loadAirports(Graph &g, const std::string &filename);
    void loadRoutes(Graph &g, const std::string &filename);
    ArrayList<std::string> add_Airports(const std::string &filename);

    FlightResults computePath(Graph &g, const std::string &start, const std::string &dest, int preference);

#endif
