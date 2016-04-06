/**********************************************************************
 *
 * Project 4: Temperature Processing
 *
 * This is the fourth project in our C++ Programming class. The aim is
 * to create a program that analyzes files of temperature data. The
 * program checks the validity of the data, and returns its sorted
 * values, mean, and median.
 *
 * Author: Jacob J. Zhang
 * Date:   August 17, 2015
 *
 **********************************************************************/

#include <bjarne/std_lib_facilities.h>

/*
 * the Reading class represents a temperature reading
 */
struct Reading {
    int hour;        // the hour that the temperature was taken
    double temperature;        // the actual reading taken
    // Constructor containing both values
    Reading(int h, double t): hour(h), temperature(t) { }
};

// Overriding the < operator
bool operator<(const Reading &r1, const Reading& r2); 

/*
 * function declarations
 */

// Overriding the << output operator
ostream& operator<<(ostream& ost, const Reading &r);

// This is the vector for storage of the temperature data
vector<Reading> get_temps();

// Checking the temperatures and adjusting as needed
double check_adjust_temp(double temperature, char scale);

// This function converts celsius to fahrenheit
// precondition: reading in celsius; returns: reading in fahrenheit
double c_to_f(double temperature);

// The calculated mean from the vector of temperatures
double mean(vector<Reading> temps);
 
// The calculated median from the vector of temperatures
double median(vector<Reading> temps);

// A function to print the readings, their mean, and their median
// precondition: temps, mean_temp, median_temp need values
void print_results(const vector<Reading>& temps, double mean_temp, 
		   double median_temp);

int main()
    try {
	vector<Reading> temps = get_temps();
	if (temps.size() == 0) error("no temperatures given!");
	double mean_temp = mean(temps);
	sort(temps.begin(), temps.end());
	double median_temp = median(temps);
	print_results(temps, mean_temp, median_temp);
    }
    catch (exception& e) {
	cerr << "error: " << e.what() << '\n'; 
	return 1;
    }
    catch (...) {
	cerr << "Oops: unknown exception!\n"; 
	return 2;
    }

/*
 * function definitions
 */

bool operator<(const Reading &r1, const Reading& r2) 
{
    // Resolve by temperature first
    if (r1.temperature < r2.temperature)
	return true;
    // If temps are equal, resolve by hour
    else if (r1.temperature == r2.temperature && r1.hour < r2.hour)
	return true;
    else
	return false;
}

ostream& operator<<(ostream& ost, const Reading &r)
{
    // Setting width and precision for formatting
    ost << setw(2) << r.hour
	<< ":"
	<< setw(8) << setprecision(2) << fixed  << r.temperature << " F \n";
    return ost;
}

vector<Reading> get_temps()
{ 
    vector<Reading> temps;
    int hour;
    double temperature;
    char scale;

    // Setting up the input stream from a file
    cout << "Please enter input file name: ";
    string iname;
    cin >> iname;
    ifstream ist {iname};
    
    while (ist >> hour >> temperature >> scale) {
	// Validating and cleaning the data
	temperature = check_adjust_temp(temperature, scale);
	if (hour < 0 || 23 < hour)
	    error("hour out of range");
	temps.push_back(Reading{hour,temperature});
    }
    return temps;
    
}

double check_adjust_temp(double temperature, char scale)
{
    double convertedtemp;
    // Validating the scale
    if (scale != 'c' && scale != 'C' && scale != 'f' && scale != 'F')
	error("illegal temperature scale");
    // Converting to fahrenheit if necessary
    if (scale == 'c' || scale == 'C')
	convertedtemp = c_to_f(temperature);
    else
	convertedtemp = temperature;
    // Checking for temperatures below absolute zero
    if (convertedtemp < -459.67)
	error("temperature too cold");
    return convertedtemp;
}

double c_to_f(double temperature)
{
    return temperature * 9/5 + 32;
}

double mean(vector<Reading> temps)
{
    double sum;
    for (int i = 0; i < temps.size(); ++i)
	sum += temps[i].temperature;    
    return sum/temps.size();
}

double median(vector<Reading> temps)
{
    double midind = temps.size()/2;    // Grabbing the middle index
    if ((temps.size() % 2) == 0) 
	return (temps[midind].temperature + temps[midind-1].temperature)/2;
    else
	return temps[midind].temperature;
}

void print_results(const vector<Reading>& temps, double mean_temp, 
		   double median_temp)
{
    cout << "The sorted temperatures are: \n";
    // Looping through temps vector to display readings in a table
    for (int i = 0; i < temps.size(); ++i)
	cout << temps[i];
    cout << "The mean temperature is " << mean_temp << " F.\n";
    cout << "The median temperature is " << median_temp << " F.\n";
}  
