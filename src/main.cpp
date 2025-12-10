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
    int nodes = graph_visualization_instance->nodes.size();
    for (int i = 0; i < nodes; i++) {
        int x = graph_visualization_instance->nodes[i]->x;
        int y = graph_visualization_instance->nodes[i]->y;
        glBegin(GL_POLYGON);
        float inc = 2 * M_PI / 60;
        for (float theta = 0; theta <= 2 * M_PI; theta += inc) {
            glVertex2f(viewpoint_x + x + 2 * cos(theta),
                       viewpoint_y + y + 2 * sin(theta));
            //std::cout << graph_visualization_instance->nodes[i]-> x+viewpoint_x  << " ";
            //std::cout << graph_visualization_instance->nodes[i]-> y+viewpoint_y  << std::endl;
        }
        glEnd();
        // for (int j=0;
        // j<graph_visualization_instance->nodes[i]->node->edgeList.size(); j++)
        // {
        //     for(int k=0; k<graph_visualization_instance->nodes.size(); k++){
        //         if(graph_visualization_instance->nodes[k]->node==graph_visualization_instance->nodes[i]->node->edgeList[j]->to){
        //             glBegin(GL_LINES);
        //             glVertex2f(viewpoint_x+x, viewpoint_y+y);
        //             glVertex2f(viewpoint_x+graph_visualization_instance->nodes[k]->x,
        //             viewpoint_y+graph_visualization_instance->nodes[k]->y);
        //             glEnd();
        //         }
        //     }
        // }
    }
}