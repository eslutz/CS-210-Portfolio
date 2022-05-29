/**
 * Eric Slutz
 * CS-210
 * Project 1
 *
 * Utilities Class
 */

#include "Utilities.h"

#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

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

string Utilities::formatNumber(unsigned int precision, const double t_input) {
	// Declares an output stream.
	ostringstream outputString;

	outputString << fixed << setprecision(2) << setfill('0') << std::setw(1) << t_input;

	// Returns the new string.
	return outputString.str();
}

string Utilities::generateHeader(string t_headerValue, unsigned int t_headerWidth, bool t_swapMidline, const string& t_errorValue) {
	// Declares an output stream.
	ostringstream outputString;

	unsigned int fixedMidlineWidth = size(t_headerValue) + 2;
	unsigned int midlineRepeat = (t_headerWidth - fixedMidlineWidth) / 2;
	transform(t_headerValue.begin(), t_headerValue.end(), t_headerValue.begin(), ::toupper);


	// Top line.
	if (t_errorValue.empty()) {
		outputString << Utilities::repeatingChar('*', t_headerWidth) << endl;
	}
	else {
		unsigned int repeatLength = size(t_errorValue) >= t_headerWidth ? 0 : t_headerWidth - size(t_errorValue);
		outputString << t_errorValue << Utilities::repeatingChar('*', repeatLength) << endl;
	}
	//Mid line.
	outputString << alternatingChar('*', ' ', midlineRepeat)
	<< " "
	<< t_headerValue
	<< " ";
	if (t_swapMidline) {
		outputString << alternatingChar(' ', '*', midlineRepeat);
	}
	else {
		outputString << alternatingChar('*', ' ', midlineRepeat);
	}
	outputString << endl;
	// Bottom line.
	outputString << repeatingChar('*', t_headerWidth) << endl;

	// Returns the new header.
	return outputString.str();
}

bool Utilities::validateInput(bool t_inputState) {
	if (t_inputState) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	return t_inputState;
}

bool Utilities::confirmation(const string& t_confirmationMessage) {
	const string validResponses [] = {"y", "yes", "n", "no"};
	bool invalidInput = true;
	string valueCorrect;

	while (invalidInput) {
		cout << t_confirmationMessage;
		cin >> valueCorrect;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		transform(valueCorrect.begin(), valueCorrect.end(), valueCorrect.begin(), ::tolower);
		for (const string& validResponse : validResponses) {
			if (valueCorrect == validResponse) {
				invalidInput = false;
			}
		}

		if (invalidInput) {
			cout << "Invalid input. Try again." << endl;
		}
	}

	if (valueCorrect == "y" || valueCorrect == "yes") {
		return true;
	}
	else {
		return false;
	}
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
