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

/**
 * Takes a string and adds the specified leading char to make a string of the desired length.
 * If no input value is provided, just a string of repeating chars is created.
 *
 * @param leadingChar character to set as leading char.
 * @param outputLength sets how long the total string should be.
 * @param input original string to add the leading char to, defaults to empty string for just repeating char.
 * @return the new string with the leading char.
 */
string Utilities::repeatingChar(char t_repeatingChar, unsigned int t_outputLength, const string& t_input) {
	// Declares an output stream.
	ostringstream outputString;

	// Adds leading character in the desired format.
	outputString << setw(t_outputLength) << setfill(t_repeatingChar) << t_input;

	// Returns the new string.
	return outputString.str();
}

/**
 * Takes a string and adds the specified repeating alternating chars to make a string of the desired length.
 * If no input value is provided, just a string of alternating chars is created.
 *
 * @param firstChar character to start alternating with.
 * @param secondChar character to alternate with.
 * @param outputLength sets how long the total string should be.
 * @param input original string to add the alternating chars to, defaults to empty string for just repeating char.
 * @return the new string with the alternating chars.
 */
string Utilities::alternatingChar(char t_firstChar, char t_secondChar, unsigned int t_outputLength, const string& t_input) {
	// Declares an output stream.
	ostringstream outputString;

	// Variable for holding the current char to set for alternating patter.
	char charToSet;
	// Loop through the specified length of the alternating characters.
	for (int i = 0; i < t_outputLength - size(t_input); i++) {
		// Determines odd or even number to alternate the chars.
		charToSet = i % 2 == 0 ? t_firstChar : t_secondChar;
		// Sets the char.
		outputString << charToSet;
	}
	// Adds the original string to the end of the output.
	outputString << t_input;

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
