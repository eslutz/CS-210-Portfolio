#include "Clock.h"
#include "Utilities.h"

#include <chrono>
#include <iostream>
#include <thread>

using namespace ChadaTechClock;
using namespace std;
using namespace std::chrono_literals;
using namespace std::this_thread;

int main() {
	int clockType;
	cout << "Enter 1 for auto-refreshing clock or 2 for enabling menu options => ";
	cin >> clockType;

	bool quitProgram = false;
	 Clock theClock;

	while (!quitProgram) {
		Utilities::clearScreen();
		theClock.displayTime();
		cout << endl;

		if (clockType != 1) {
			Clock::displayClockMenu();
			auto menuSelection = Clock::getClockMenuSelection();

			switch (menuSelection) {
				case 1:
					theClock.addOneHour();
					break;
				case 2:
					theClock.addOneMinute();
					break;
				case 3:
					theClock.addOneSecond();
					break;
				case 4:
				default:
					quitProgram = true;
			}
		}
		else {
			sleep_for(1s);
		}

		theClock.updateClockTime();
	}

	cout << endl << "Goodbye!  Hope you had a good... time." << endl;

	return 0;
}
