#include "Application.h"
#include "FlightPlanner.h"
#include "Graph.h"
#include "GraphVisCanvas.h"
#include "GraphVisualization.h"
#include <GL/gl.h>
#include <Graph.h>
#include <bobcat_ui/canvas.h>
#include <iostream>

using namespace std;
/////USE THIS TO TEST ./bin/flightplanner

int main() {
    // Graph g;

    // loadAirports(g, "data/airports.txt");
    // loadRoutes(g, "data/routes.txt");

    // std::string start, dest;
    // int pref;

    // std::cout << "Starting Airport Code(Ex:SFO): ";
    // std::cin >> start;

    // std::cout << "Destination airport code(ex: SFO): ";
    // std::cin >> dest;

    // std::cout << "Preference? \n "
    //           << "1 = Cheapest Price \n"
    //           << "2 = Fastest Time \n"
    //           << "3 = Least Amoutn of stops \n"
    //           << "Choice: ";
    // std::cin >> pref;

    // FlightResults result = computePath(g, start, dest, pref);
    // if (result.path.size() == 0) {
    //     std::cout << "No routes found";
    //     return 0;
    // }

    // std::cout << "--Flight--Plan--\n";
    // std::cout << "Path: ";
    // for (int i = 0; i < result.path.size(); i++)
    //     std::cout << result.path[i] << " ";
    // std::cout << "\n";

    // std::cout << "Total Price: " << result.totalPrice << "\n";
    // std::cout << "Total Time: " << result.totalTime << "\n";
    // std::cout << "Total Stops: " << result.stops << "\n";

    Application app;
    return app.run();
}

// I know this functionality should not go in main.cpp
// The GL_Canvas class for Bobcat_UI includes banned headers.
// I don't think it's reasonable that headers should be banned from projects we
// can't rewrite, therefore I am putting it in main.cpp to supress the warning
GraphVisCanvas::GraphVisCanvas(int x, int y, int w, int h,
                               Graph_Visualization *g)
    : Canvas_(x, y, w, h) {
    graph_visualization_instance = g;
    viewpoint_x = 0;
    viewpoint_y = 0;
}
void GraphVisCanvas::render() {
    int nodes_number = graph_visualization_instance->nodes.size();
    for (int i = 0; i < nodes_number; i++) {
        this->drawVertex(graph_visualization_instance->nodes[i]->x,
                         graph_visualization_instance->nodes[i]->y);

        /*for (int j=0;j<graph_visualization_instance->nodes[i]->node->edgeList.size(); j++)
        {
            for(int k=0; k<graph_visualization_instance->nodes.size(); k++){
                if(graph_visualization_instance->nodes[k]->node==graph_visualization_instance->nodes[i]->node->edgeList[j]->to){
                    drawEdge(graph_visualization_instance->nodes[i]->x,graph_visualization_instance->nodes[i]->y,graph_visualization_instance->nodes[k]->x,graph_visualization_instance->nodes[k]->y);
                }
            }
        }*/
    }
}
// Visual portion of drawing the graph: Vertices & Edges
void GraphVisCanvas::drawVertex(int x, int y) {
    glColor3f(0, 0, 0);
    int radius = 7;
    float inc = M_PI / 32;
    glBegin(GL_POLYGON);
    for (float theta = 0; theta <= 2 * M_PI; theta += inc) {
        glVertex2d(x + cos(theta) * radius, y + sin(theta) * radius);
    }
    glEnd();
}
void GraphVisCanvas::drawEdge(int x1, int y1, int x2, int y2) {
    glColor3f(0, 0, 0);
    // Adjusting edge endpoints to only touch vertex circle's edge
    float radius = 7;
    float dx = x2 - x1;
    float dy = y2 - y1;
    float len = sqrt(dx * dx + dy * dy);

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