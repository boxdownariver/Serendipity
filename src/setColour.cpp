#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <string>
#include "headers/setColour.h"
using namespace std;

/**
 * setColour sets the terminal text colour to the specified colour code.
 * 
 * Parameters:
 * - colourCode: An integer representing the desired color code.
 * 
 * The function does not return any value. It directly modifies the terminal color.
 */
void setColour ( int colourCode )
{
	cout << "\033[1;" << colourCode << "m";
	return;
}

/**
 * resetColour resets the terminal text color back to the default colour
 * 
 * The function does not take any parameters and does not return any value.
 */
void resetColour()
{
    cout << "\033[0m"; 
}

/**
 * generateDate Generates the current date in MM/DD/YYYY format.
 *
 * This function retrieves the system's current date using the `time` library,
 * converts it to local time, and formats it into a string representation.
 * The generated date is returned as a string.
 *
 * returns a string representing the current date in MM/DD/YYYY format.
 */

string generateDate ()
{
	time_t t = time(nullptr);  
   tm* tm = localtime(&t); // Convert to local time

    // Format the date as MM/DD/YYYY and store it in a string
    stringstream ss;
    ss << setfill('0') << setw(2) << (tm->tm_mon + 1) << "/"  // Month
       << setw(2) << tm->tm_mday << "/"                       // Day
       << (tm->tm_year + 1900);                               // Year

    // Copy the formatted date to a std::string
    string currentDate = ss.str();  // Now `currentDate` holds the date as a string

    // Print the string (date)

    // You can use currentDate as a string now
    // Example: Copy to another string variable
    string copiedDate = currentDate;

	return copiedDate;

}
