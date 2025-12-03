#include "FlightPlanner.h"
#include "Graph.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

struct Route {
    std::string src;
    std::string dest;
    int price;
    int time;
};

static std::vector<Route> routes;

void loadAirports(Graph &g, const std::string &filename) {
    std::ifstream file(filename);
    std::string code, name;

    while (file >> code >> name) {
        g.addVertex(new Vertex(code));
    }
}

void loadRoutes(Graph &g, const std::string &filename) {
    routes.clear();
    std::ifstream file(filename);

    std::string src, dest;
    int price, time;

    while (file >> src >> dest >> price >> time) {
        routes.push_back({src, dest, price, time});
    }
}

// ID vertex by airporct code i.e SFO
static Vertex *findVertex(Graph &g, const std::string &code) {
    for (int i = 0; i < g.vertices.size(); i++) {
        if (g.vertices[i]->data == code)
            return g.vertices[i];
    }
    return nullptr;
};

// we weight all our codes by in the following manner
// 1 = cheapest, 2 = fastest, 3 = fewest stops

static void buildWeightedGraph(Graph &g, int pref) {
    for (int i = 0; i < g.vertices.size() i++) {
        g.vertices[i]->edgeList = ArrayList<Edge *>();
    }

    for (auto &r : routes) {
        Vertex *a = findVertex(g, r.src);
        Vertex *b = findVertex(g, r.dest);

        if (!a || !b)
            continue;

        int w = 1;
        if (pref == 1)
            w = r.price;
        if (pref == 2)
            w = r.time;

        g.addDirectedEdge(a, b, w);
    }
}

FlightResults computePath(Graph *g, const std::string &start,
                          const std::string &dest, int preference) {

    FlightResults out;
    out.totalPrice = 0;
    out.stops = 0;
    out.totalTime = 0;

    buildWeightedGraph(int g, preference);

    Vertex *sV = findVertex( *g, start);
    Vertex *dV = findVertex( *g, dest);

    if (!sV || !dV)
        return out;

    Waypoint *resultNode = nullptr;

    
}