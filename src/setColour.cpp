#include <iostream>

using namespace std;

// Function to set the colour codes

void setColour ( int colourCode )
{
	cout << "\033[1;" << colourCode << "m";
	return;
}


