/**********************************************************************
 *
 * Project 5A: Some Computer Graphics Examples
 *
 * Part A of our fifth programming project is a program that gets a
 * line from user input and displays it with our styling in a window.
 *
 * Author: Jacob J. Zhang
 * Date:   August 19, 2015
 *
 **********************************************************************/

#include <Graph.h>        // To display "Next" button
#include <Simple_window.h> 

using namespace Graph_lib;

int main ()
    try
	{
	    string name;
	    // Prompting for a name and grabbing the entire line entered
	    cout << "What is your name? ";
	    getline(cin, name);
	    if (string::npos != name.find_first_of("0123456789"))
		throw domain_error("This is not a valid name");

	    // Instructions to appear while the window is open
	    cout << "Click the \"Next\" button to quit the program!\n";	   

	    // Setting styling of text to display name input
	    Text t{Point{100,100}, name};
	    t.set_font(Graph_lib::Font::times_italic);
	    t.set_font_size(30);
	    
	    Point tl{100,100};
	    Simple_window win{tl,350,350,"Canvas"};	  
	    win.set_label("Project 5A");
	    win.attach(t);
	    
 	    win.wait_for_button();        // Display until quit
	} 
    catch(domain_error bad_name) {
	// To handle bad names with numbers
	cout << bad_name.what() << "\n";
    }
