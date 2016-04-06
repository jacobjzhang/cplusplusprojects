/************************************************************************
 *
 * Project 1: 
 *
 * Author: Jacob J. Zhang
 * Date:   5 August 2015
 *
 * This is the canonical second program for C++.
 * Its purpose is to show that one knows how to define variables, 
 * use statements, and demonstrate an understanding of computation.
 *
 ************************************************************************/

#include <bjarne/std_lib_facilities.h>

// Main function comprising of all coin variables and subsequent operations 
int main ()
{
    cout << "Enter the number of coins you have for each denomination.\n";

    // Requesting the input of each denomination
    cout << " Pennies? ";
    int num_pennies;
    cin >> num_pennies;

    cout << " Nickels? ";
    int num_nickels;
    cin >> num_nickels;

    cout << " Dimes? ";
    int num_dimes;
    cin >> num_dimes;

    cout << " Quarters? ";
    int num_quarters;
    cin >> num_quarters;

    cout << " Half dollars? ";
    int num_half_dollars;
    cin >> num_half_dollars;

    // Totaling the amount after conversion to cents
    int total_cents = num_pennies + num_nickels*5 + num_dimes*10 + num_quarters*25 + num_half_dollars*50;

    // Declaring the dollar amount of the total number of cents
    int total_cents_dollar = total_cents/100;
    // Declaring the cents amount of the total number of cents
    float total_cents_cents = total_cents % 100;

    // Outputting the entered information
    cout << "You have:\n";
    cout << "  " << num_pennies << " pennies \n";
    cout << "  " << num_nickels << " nickels \n";
    cout << "  " << num_dimes << " dimes \n";
    cout << "  " << num_quarters << " quarters \n";
    cout << "  " << num_half_dollars << " half dollars \n";

    // Adding a zero as a placeholder for totals with single-digit cents
    string add_zero;
    if (total_cents_cents < 10) {
	add_zero = "0";
    }

    // Outputting the computation
    cout << "The value of all your coins is " << total_cents << " cents, which is" << " $" << total_cents_dollar << "." << add_zero << total_cents_cents << ".\n";

    return 0;
}
