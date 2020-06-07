/****************************************************************
  * File: Simple_window.cpp
  * Description: Implements Simple_window.h - base window class to show experiments results
  * Author: Fabio Andreozzi Godoy
  * Date: 2020-06-06 - Modified: 2020-06-06
  */

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

