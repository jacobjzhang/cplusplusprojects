/**********************************************************************
 *
 * Project 2: Quadratic Equation Solver
 *
 * This program uses the quadratic formula to solve varying
 * types of quadratic equations. It uses control mechanisms that we
 * have learned in class to solve equations differently depending
 * on what is inputted.
 *
 * This is the extra credit version that also includes the stable
 * formula, allowing for an alternative method that is more precise.
 *
 * Author: Jacob J. Zhang
 * Date:   6 August 2015
 *
 **********************************************************************/

#include <bjarne/std_lib_facilities.h>

// function declarations
void solve_linear(double b, double c);
void solve_quadratic(double a, double b, double c);

int main()
{
    // input the coefficients of the polynomial
    double a, b, c;        // coefficients of the polynomial

    cout << "Enter the coefficients of a quadratic polynomial "
	 << "a*x**2 + b*x +c: \n";

    // Requesting input for each coefficient
    cout << "  a? ";
    cin >> a;
    cout << "  b? ";
    cin >> b;
    cout << "  c? ";
    cin >> c;    

    // handle degenerate case (linear equation) and quit
    if (a == 0)  // linear equation, not quadratic
	solve_linear(b, c);
    else  // genuine quadratic equation ... forge ahead
	solve_quadratic(a, b, c);
}

// solve the linear equation b*x + c == 0
void solve_linear(double b, double c)
{
    // Output identifying the equation being solved
    cout << "Trying to solve linear equation "
	 << b << "*x + " << c << " == 0\n";

    // Distinguishing between the different binomial possibilities
    if (b == 0 && c == 0) {        // Determine it's a  trivial identity
	cout << "This is the trivial identity 0 == 0.\n";
    } else if (b == 0) {        // Determine it's a contradiction
	cout << "This is the contradictory statement " << c << " == 0.\n";
    } else {
	// Solving for basic linear equations
	double root = -c/b;
	// Output for single root
	cout << "One root, x = " << root << "\n";
    }
}

// use classical quadratic formula to solve a genuine quadratic equation
// a*x^2 + b*x + c ==0, with a != 0
void solve_quadratic(double a, double b, double c)
{
    cout << "Trying to solve the quadratic equation "
	 << a << "*x*x + " << b << "*x + " << c << " == 0\n";

    // Declaring and solving the two different roots with the classical formula
    double root1 = (-b + sqrt(pow(b,2) - 4 * a * c))/(2*a);
    double root2 = (-b - sqrt(pow(b,2) - 4 * a * c))/(2*a);

    // Comparing different aspects of the equation for how to proceed
    // Checking if the discriminant is negative
    if ((pow(b,2) - 4 * a * c) < 0) {
	cout << "No real roots. \n";        // Output if no real roots

    // Checking if it's a double root
    } else if (root1 == root2) {
	cout << "Double root, x = " << root1 << "\n";        // Output for double
	
    } else {        // Proceeding with application of the quadratic formula
	if (b > 0) {
	    // Declaring and solving for roots with stable formula
	    double root_pos_stable1 = (-b - sqrt(pow(b,2) - 4 * a * c))/(2*a);
	    double root_pos_stable2 = c/(a * root_pos_stable1);

	    // Output for unique roots with the classical formula
	    cout << "Using classical formula: Two roots, x = "
		 << root1 << " and x = " << root2 << "\n";
	    // Output for unique roots with the stable formula
	    cout << "Using stable formula: Two roots, x = "
		 << root_pos_stable1 << " and x = " << root_pos_stable2 << "\n";
	} else  {
	    // Declaring and solving for roots with the stable formula
	    double root_neg_stable1 = (-b + sqrt(pow(b,2) - 4 * a * c))/(2*a);
	    double root_neg_stable2 = c/(a * root_neg_stable1);

	    // Output for unique roots with the classical formula
	    cout << "Using classical formula: Two roots, x = "
		 << root1 << " and x = " << root2 << "\n";
	    // Output for unique roots with the stable formula
	    cout << "Using stable formula: Two roots, x = "
		 << root_neg_stable1 << " and x = " << root_neg_stable2 << "\n";
	}
    }
		   
}
