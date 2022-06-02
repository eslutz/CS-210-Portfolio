/**
 * Eric Slutz
 * CS-210
 * Project 1
 *
 * Utilities Class
 */

#include "Utilities.h"

#include <cstdlib>
#include <iomanip>
#include <sstream>

namespace ChadaTechClock {

	/**
	 * Takes a string and adds the specified leading char to make a string of the desired length.
	 * If no input value is provided, just a string of repeating chars is created.
	 *
	 * @param leadingChar character to set as leading char.
	 * @param leadingRepeat sets how long the total string should be.
	 * @param input original string to add the leading char to, defaults to empty string for just repeating char.
	 * @return the new string with the leading char.
	 */
	string Utilities::repeatingChar(char repeatingChar, unsigned int repeatingSize, const string& input) {
		// Declares an output stream.
		ostringstream outputString;

		// Adds leading character in the desired format.
		outputString << setw(repeatingSize) << setfill(repeatingChar) << input;

		// Returns the new string.
		return outputString.str();
	}

	/**
	 * Clears the console screen.
	 */
	void Utilities::clearScreen() {
#ifdef _WIN32
		// Clears console on a Windows computer.
		system("cls");
#else
		// Clears console on a Mac/Linux computer.
		system("clear");
#endif
	}

}
