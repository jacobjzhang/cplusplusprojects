/**********************************************************************
 *
 * Project 3: Bulls and Cows
 *
 * Author: Jacob J. Zhang
 * Date:   August 11, 2015
 *
 * This is the third project in our C++ programming class, and is 
 * meant to demonstrate usage of vectors, functions, error handling, etc.
 * In it, we build a game called "Bulls and Cows" where a secret
 * number sequence needs to be guessed by the user.
 * 
 **********************************************************************/

#include <bjarne/std_lib_facilities.h>

// (global) constants
const bool show_soln = false; // show solution before playing a new round
const bool debug = false;     // print debug info about the bull/cow calculation
const int num_slots = 4;     // number of slots
const int range_top = 10;    // upper bound on slot value

// for bad input data
class Bad_data{};

// for a bad frequency vector ... this shouldn't ever happen
class Bad_frequency{};

// function declarations
void offer_help();
vector<int> generate_solution();
void print_vector(string msg, vector<int> v);
bool play_one_game(vector<int> solution);
int count_cows(int bulls, vector<int> guess, vector<int> solution);
vector<int> compute_frequency(vector<int> data);
void print_debug_info(vector<int> solution_frequency, 
                      vector<int> guess_frequency, 
                      vector<int> min_frequency, int total_hits);

/*
 * main() handles top-level flow of control, as usual 
 */
int main()
{
    // pigeonhole-principle check
    if (num_slots >= range_top) {
	cerr << "Error: range_top (" << range_top
	     << ") should be greater than num_slots " << num_slots << endl; 
	return 1;
    }

    try {
	offer_help();     // ... if needed

	bool playing = true;           // play another round?
	while (playing) {
	    // generate solution, printing same if debugging
	    vector<int> solution = generate_solution();
	    if (show_soln) 
		print_vector("Actual solution: ", solution);

	    // play the game
	    bool success = play_one_game(solution);

	    // how'd we do?
	    if (success)
		cout << "Congratulations!\n";
	    else 
		print_vector("Too bad!  Solution was ", solution);

	    // another round?
	    cout << "\nPlay again (0/1)? ";
	    int play_again;
	    if (!(cin >> play_again))
		throw Bad_data();
	    playing = play_again != 0;
	}
    }
    catch (Bad_data) {
	cerr << "Bad input data!  I give up!\n";
	return 2;
    }
    catch (Bad_frequency) {
	cerr << "Bad frequency vector.  This can't happen!\n";
	return 3;
    }
}

/*
 * offer help, if needed
 */
void offer_help()
{
    cout << "Need help (0/1)? ";        // Prompt for providing assistance
    int need_help;
    if (!(cin >> need_help))       
	throw Bad_data();

    // If help is requested, these  basic instructions are given.
    if (need_help != 0) {
	cout << "I will generate a pattern of 4 distinct numbers, each in the range 0 through 9.\n"
	     << "You will give a series of guesses of this pattern.\n"
	     << "Each guess that you enter will be a line containing 4 integers,\n"
	     << "separated by spaces, such as\n"
	     << "    2 4 3 1\n"
	     << "I will respond with the number of bulls and cows.\n"
	     << "For example, if the actual solution was 2 3 6 1, I'll respond\n"
	     << "    Bulls: 2, cows: 1\n"
	     << "since two guesses (2 and 1) were in the correct position\n"
	     << "and one guess (3) was in an incorrect position.\n"
	     << "See how many guesses it takes you to get the solution!\n\n"
	     << "If you want to give up, type a negative number for one of\n"
	     << "your guesses, and we'll tell you what the pattern was.\n";
    }
}

/*
 * generate solution for a game of Bulls and Cows
 *
 * precondition: num_slots > 0, range_top > 0
 * return value: vector of size num_slots, with distinct entries, each
 * in the range [0..range_top)
 */

vector<int> generate_solution()
{
    // tracks which numbers have been used
    vector<bool> is_used(range_top);
    vector<int> solution;
    for (int i = 0; i < num_slots; i++) {
	int trial = randint(range_top-1);
	while (is_used.at(trial)) 
	    trial = randint(range_top-1);         
	solution.push_back(trial);
	is_used.at(trial) = true;
    }
    return solution;
}

/*
 * print a vector, with an initial decoration, all on one line
 * 
 * the only precondition (not easily enforceable) is that it all fits
 * on line
 */
void print_vector(string msg, vector<int> v)
{
    cout << msg;
    for (auto x: v) cout << x << " ";   
    cout << endl;
}

/*
 * The play_one_game function contains the primary gameplay
 * mechanism. It initializes the number of guesses, bulls, and cows
 * for each game and increases them accordingly as the game progresses.
 * 
 * precondition: solution must a vector with values
 * return value: if true, the player wins the game. If false, we exit out.
 */
bool play_one_game(vector<int> solution)
{
    bool still_guessing = true;

    // Initialize guess number at 1 to start off the game 
    int guess_number = 1;

    // Looping through the rounds of guesses while still guessing
    while (still_guessing) {
	// Declaring vectors and integers
	vector<int> guess;
	int bulls = 0;
	int cows = 0;
	int tempInt;

	cout << "Guess #" << guess_number << "? ";        // Prompt for input

	// Inputting as many elements as needed to fill the slots
	for (int i = 0; i < num_slots; ++i) {
	    cin >> tempInt;	       
	    guess.push_back(tempInt);
	}	

	// Increase the guess number after receiving an input
	guess_number++;

	for (int i = 0; i < guess.size(); ++i) {
	    // Check if any of the inputs were negatives and exit
	    if (guess[i] < 0)
		return false;
	    // If the guess is too big or a letter, throw an error
	    if (guess[i] >= range_top || isalpha(guess[i]) > 0)
		throw Bad_data();
	    // Increase the # of bulls if there is a match with the solution
	    if (guess[i] == solution[i])
		bulls++;
	}

	// Ensure that the cows are counted and stored in an integer
	cows = count_cows(bulls, guess, solution);

	// Outputting the number of bulls and the number of cows
	cout << "Bulls: " << bulls << ", cows: " << cows << "\n\n";
	
	if (bulls == num_slots)
	    return true;                         // we won!

    }
}

/*
 *  This is the function to count the number of cows. It works by 
 *  obtaining the minimum of each value within the solution and guess
 *  vectors, and summing the minimums up for a total number of hits,
 *  which, subtracted by the bulls, gives the number of cows.
 *  
 *  precondition: bulls > 0, guess and solutions are vectors with values
 *
 *  return value: the number of cows, calculated by total hits - bulls
 */
int count_cows(int bulls, vector<int> guess, vector<int> solution)
{
    // Use the compute_frequency to obtain solution_frequency and guess_frequency
    vector<int> solution_frequency = compute_frequency(solution);
    vector<int> guess_frequency = compute_frequency(guess);
    vector<int> min_frequency;

    // Computing the min_frequency vector
    for (int i = 0; i < 10; ++i) {
	min_frequency.push_back(min(solution_frequency[i],guess_frequency[i]));
    }
    
    int total_hits = 0;

    // Summing up the total hits
    for (int j = 0; j < min_frequency.size(); ++j) {
	total_hits += min_frequency[j];
    }
    
    if (debug)
	print_debug_info(solution_frequency, guess_frequency, 
			 min_frequency, total_hits);
    
    return total_hits - bulls;        // returning # of cows
}

/*
 * determine how many 0's, 1's, ... in a given vector
 *
 * precondition: There needs to be vector with a values
 *
 * return value: It returns a vector with the frequency of each element
 * corresponding to each number from 0 to 9.
 *
 */
vector<int> compute_frequency(vector<int> data)
{
    vector<int> temp(range_top);
    // Looping through until the outer bound of the range
    for (int i = 0; i < range_top; ++i) {
	// Checking the [i] element of data against the element in the range
	for (int j = 0; j < data.size(); ++j)
	    if (i == data[j])
		temp[i]++;
    }
    return temp;
}

/*
 * prints useful debugging information, as per the project handout
 */
void print_debug_info(vector<int> solution_frequency, 
		      vector<int> guess_frequency, 
		      vector<int> min_frequency, int total_hits)
{
    cout << "index:             ";
    for (int i = 0; i < solution_frequency.size(); i++)
	cout << " " << i;
    cout << "                   ";
    cout << endl;
    cout << "                   ";
    for (int i = 0; i < solution_frequency.size(); i++)
	cout << "--";
    cout << endl;      
    print_vector("solution frequency: ", solution_frequency);
    print_vector("guess frequency   : ", guess_frequency);
    print_vector("minimum           : ", min_frequency);
    cout << "sum minimum:        " << total_hits << endl;
}
