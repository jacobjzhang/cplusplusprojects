/**********************************************************************
 *
 * Project 7: Strings, the Hard Way
 *
 * Author: Jacob J. Zhang
 * Date:   August 26, 2015
 *
 * In our seventh programming assignment, we write several functions
 * to manipulate C style strings that culinate in a program able to
 * check and fix capitalization, and analyze if a string is a palindrome.
 *
 **********************************************************************/

#include <iostream>
using namespace std;

const char* get_c_string();
int strlen(const char* s);
bool islower(char c);
void toupper(char* s);
char* strdup(const char* s);
char* cat_dot(const char *s1, const char* s2, const char* sep=".");
char* reverse(const char* s);
bool is_palindrome(const char* s);

// test out our functions
int main()
{
    cout << "toupper/strdup test:\n";
    cout << "Enter a mixed-case string: ";
    const char* s = get_c_string();
    cout << "The original string is \"" << s << "\"\n";
    char *s1 = strdup(s);
    toupper(s1);
    cout << "Translated to upper case: \"" << s1 << "\"\n";

    cout << "\ncat_dot test\n";
    char str1[] = "bonjour";
    char str2[] = "olam";
    // use default separator
    cout << "cat_dot(\"" << str1 << "\", \"" << str2 << "\") is \""
	 << cat_dot(str1, str2) << "\"\n";
    // use new separator
    char newsep[] = "#!?"; 
    cout << "cat_dot(\"" << str1 << "\", \"" << str2 << "\", " 
	 << newsep << "\") is \""
	 << cat_dot(str1, str2, newsep) << "\"\n";

    cout << "\nPalindrome test:\n";
    cout << "Enter palindrome candidates (one per line).\n"
	"End-of-file (control-D) terminates input (and program).\n";
    while (true) {
	const char* pal_cand = get_c_string();
	if (!cin)
	    break;
	cout << "\"" << pal_cand << "\" is " ;
	if (!is_palindrome(pal_cand)) cout << "not ";
	cout << "a palindrome.\n";
    }
}

// returns the length of a C-string 
int strlen(const char *s)
{
    int len = 0;
    while (s[len] != 0) len++;
    return len;
}

// foolproof way to get a C-string from input
// not exactly in the spirit of C :-)
// suffers from a memory leak
const char* get_c_string()
{
    string str;
    getline(cin, str);
    const char* s = str.c_str();         // memory leak!
    return s;
}

// Check if a char is in the ASCII range of lowercase chars
bool islower(char c)
{
    if (c >= 'a' && c <= 'z')
	return true;
    else
	return false;
}

// Using ASCII range to get the uppercase version of a char
char toupper(char c)
{
    return c - 'a' + 'A';
}

// If a char is lowercase, run it through the toupper function
void toupper(char* s)
{
    for (int i = 0; s[i] != '\0'; i++)
	if (islower(s[i]))
	    s[i] = toupper(s[i]);
}

// Implementing a string duplication function
char* strdup(const char* s)
{
    char *p = (char*)malloc(strlen(s)+1);    // Allocate memory block

    // Copying the string over to new memory
    int i = 0;
    while(s[i] != '\0') {
	p[i] = s[i];
	i++;
    }

    p[i] = '\0';    // Ensure that it ends with a 0 char
    return p;
}

// Concatenating C strings by appending them via loops
char* cat_dot(const char *s1, const char* s2, const char* sep)
{
    char* cat_result = strdup(s1);
    
    // Filling the next elements in cat_result with ones from sep
    for (int i = strlen(s1); i < (strlen(s1)+strlen(sep)); i++)
	cat_result[i] = sep[i-strlen(s1)];
    
    // Doing the same as previous comment with elements from s2
    for (int j = (strlen(s1)+strlen(sep)); j < (strlen(s1)+strlen(sep)+strlen(s2)); j++)
	cat_result[j] = s2[j-(strlen(s1)+strlen(sep))];
    
    return cat_result;
}

// Creating a new reversed C string via a loop by iterating through
// original string backwards
char* reverse(const char* s)
{
    char* rs = strdup(s);
    for (int i = 0; i < strlen(s); i++)
	rs[i] = s[strlen(s)-1-i];
    return rs;
}

// Comparing C strings by iterating through matching char elements
bool equal(const char* s1, const char* s2)
{
    int i = 0;

    // While each char in both match up, continue until end
    while (s1[i] == s2[i]) {
	if (s1[i] == '\0' || s2[i] == '\0')
	    break;
	i++;
    }

    // Use the number of the iterator to ensure strings end simultaneously
    if (s1[i] == '\0' && s2[i] == '\0')
	return true;
    else
	return false;

}

// A simple if-statement to tie together our equal and reverse functions
bool is_palindrome(const char* s)
{
    if (equal(s, reverse(s)))
	return true;
    else
	return false;
}
