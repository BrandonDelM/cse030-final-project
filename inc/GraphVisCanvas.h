#ifndef GRAPH_VIS_CANVAS_H
#define GRAPH_VIS_CANVAS_H

#include <bobcat_ui/canvas.h>

class GraphVisCanvas:public bobcat::Canvas_{
    public:
    GraphVisCanvas(int x, int y, int w, int h);
    void render();
};



#endif