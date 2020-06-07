/****************************************************************
  * File: Simple_window.h
  * Description: Base class to show a window with the results of the experiment
  * Author: Fabio Andreozzi Godoy
  * Date: 2020-06-06 - Modified: 2020-06-06
  */

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
