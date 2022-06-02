<<<<<<< HEAD
/**
 * Eric Slutz
 * CS-210
 * Project 1
 *
 * Main Method
 */

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
	// Sets boolean values needed fo program to run.
	bool clockAutoRefresh = false;
	bool quitProgram = false;
	// Initializes a clock.
	Clock theClock;

	// Loops until quitProgram is true.
	while (!quitProgram) {
		// Displays the clock.
		theClock.displayTime();
		cout << endl;

		// If clockAutoRefresh is not enabled, display the clock menu.
		if (!clockAutoRefresh) {
			// Displays the clock menu and get the user's menu selection.
			Clock::displayClockMenu();
			auto menuSelection = Clock::getClockMenuSelection();

			// Switch statement, based on user's selection, picks the correct code.
			switch (menuSelection) {
				// User wants to add one hour to the clock.
				case 1:
					theClock.addOneHour();
					break;
				// User wants to add one minute to the clock.
				case 2:
					theClock.addOneMinute();
					break;
				// User wants to add one second to the clock.
				case 3:
					theClock.addOneSecond();
					break;
				// User wants to quit the program.
				case 4:
					quitProgram = true;
					Utilities::clearScreen();
					break;
				// User want to enable the clock auto refresh.
				case 5:
					clockAutoRefresh = Clock::enableAutoRefresh();
					break;
				// Default action is to start the loop again.
				default:
					continue;
			}
		}
		// Auto refresh has been enabled.
		else {
			// Start looping once per second.
			sleep_for(1s);
		}

		// Call updateClockTime() method to update the clocks time before displaying it again.
		theClock.updateClockTime();
	}

	// Display a goodbye message after the user quits the program.
	cout << endl << "Goodbye!  Hope you had a good... time." << endl;

	return 0;
}
=======
/**
 * Eric Slutz
 * CS-210
 * Project 2
 *
 * Main Method
 */

#include <iostream>

#include "Bank.h"

using namespace std;

int main() {
	// Sets the boolean for program to run.
	bool quitProgram = false;
	// Initializes the bank instance.
	Bank airgead = Bank::startInvestment();

	// Loops until quitProgram is true.
	while (!quitProgram) {
		// Displays menu and gets the user's menu selection.
		auto userSelection = Bank::getBankMenuSelection();
		// Switch statement, based on user's selection, picks the correct code.
		switch (userSelection) {
			// User wants to view the investment report including monthly deposits.
			case 1:
				airgead.getInvestmentReport(true);
				break;
			// User wants to view the investment report excluding monthly deposits.
			case 2:
				airgead.getInvestmentReport();
				break;
			// User wants to update the initial investment amount.
			case 3:
				airgead.setInitialInvestment();
				break;
			// User wants to update the monthly deposit amount.
			case 4:
				airgead.setMonthlyDepositAmount();
				break;
			// User wants to update the annual interest rate amount.
			case 5:
				airgead.setAnnualInterestRate();
				break;
			// User wants to update the number of years of the investment.
			case 6:
				airgead.setLengthOfInvestment();
				break;
			// User wants to quit the program.
			// Default action is to quit the program.
			case 7:
			default:
				quitProgram = true;
				cout << endl << "Thank you for investing with Airgad Banking!" << endl;
		}
	}

	return 0;
}
>>>>>>> remotes/repo2/main
