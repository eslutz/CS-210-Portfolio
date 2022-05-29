/**
 * Eric Slutz
 * CS-210
 * Project 1
 *
 * Utilities Header
 */

#ifndef PROJECT_1_UTILITIES_H
#define PROJECT_1_UTILITIES_H

#include <string>

using namespace std;

/**
 * Utilities class for general methods.
 */
class Utilities {
public:
	static string repeatingChar(char t_leadingChar, unsigned int t_outputLength, const string& t_input = "");
	static string alternatingChar(char t_firstChar, char t_secondChar, unsigned int t_outputLength, const string& t_input = "");
	static string formatNumber(unsigned int precision, const double t_input);
	static string generateHeader(string t_headerValue, unsigned int t_headerWidth, bool t_swapMidline = false, const string& t_errorValue = "");
	static bool validateInput(bool t_inputState);
	static bool confirmation(const string& t_confirmationMessage);
	static void clearScreen();
};

#endif //PROJECT_1_UTILITIES_H
