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

#endif //PROJECT_1_UTILITIES_H
