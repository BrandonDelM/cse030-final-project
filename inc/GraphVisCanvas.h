#ifndef GRAPH_VIS_CANVAS_H
#define GRAPH_VIS_CANVAS_H

#include "GraphVisualization.h"
#include <bobcat_ui/canvas.h>

class GraphVisCanvas : public bobcat::Canvas_ {
public:
    int viewpoint_x, viewpoint_y;
    Graph_Visualization *graph_visualization_instance;
    GraphVisCanvas(int x, int y, int w, int h, Graph_Visualization *g);
    void render();
};

#endif