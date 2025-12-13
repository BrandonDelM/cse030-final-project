#ifndef GRAPH_VIS_CANVAS_H
#define GRAPH_VIS_CANVAS_H

#include "GraphVisualization.h"
#include <bobcat_ui/canvas.h>

class GraphVisCanvas : public bobcat::Canvas_ {
public:
    void drawVertex(int x, int y);
    void drawEdge(int x1, int y1, int x2, int y2);
    int viewpoint_x, viewpoint_y;
    Graph_Visualization *graph_visualization_instance;
    GraphVisCanvas(int x, int y, int w, int h, Graph_Visualization *g);
    void render();
};

#endif