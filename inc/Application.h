#ifndef APPLICATION_H
#define APPLICATION_H

#include "GraphVisCanvas.h"
#include <bobcat_ui/bobcat_ui.h>
#include <bobcat_ui/window.h>

class Application : public bobcat::Application_ {

bobcat::Window* window;
Canvas* main_Canvas;

public:
Application();

};
#endif