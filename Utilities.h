#ifndef PROJECT_1_UTILITIES_H
#define PROJECT_1_UTILITIES_H

#include <string>

using namespace std;

namespace ChadaTechClock {

	class Utilities {
	public:
		static string leadingChar(char leadingChar, unsigned int leadingRepeat, const string& input);
		static string repeatingChar(char repeatingChar, unsigned int repeatQuantity);
		static void clearScreen();
	};

}

#endif //PROJECT_1_UTILITIES_H
