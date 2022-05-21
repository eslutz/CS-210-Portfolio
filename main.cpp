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
	bool clockAutoRefresh = false;
	bool quitProgram = false;
	Clock theClock;

	while (!quitProgram) {
		theClock.displayTime();
		cout << endl;

		if (!clockAutoRefresh) {
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
				quitProgram = true;
				Utilities::clearScreen();
				break;
			case 5:
				clockAutoRefresh = Clock::enableAutoRefresh();
				break;
			default:
				continue;
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
