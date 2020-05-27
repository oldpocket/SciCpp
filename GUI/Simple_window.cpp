
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "Simple_window.h"

//------------------------------------------------------------------------------

GUI::Simple_window::Simple_window(int w, int h, const string& title) :
    Fl_Window(w, h, title.c_str())
{
}

GUI::Simple_window::~Simple_window()
{
}

//------------------------------------------------------------------------------

