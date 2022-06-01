/**
 * Eric Slutz
 * CS-210
 * Project 2
 *
 * Utilities Class
 */

#include "Utilities.h"

#include <algorithm>
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
string Utilities::repeatingChar(char t_repeatingChar, int t_outputLength, const string& t_input) {
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
string Utilities::alternatingChar(char t_firstChar, char t_secondChar, int t_outputLength, const string& t_input) {
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
 * Formats a double to the specified decimal point precision.
 *
 * @param precision how many numbers past the decimal point to include.
 * @param t_input the number to set precision on.
 * @return the formatted number.
 */
string Utilities::formatMoney(double t_input) {
	// Declares an output stream.
	ostringstream outputString;

	// Change the number to money format, then add it to the output.
	outputString << fixed << setprecision(2)  << "$" << t_input;

	// Returns the new string.
	return outputString.str();
}

/**
 * Generates a header for use at various points in the program
 *
 * @param t_headerValue text to display in the header.
 * @param t_headerWidth total width of the header.
 * @param t_swapMidline sets if alternating pattern should be swapped in the second half of midline.
 * @param t_errorValue sets error to display at the start of the header.
 * @return the completed header.
 */
string Utilities::generateHeader(string t_headerValue, int t_headerWidth, bool t_swapMidline, const string& t_errorValue) {
	// Declares an output stream.
	ostringstream outputString;

	// Determines the width of content to display in the header.
	int fixedMidlineWidth = static_cast<int>(size(t_headerValue)) + 2;
	// Determines how long the repeat.
	int midlineRepeat = (t_headerWidth - fixedMidlineWidth) / 2;
	// Capitalizes text to display in the header.
	transform(t_headerValue.begin(), t_headerValue.end(), t_headerValue.begin(), ::toupper);


	// Top line.
	// If there is no error to display, generate a normal top header line.
	if (t_errorValue.empty()) {
		outputString << Utilities::repeatingChar('*', t_headerWidth) << endl;
	}
	// Otherwise, generate a top header line with the error at the start.
	else {
		// Sets length of the repeat after the error is displayed.
		// If the length of the error is longer than total header width, then set the repeat to zero.
		// Otherwise, set the repeat to the difference between the error length and header width.
		int repeatLength = size(t_errorValue) >= t_headerWidth ? 0 : t_headerWidth - static_cast<int>(size(t_errorValue));
		// Generate top header line with error followed by the repeating character.
		outputString << t_errorValue << Utilities::repeatingChar('*', repeatLength) << endl;
	}

	//Mid-line.
	// Sets the first half of the repeat, followed by the header text.
	outputString << alternatingChar('*', ' ', midlineRepeat)
	<< " "
	<< t_headerValue
	<< " ";
	// Determines if the trailing repeat should swap the alternating pattern.
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

/**
 * Checks cin.fail(), clearing cin if there was a failure, and returns the value of cin.fail().
 *
 * @param t_inputState pass in cin.fail() to see if there was an error during processing.
 * @return true for a failure, false for no failure.
 */
bool Utilities::validateInput(bool t_inputState) {
	// If true, clear cin so it's ready for the next read attempt.
	if (t_inputState) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	// Returns true or false based on what was passed in.
	return t_inputState;
}

/**
 * Displays a confirmation message to the user, with a yes or no prompt, looping until a valid input is given.
 *
 * @param t_confirmationMessage the confirmation message to ask the user.
 * @return true for yes, false for no.
 */
bool Utilities::confirmation(const string& t_confirmationMessage) {
	// Constant for the valid responses that are being checked for.
	const string validResponses [] = {"y", "yes", "n", "no"};
	// Declares variables needed for storing and validating the users input.
	bool invalidInput = true;
	string valueCorrect;

	// Loops until the user gives a valid response.
	while (invalidInput) {
		// Displays the confirmation message.
		cout << t_confirmationMessage << " (y/n) => ";
		// Gets the users input.
		cin >> valueCorrect;
		// clears out anything extra that may be waiting.
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		// Converts the users input to lower case.
		transform(valueCorrect.begin(), valueCorrect.end(), valueCorrect.begin(), ::tolower);
		// Loops through the possible valid responses, checking if the users input matches any of them.
		// If there is a match, set invalidInput to false so the loop can end.
		for (const string& validResponse : validResponses) {
			if (valueCorrect == validResponse) {
				invalidInput = false;
			}
		}

		// If no valid response was given, display error message before starting loop again.
		if (invalidInput) {
			cout << "Invalid input. Try again." << endl;
		}
	}

	// Check if the validated input was 'yes' and return true.
	if (valueCorrect == "y" || valueCorrect == "yes") {
		return true;
	}
	// Otherwise, input was 'np' so return false.
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
