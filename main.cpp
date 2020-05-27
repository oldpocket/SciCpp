#include "GUI/Simple_window.h"

int main() {
    GUI::Simple_window win {640,480,"An empty window"};
    win.show();
    return Fl::run();
    //win.wait_for_button();
}
