#ifndef APPLICATION_H
#define APPLICATION_H

#include "GraphVisCanvas.h"
#include <bobcat_ui/bobcat_ui.h>
#include <bobcat_ui/window.h>
#include <bobcat_ui/dropdown.h>
#include <bobcat_ui/textbox.h>
#include <bobcat_ui/button.h>
#include <FL/Fl_Scroll.H>

using namespace bobcat;

class Application : public bobcat::Application_ {

    Window* window;
    Dropdown* from_dropdown; //Where you're starting from
    Dropdown* to_dropdown; //Where you want to go
    Dropdown* preference_dropdown; //1 2 3
    TextBox* arrow_text; //Arrow between from and to
    Button* findpath_button; //Run the code to find the route
    Fl_Scroll* path_scroll; //Shows the route
    TextBox* stats_textbox; //Statistics for the route
    GraphVisCanvas* canvas;

    public:
    Application();
    void handleClick(bobcat::Widget* sender);

};
#endif