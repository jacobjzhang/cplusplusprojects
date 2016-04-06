/**********************************************************************
 *
 * Project 6: Extending the GUI
 *
 * Our sixth programming project extends the GUI and adds a Square
 * class for the creation and utilization of square shapes.
 * 
 * Author: Jacob J. Zhang
 * Date:   August 20, 2015
 *
 **********************************************************************/

#include "Square.h"

int main ()
    try	{
	// Setting up the window
	Point tl{100,100};
	Simple_window win{tl,800,600,"Canvas"};
	win.set_label("Project 6");

	// Setting the two squares and their colors
	Square sq1(Point {200,200}, 200);
	sq1.set_color(Color::blue);
	win.attach(sq1);
	Square sq2(Point {400,300}, 200);
	sq2.set_color(Color::red);
	win.attach(sq2);
	
	// Adding the display text via an ostringstream
	ostringstream os;
	os << "The side-length of the blue-outlined square is "
	   << sq1.side() << " pixels.";

	Graph_lib::Text t1(Point {100,100}, os.str());
	t1.set_font(Graph_lib::Font::times);
	t1.set_font_size(18);
	win.attach(t1);

	Graph_lib::Text t2(Point {100, 150},
			   "Press the \"Next\" button to change the picture");
	t2.set_font(Graph_lib::Font::times);
	t2.set_font_size(18);
	win.attach(t2);

	win.wait_for_button();        // To display

	
	// Next window panel view
	// Changing the color and border-color of square 1
	sq1.set_color(Color::black);
	sq1.set_style(Line_style{Line_style::dash,1});
	sq1.set_fill_color(Color::white);
	sq2.move(100, 0);      // Moving square 2 100px to the right

	// Replacing t1 and t2 elements with new text
	ostringstream oss;
	oss << "The side-length of the white square is "
	    << sq1.side() << " pixels.";
	t1.set_label(oss.str());
	t2.set_label("Press the \"Next\" button to get an unpleasant surprise");

	win.wait_for_button();
	

	// Testing a bad square
	Point sp3 = {300, 300};
	Point sp4 = {400, 600};
	Square sq3(sp3, sp4);

	win.wait_for_button();
	
    }
    catch(exception& e) {
	cerr << "caught exception " << e.what() << endl;
	return 1;
    }
    catch(...) {
	cerr << "what happened? \n";
	return 2;
    }
