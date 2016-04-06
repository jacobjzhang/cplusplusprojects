/**********************************************************************
 *
 * Project 8: Timing Has Come Today
 *
 * Author: Jacob J. Zhang
 * Date:   August 27, 2015
 *
 * Our final project is a program that measures and prints the speed
 * at which a vector of doubles is inserted into different containers.
 *
 **********************************************************************/

#include <std_lib_facilities.h>
#include <set>
#include <chrono>
using namespace std::chrono;
using Inserter = void(const vector<double>&);

// the Larger_than class for the find_if function
class Larger_than {
    double v;
public:
    Larger_than(double vv) : v(vv) {}
    bool operator()(double x) const { return x>v; }
};

int num_elts;
vector<double> random_vector(int n);
// Function declarations
void time_insert(Inserter inserter, const vector<double>& data);
void insert_list(const vector<double>& data);
void insert_vector(const vector<double>& data);
void insert_set(const vector<double>& data);
template <typename Iter> bool is_sorted(Iter first, Iter last);

int main()
    try {
	cout << "How many elements for container? ";
	while (cin >> num_elts) {
	    // No empty containers
	    if (num_elts <= 0) {
		error("Asking for empty container---ignored.");
	    }
	    else {
		const vector<double>& data = random_vector(num_elts);
		// Inserting into the 3 different containers
		time_insert(insert_list, data);
		time_insert(insert_set, data);
		time_insert(insert_vector, data);
	    }
	    cout << "\nHow many elements for next container? ";
	}
	cout << endl;
    }
    catch(exception& e) {
	cerr << e.what() << endl;
	return 1;
    }
    catch(...) {
	cerr << "what happened? \n";
	return 2;
    }

// Inserting data into a list
void insert_list(const vector<double>& data) {
    list<double> new_list;

    for (auto i: data) {
	// Obtaining the insertion point
	auto j = find_if(new_list.begin(), new_list.end(), Larger_than(data[i]));
	new_list.insert(j, data[i]);
    }

    // Check for sorting of list
    if (std::is_sorted(new_list.begin(), new_list.end()))
    	cout << "Check: list is sorted...";
    else
    	cout << "List is not sorted...";
}

// Inserting data into a set
void insert_set(const vector<double>& data) {
    set<double> new_set(data.begin(), data.end());
    cout << "Don't need to check that a set is sorted...";
}

// Inserting data into a vector
void insert_vector(const vector<double>& data) {
    vector<double> new_vector;
    
    for (int i = 0; i < data.size(); i++) {
	// Obtaining the insertion point
	auto j = find_if(new_vector.begin(), new_vector.end(), Larger_than(data[i]));
	// Using insert for memory allocation
	new_vector.insert(j, data[i]);
	    
    }

    // Check if vector is sorted
    if (std::is_sorted(new_vector.begin(), new_vector.end()))
	cout << "Check: vector is sorted...";
    else
	cout << "Vector is not sorted...";

}

// Getting the time before and after insertion
void time_insert(Inserter inserter, const vector<double>& data)
{
    auto t1 = system_clock::now();
    inserter(data);
    auto t2 = system_clock::now();    
    
    cout << "Elapsed time: "
	 << duration_cast<milliseconds>(t2-t1).count() << "milliseconds\n";
}

// Generate a random vector of doubles
vector<double> random_vector(int n)
{
    vector<double> v(n);
    default_random_engine ran{};
    uniform_real_distribution<> ureal{0,5};
    for (int i = 0; i < n; ++i)
	v[i] = ureal(ran);

    return v;
}

