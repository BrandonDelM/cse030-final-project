#include "GraphVisualization.h"
#include "ArrayList.h"
#include "Graph.h"
#include <cmath>
#include <math.h>

Graph_Visualization::Graph_Visualization(Graph *const input_graph) {
    g = input_graph;
    init_nodes();
    for (int i = 0; i < 15; i++) {
        // iteration();
    }
}
void Graph_Visualization::init_nodes() {
    int x_cursor, y_cursor = 0;
    for (int i = 0; i < g->vertices.size(); i++) {
        Node_Visualization *new_node_vizualization = new Node_Visualization();
        new_node_vizualization->x = x_cursor;
        new_node_vizualization->y = y_cursor;
        this->nodes.append(new_node_vizualization);
        x_cursor += 100;
        if (x_cursor >= 1500) {
            x_cursor = 0;
            y_cursor += 100;
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
    delete [] forcex,forcey;
}