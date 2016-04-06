/**********************************************************************
 *
 * Project 5B: Some Computer Graphics Examples
 *
 * Part B of our fifth programming project is a program that draws
 * a standard 8x8 checkerboard with alternating black and red squares.
 *
 * Author: Jacob J. Zhang
 * Date:   August 19, 2015
 *
 **********************************************************************/

#include <Graph.h>
#include <Simple_window.h> 

int main ()
{
    Vector_ref<Rectangle> vr;

    Point tl{100,100};        // Setting initial point
    Simple_window win{tl,550,480,"Canvas"};

    // Providing user instructions as the window opens
    cout << "Click the \"Next\" button to quit the program!\n";

    win.set_label("Checkerboard");        // Providing a name
    
    // Looping through the creation of squares and setting colors by
    // alternating through even and odd coordinate points
    for (int i = 0; i < 8; ++i)
	for (int j = 0; j < 8; ++j) {
	    vr.push_back(new Rectangle{Point{i*60,j*60},60,60});
	    if ((i%2 == 0 && j%2 == 0) || (i%2 != 0 && j%2 != 0))
		vr[vr.size()-1].set_fill_color(Color::red);
	    else
		vr[vr.size()-1].set_fill_color(Color::black);
	    win.attach(vr[vr.size()-1]);
	}

    // Displaying until the "next" button is pressed
    win.wait_for_button();
} 
