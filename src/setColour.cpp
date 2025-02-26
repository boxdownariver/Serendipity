#include <iostream>

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

