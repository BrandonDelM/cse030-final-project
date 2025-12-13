#include "Application.h"
#include "FlightPlanner.h"
#include <ArrayList.h>
#include <FL/Enumerations.H>
#include <bobcat_ui/bobcat_ui.h>
#include <bobcat_ui/dropdown.h>
#include <bobcat_ui/textbox.h>
#include <bobcat_ui/window.h>

using namespace bobcat;
using namespace std;

std::string intToPrice(int price) { return "$" + roundFloat(price); }

std::string intToTime(int time) { return roundFloat(time, 0) + " Hrs"; }

Application::Application() {
    window = new Window(100, 100, 400, 400, "Flight Tracker");
    from_dropdown = new Dropdown(50, 25, 100, 25, "From");
    to_dropdown = new Dropdown(250, 25, 100, 25, "To");
    arrow_text = new TextBox(175, 25, 50, 25, "------->");
    preference_dropdown = new Dropdown(50, 75, 300, 25, "Path Preference");
    findpath_button = new Button(50, 125, 300, 25, "Find Path");
    stats_textbox = new TextBox(50, 150, 300, 50, "");
    path_scroll = new Fl_Scroll(50, 225, 300, 150, "Path Route");

    ArrayList<std::string> airports = add_Airports("data/airports.txt");
    for (int i = 0; i < airports.size(); i++) {
        from_dropdown->add(airports[i]);
        to_dropdown->add(airports[i]);
    }

    preference_dropdown->add("Cheapest price");
    preference_dropdown->add("Shortest travel time");
    preference_dropdown->add("Least number of stops");

    path_scroll->align(FL_ALIGN_TOP_LEFT);
    path_scroll->box(FL_THIN_UP_BOX);

    ON_CLICK(findpath_button, Application::handleClick);

    window->show();
}

void Application::handleClick(bobcat::Widget *sender) {
    Graph g;

    loadAirports(g, "data/airports.txt");
    loadRoutes(g, "data/routes.txt");

    std::string start = from_dropdown->text();
    std::string dest = to_dropdown->text();

    path_scroll->clear();
    stats_textbox->label("");

    int pref = preference_dropdown->value() + 1;
    FlightResults result = computePath(g, start, dest, pref);
    if (result.path.size() != 0) {
        for (int i = 0; i < result.path.size(); i++) {
            path_scroll->add(
                new TextBox(40, 225 + (40 * i), 300, 25, result.path[i]));
        }
        std::string statistics =
            "Total Price: " + intToPrice(result.totalPrice) + "\n";
        statistics += "Total Time: " + intToTime(result.totalTime) + "\n";
        statistics += "Total Stops: " + to_string(result.stops) + "\n";
        stats_textbox->label(statistics);
    } else {
        path_scroll->add(new TextBox(40, 225, 300, 25, "No path found"));
    }
    window->redraw();
}