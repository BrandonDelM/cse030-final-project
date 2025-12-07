#include "Application.h"
#include <FL/Enumerations.H>
#include <bobcat_ui/dropdown.h>
#include <bobcat_ui/textbox.h>
#include <bobcat_ui/window.h>
#include <ArrayList.h>
#include "FlightPlanner.h"

using namespace bobcat;
using namespace std;

Application::Application(){
    window = new Window(100,100, 400, 400,"Flight Tracker");
    from_dropdown = new Dropdown(50, 25, 100, 25, "From");
    to_dropdown = new Dropdown(250, 25, 100, 25, "To");
    arrow_text = new TextBox(175, 25, 50, 25, "------->");
    preference_dropdown = new Dropdown(50, 75, 300, 25, "Path Preference");
    findpath_button = new Button(50, 125, 300, 25, "Find Path");
    stats_textbox = new TextBox(50, 150, 300, 50, "help");
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

    window->show();
}