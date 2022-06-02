/**
 * Eric Slutz
 * CS-210
<<<<<<< HEAD
 * Project 1
=======
 * Project 2
>>>>>>> remotes/repo2/main
 *
 * Utilities Header
 */

#ifndef PROJECT_1_UTILITIES_H
#define PROJECT_1_UTILITIES_H

#include <string>

using namespace std;

<<<<<<< HEAD
namespace ChadaTechClock {

	/**
	 * Utilities class for general methods.
	 */
	class Utilities {
	public:
		static string repeatingChar(char leadingChar, unsigned int leadingRepeat, const string& input = "");
		static void clearScreen();
	};

}
=======
/**
 * Utilities class for general methods.
 */
class Utilities {
public:
	static string repeatingChar(char t_leadingChar, int t_outputLength, const string& t_input = "");
	static string alternatingChar(char t_firstChar, char t_secondChar, int t_outputLength, const string& t_input = "");
	static string formatMoney(double t_input);
	static string generateHeader(string t_headerValue, int t_headerWidth, bool t_swapMidline = false, const string& t_errorValue = "");
	static bool validateInput(bool t_inputState);
	static bool confirmation(const string& t_confirmationMessage);
	static void clearScreen();
};
>>>>>>> remotes/repo2/main

#endif //PROJECT_1_UTILITIES_H
