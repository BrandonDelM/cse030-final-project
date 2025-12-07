#include "Application.h"
#include "GraphVisCanvas.h"
#include <bobcat_ui/window.h>

Application::Application(){
    window = new bobcat::Window(800,800,"Flight Tracker");
    main_Canvas = new Canvas(0,0,800, 400);
    
}