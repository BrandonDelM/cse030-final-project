#include "FlightPlanner.h"
#include "Graph.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>


struct Route {
    std::string src;
    std::string dest;
    int price;
    int time;
};

static ArrayList<Route>;

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
        Route r;
        r.src = src;
        r.dest = dest;
        r.price = price;
        r.time = time;
        routes.append(r);
    }
}

// ID vertex by airporct code i.e SFO
static Vertex *findVertex(Graph &g, const std::string &code) {
    for (int i = 0; i < g.vertices.size(); i++) {
        if (g.vertices[i]->data == code)
            return g.vertices[i];
    }
    return nullptr;
}

// we weight all our codes by in the following manner
// 1 = cheapest, 2 = fastest, 3 = fewest stops

static void buildWeightedGraph(Graph &g, int pref) {
    for (int i = 0; i < g.vertices.size(); i++) {
        g.vertices[i]->edgeList.clear();
    }
    for (int i = 0; i < routes.size(); i++) {
        Route &r = routes[i];

        Vertex *a = findVertex(g, r.src);
        Vertex *b = findVertex(g, r.dest);

        if (!a || !b) continue;

        int w = 1;
        if (pref == 1)
            w = r.price;
        if (pref == 2)
            w = r.time;

        g.addDirectedEdge(a, b, w);
    }
}

static std::vector<std::string> buildPath(Waypoint *end) {
    std::vector<std::string> path;

    while (end != nullptr) {
        path.push_back(end->vertex->data);
        end = end->parent;
    }

    std::reverse(path.begin(), path.end());
    return path;
}

FlightResults computePath(Graph &g, const std::string &start,
                          const std::string &dest, int preference) {
    FlightResults out;
    out.totalPrice = 0;
    out.stops = 0;
    out.totalTime = 0;

    buildWeightedGraph(g, preference);
    ///sV (stariting vecotor)
    ///dV (destination vector)
    Vertex *sV = findVertex(g, start);
    Vertex *dV = findVertex(g, dest);

    if (!sV || !dV)
        return out;

    Waypoint *resultNode = nullptr;

    std::cout << "\n debug " << g.vertices.size() << "\n";
    for (int i = 0; i < g.vertices.size(); i++)
        std::cout << " - " << g.vertices[i]->data << "\n";
    std::cout << "\n debug loaded routes: " << routes.size() << "\n";
    if (preference == 3) {
        resultNode = g.bfs(sV, dV);

    } else {
        resultNode = g.ucs(sV, dV);
    }

    if (!resultNode)
        return out;
    // pathing
    out.path = buildPath(resultNode);
    out.stops = out.path.size() - 1;

    for (int i = 0; i < out.path.size() - 1; i++) {
        std::string a = out.path[i];
        std::string b = out.path[i + 1];

        for (auto &r : routes) {
            if (r.src == a && r.dest == b) {
                out.totalPrice += r.price;
                out.totalTime += r.time;
            }
        }
    }

    return out;
}
