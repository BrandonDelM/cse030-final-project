#include "GraphVisualization.h"
#include "ArrayList.h"
#include "Graph.h"
#include <cmath>
#include <iostream>
#include <math.h>
#include <GL/gl.h>
#include <bobcat_ui/canvas.h>

// Visual portion of drawing the graph: Vertices & Edges
void Graph_Visualization::drawVertex(int x, int y) {
    glColor3f(0, 0, 0);
    int radius = 7;
    float inc = M_PI / 32;
    glBegin(GL_POLYGON);
        for (float theta = 0; theta <= 2 * M_PI; theta += inc){
            glVertex2d(x + cos(theta) * radius, y + sin(theta) * radius);
        }
    glEnd();
}
void Graph_Visualization::drawEdge(int x1, int y1, int x2, int y2) {
    glColor3f(0,0,0);
    // Adjusting edge endpoints to only touch vertex circle's edge
    float radius = 7;
    float dx = x2 - x1;
    float dy = y2 - y1;
    float len = sqrt(dx*dx + dy*dy);

    float nx = dx / len;
    float ny = dy / len;

    float x1_adj = x1 - nx * radius;
    float y1_adj = y1 - ny * radius;
    float x2_adj = x2 - nx * radius;
    float y2_adj = y2 - ny * radius;

    glBegin(GL_LINES);
        glVertex2f(x1_adj, y1_adj);
        glVertex2f(x2_adj, y2_adj);
    glEnd();
}

Graph_Visualization::Graph_Visualization(Graph *const input_graph) {
    g = input_graph;
    init_nodes();
    for (int i = 0; i < 15; i++) {
        // iteration();
    }
    for (int i =0; i<nodes.size(); i++) {
        
    }
}
void Graph_Visualization::init_nodes() {
    int x_cursor = 0;
    int y_cursor = 0;
    for (int i = 0; i < g->vertices.size(); i++) {
        Node_Visualization *new_node_vizualization = new Node_Visualization();
        new_node_vizualization->x = x_cursor;
        new_node_vizualization->y = y_cursor;
        this->nodes.append(new_node_vizualization);
        x_cursor += 50;
        if (x_cursor >= 400) {
            x_cursor = 0;
            y_cursor += 50;
        }
    }
}
float Graph_Visualization::DistanceBetweenPointsHelper(const float x1,
                                                       const float y1,
                                                       const float x2,
                                                       const float y2) {
    return sqrt(powf(x2 - x1, 2) + powf(y2 - y1, 2));
}
void Graph_Visualization::iteration() {
    float *forcex = new float[nodes.size()];
    float *forcey = new float[nodes.size()];
    for (int i = 0; i < nodes.size(); i++) {
        //Can be optimized because the forces are compliments of each other
        Node_Visualization node = *nodes[i];
        // Repulsion
        for (int j = 0; j < nodes.size(); j++) {
            if (i == j) {
                continue;
            }
            forcex[i]=forcex[i]+(REPULSION_FORCE*(log(node.x-nodes[j]->x)/log(LOGRITHMIC_FALLOFF)));
            forcey[i]=forcey[i]+(REPULSION_FORCE*(log(node.y-nodes[j]->y)/log(LOGRITHMIC_FALLOFF)));
        }
        // Attraction
        // Get Verticies
        for (int j=0; j<node.node->edgeList.size(); j++) {
            for(int k=0; k<nodes.size(); k++){
                if(nodes[k]->node==node.node->edgeList[j]->to){
                    forcex[i]=forcex[i]-(ATTRACTION_FORCE*(log(node.x-nodes[k]->x)/log(LOGRITHMIC_FALLOFF)));
                    forcey[i]=forcey[i]-(ATTRACTION_FORCE*(log(node.y-nodes[k]->y)/log(LOGRITHMIC_FALLOFF)));
                }
            }
        }
    }
    for(int i=0; i<nodes.size(); i++){
        nodes[i]->x+=forcex[i];
        nodes[i]->y+=forcey[i];
    }
    delete [] forcex;
    delete [] forcey;
}