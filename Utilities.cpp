#include "Utilities.h"

#include <cstdlib>
#include <iomanip>
#include <sstream>

namespace ChadaTechClock {

	string Utilities::leadingChar(char leadingChar, unsigned int leadingRepeat, const string& input) {
		ostringstream outputString;

		outputString << setw(leadingRepeat) << setfill(leadingChar) << input;

		return outputString.str();
	}

	string Utilities::repeatingChar(char repeatingChar, unsigned int repeatQuantity) {
		ostringstream outputString;

		outputString << setw(repeatQuantity) << setfill(repeatingChar) << "";

		return outputString.str();
	}

	void Utilities::clearScreen() {
#ifdef _WIN32
		system("cls");
#else
		system("clear");
#endif
	}

}
