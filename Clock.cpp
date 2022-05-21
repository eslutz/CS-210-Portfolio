/**
 * Eric Slutz
 * CS-210
 * Project 1
 *
 * Clock Class
 */

#include "Clock.h"
#include "Utilities.h"

#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>

using namespace std;

namespace ChadaTechClock {

	/**
	 * Default constructor that initializes a clock to current the local time.
	 */
	Clock::Clock() {
		// Gets current local time (24 hr format).
		time_t currentTime = time(nullptr);
		tm localTime{};
		localtime_r(&currentTime, &localTime);
		this->timeLastRefreshed = static_cast<unsigned int>(currentTime);

		// Sets 24 hr time.
		this->hour = localTime.tm_hour;
		this->minute = localTime.tm_min;
		this->second = localTime.tm_sec;
	}

	/**
	 * Adds one hour to the time.  After hour reaches 23, resets to 0 the next time
	 * the method is called.
	 */
	void Clock::addOneHour() {
		this->hour = (this->hour == 23) ? 0 : this->hour + 1;
	}

	/**
	 * Adds one minute to the time.  After minute reaches 59, resets to 0 the next
	 * time the method is called and calls addOneHour().
	 */
	void Clock::addOneMinute() {
		if (this->minute == 59) {
			this->minute = 0;
			addOneHour();
		}
		else {
			this->minute++;
		}
	}

	/**
	 * Adds one second to the time.  After second reaches 59, resets to 0 the next
	 * time the method is called and calls addOneMinute().
	 */
	void Clock::addOneSecond() {
		if (this->second == 59) {
			this->second = 0;
			addOneMinute();
		}
		else {
			this->second++;
		}
	}

	/**
	 * Formats the time in 24-hour or 12-hour format to display.
	 * For 12-hour format, converts the time from 24-hour to 12-hour and sets the
	 * correct option for AM or PM.
	 *
	 * @param clock12Hr defaults to false for 24-hour format, pass true for 12-hour format
	 * @return Formatted time string.
	 */
	string Clock::getFormattedTime(bool clock12Hr) const {
		// Declares string for storing 'AM' or PM;
		string amOrPm;
		// Create a local copy of hour for manipulating.
		unsigned int hourForClock = this->hour;
		// If clock12Hr == true, convert the hourForClock from 24-hour to 12-hour.
		if (clock12Hr) {
			// If hour == 0, then it's midnight, so set hour to 12 and amOrPm to 'AM'.
			if (hourForClock == 0) {
				hourForClock = 12;
				amOrPm = "A M";
			}
				// If hour == 12, do not change the value and set amOrPm to 'PM'.
			else if (hourForClock == 12) {
				amOrPm = "P M";
			}
				// If hour > 12, subtract 12 from the value to convert to 12-hour time and set amOrPm to 'PM'.
			else if (hourForClock > 12) {
				hourForClock = hourForClock - 12;
				amOrPm = "P M";
			}
				// If none of the previous conditions are true, then it's morning so set amOrPm to 'AM'.
			else {
				amOrPm = "A M";
			}
		}

		// Declares an output stream.
		ostringstream timeString;

		// Formats each digit with a leading '0' if needed, separating the values with ':' and adds it to the output stream.
		timeString << Utilities::repeatingChar('0', 2, to_string(hourForClock)) << ":";
		timeString << Utilities::repeatingChar('0', 2, to_string(this->minute)) << ":";
		timeString << Utilities::repeatingChar('0', 2, to_string(this->second));
		// If clock12Hr == true, ends stream with 'AM' or 'PM'.
		if (clock12Hr) {
			timeString << " " << amOrPm;
		}

		// Returns the new formatted time string.
		return timeString.str();
	}

	/**
	 * Takes the two formatted times and formats them further for display together.
	 */
	void Clock::displayTime() {
		Utilities::clearScreen();
		// Top line.
		cout << Utilities::repeatingChar('*', 27);
		cout << Utilities::repeatingChar(' ', 3);
		cout << Utilities::repeatingChar('*', 27) << endl;
		// Clock type titles.
		cout << "*      12-HOUR CLOCK      *";
		cout << Utilities::repeatingChar(' ', 3);
		cout << "*      24-HOUR CLOCK      *" << endl;
		// Mid gap line.
		cout << "*" << Utilities::repeatingChar(' ', 25) << "*";
		cout << Utilities::repeatingChar(' ', 3);
		cout << "*" << Utilities::repeatingChar(' ', 25) << "*" << endl;
		// Clock time.
		// Calls getFormattedTime(true) to get 12-hour formatted time.
		cout << "*      " << this->getFormattedTime(true) << "       *";
		cout << Utilities::repeatingChar(' ', 3);
		// Calls getFormattedTime() to get 24-hour formatted time.
		cout << "*        " << this->getFormattedTime() << "         *" << endl;
		// Bottom line.
		cout << Utilities::repeatingChar('*', 27);
		cout << Utilities::repeatingChar(' ', 3);
		cout << Utilities::repeatingChar('*', 27) << endl;
	}

	/**
	 * Displays the clock menu.
	 */
	void Clock::displayClockMenu() {
		// Generates menu width based on the longest string in the menu.
		// Variable for storing the number of fixed menu items such as '* [item number] - ' and trailing '*'.
		const unsigned int fixedMenuContentWidth = 7;
		// Variable for storing the length of the longest string in the menu options.
		unsigned int menuWidth = 0;
		// Loops through menuOptions array.
		for (string_view menuOption : menuOptions) {
			// Initialize a variable with the length of the current menu option.
			auto menuOptionLength = static_cast<unsigned int>(menuOption.length());
			// If menuOptionLength is greater than menuWidth, set menuWidth with the new longer size.
			if (menuOptionLength > menuWidth) {
				menuWidth = menuOptionLength;
			}
		}
		// Take menuWidth, which now has the length of the longest menu option,
		// add fixedMenuContentWidth, and add 6 for extra whitespace at the end.
		menuWidth += fixedMenuContentWidth + 6;

		// Top line.
		cout << Utilities::repeatingChar('*', menuWidth) << endl;
		// Loop through menuOption, formatting each one for display and printing it.
		// Loop through all but last menu option, to separate the last one as a special option.
		for (int i = 0; i < size(menuOptions) ; i++) {
			// Checks if loop is on its last iteration.
			if (i == size(menuOptions) - 1) {
				// Menu divider line for extra menu item.
				cout << "* " << Utilities::repeatingChar('-', menuWidth - 4) << " *" << endl;
			}

			// Sets the number of times the char should be repeated.
			unsigned int repeatSize = menuWidth - fixedMenuContentWidth - static_cast<unsigned int>(menuOptions[i].length());
			cout << "* " << i + 1 << " - " << menuOptions[i];
			cout << Utilities::repeatingChar(' ', repeatSize);
			cout << "*" << endl;
		}
		// Bottom line.
		cout << Utilities::repeatingChar('*', menuWidth) << endl;
	}

	/**
	 * Gets input from the user for their menu selection.
	 * Checks that it is a valid option.
	 *
	 * @return the users valid menu selection.
	 */
	unsigned int Clock::getClockMenuSelection() {
		// Declares variables for storing the users input and the users validated selection.
		string userInput;
		unsigned int userSelection = 0;

		// Loops until the user makes a valid menu selection.
		while (userSelection == 0 || userSelection > size(menuOptions)) {
			// Gets the users input.
			cout << "=> ";
			cin >> userInput;

			// Check if user entered a valid menu option.
			try {
				// Attempt to parse the input as an unsigned int.
				userSelection = stoul(userInput);
				// Check that it is a positive integer and not larger than the available number of menu options.
				if (userSelection == 0 || userSelection > size(menuOptions)) {
					throw out_of_range("Not a valid menu option");
				}
			}
			// User entered an invalid option.
			catch (...) {
				// Prompt user for input again.
				Utilities::clearScreen();
				displayClockMenu();
				cout << "Not a valid menu option. Try again." << endl;
			}
		}

		// Return the users validated menu selection.
		return userSelection;
	}

	/**
	 * Determines elapsed time since clock last refreshed and updates the time.
	 */
	void Clock::updateClockTime() {
		// Declares secondsPerHour constant: 60sec * 60min = 3600sec.
		const unsigned int secondsPerHour = 3600;
		// Declares secondsPerHour constant: 60sec.
		const unsigned int secondsPerMinute = 60;

		// Gets the current time.
		unsigned int currentTime = static_cast<int>(time(nullptr));
		// Determines how much time has passed since the last refresh.
		unsigned int timeElapsed = currentTime - this->timeLastRefreshed;
		// Sets timeLastRefreshed to the current time of refresh.
		this->timeLastRefreshed = currentTime;

		// Sets the number of hoursPassed that have passed.
		unsigned int hoursPassed = timeElapsed / secondsPerHour;
		// Gets remaining seconds left.
		timeElapsed %= secondsPerHour;
		// Sets the number of minutes that have passed.
		unsigned int minutesPassed = timeElapsed / secondsPerMinute;
		// Gets remaining seconds left.
		timeElapsed %= secondsPerMinute;
		// Sets the number of that have passed.
		unsigned int secondsPassed = timeElapsed;

		// Updates clock time by hour, minute, and second.
		for (int i = 0; i < hoursPassed; i++) {
			addOneHour();
		}
		for (int i = 0; i < minutesPassed; i++) {
			addOneMinute();
		}
		for (int i = 0; i < secondsPassed; i++) {
			addOneSecond();
		}
	}

	/**
	 * Enables the automatic refreshing of the clock, so you see every second tick by.
	 *
	 * @return true to enable auto refresh, false to go back to clock menu.
	 */
	bool Clock::enableAutoRefresh() {
		Utilities::clearScreen();
		// Declares userRefreshSelection to store users input.
		char userRefreshSelection;
		// Displays warning message that this will start an infinite loop and disable the menu.
		cout << "Clock Auto Refresh" << endl << endl;
		cout << "This will disable menu access and will start an infinite loop." << endl;
		cout << "Are you sure you want to continue (y/n) => ";
		// Gets the users input.
		cin >> userRefreshSelection;
		// Clears input cache after previously reading the first char.
		cin.ignore(numeric_limits<int>::max(), '\n');

		// If the user entered 'Y' or 'y' to enable auto refresh, returns true.
		if (tolower(userRefreshSelection) == 'y') {
			return true;
		}
		// Otherwise, returns false if user enters 'n' or invalid input.
		else {
			return false;
		}
	}

}
