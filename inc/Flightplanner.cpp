#include "../inc/Flightplanner.h"
#include "../inc/Graph.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

struct RouteRecord {
    std::string src;
    std::string dest;
    double price;
    double time;
    std::string routes;
};

static std::vector<RouteRecord> routes;

void loadAirports(Graph &g, const std::string &filename) {
    std::ifstream file(filename);
    std::string code, name;

    while (file >> code >> name) {
        g.addVertex(code);
    }
}

void loadRoutes(Graph &g, const std::string &filename) {
    routes.clear();
    std::ifstream file(filename);

    std::string src, dest;
    double price, time;

    while (file >> src >> dest >> price >> time) {
        routes.push_back({src, dest, price, time});
    }
}

/// DIJKSTRA

static std::vector<std::string> dijkstra(Graph &g, const std::string &start,
                                         const std::string &goal,
                                         bool usePrice) {
    std::unordered_map<std::string, double> dist;
}