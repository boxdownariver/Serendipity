#include <iostream>

using namespace std;

// Function to set the colour codes
void setColour ( int colourCode )
{
	cout << "\033[1;" << colourCode << "m";
	return;
}

//Function to reset the colour code back to default
void resetColour()
{
    cout << "\033[0m"; 
}

