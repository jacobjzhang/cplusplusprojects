/**********************************************************************
 *
 * Project 6: Extending the GUI
 *
 * The Square.cc file in project 6 is the source code file for our
 * class and includes the definitions for its member functions.
 * 
 * Author: Jacob J. Zhang
 * Date:   August 20, 2015
 *
 **********************************************************************/

#include "Square.h"

void Square::draw_lines() const
{

    // Draw the lines for the Square and set initial color
    if (fill_color().visibility()) {
	fl_color(fill_color().as_int());
	fl_rectf(point(0).x,point(0).y, l, l);
	fl_color(color().as_int());
    }

    // To change the fill color of the Square
    if (color().visibility()) {
	fl_color(color().as_int());
	fl_rect(point(0).x,point(0).y, l, l);
    }

}
