#ifndef GRAPH_VISUALIZATION_H
#define GRAPH_VISUALIZATION_H

#include "ArrayList.h"
#include "Graph.h"

struct Node_Visualization {
    int x, y;
    Vertex *node;
    bool selected;
};

class Graph_Visualization {
    static constexpr float REPULSION_FORCE = 1;
    static constexpr float ATTRACTION_FORCE = 2;
    static constexpr float LOGRITHMIC_FALLOFF = 25;
    const Graph *g;
    void drawVertex(int x, int y);
    void drawEdge(int x1, int y1, int x2, int y2);
    void init_nodes();
    void iteration();
    float DistanceBetweenPointsHelper(const float x1, const float y1,
                                      const float x2, const float y2);

public:
    Graph_Visualization(Graph* const g);
    ArrayList<Node_Visualization *> nodes;
};

#endif