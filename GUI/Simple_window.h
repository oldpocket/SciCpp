//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#ifndef SIMPLE_WINDOW
#define SIMPLE_WINDOW 1

#include <string>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

using std::string;

namespace GUI {

//------------------------------------------------------------------------------

class Simple_window : public Fl_Window {
public:
    Simple_window(int w, int h, const string& title );
    ~Simple_window();

private:

};

}
//------------------------------------------------------------------------------

#endif // SIMPLE_WINDOW_GUARD
