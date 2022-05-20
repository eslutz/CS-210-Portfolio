//
// Created by Eric Slutz on 5/18/22.
//

#include "Clock.h"
#include "Utilities.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

namespace ChadaTechClock {
	// TODO: get clock to auto-refresh.
	// TODO: comment all the things!!!

	// Clock default constructor that initializes clock to current local time
	Clock::Clock() {
		// Gets current local time (24 hr format).
		time_t currentTime = time(nullptr);
		tm *tm_local = localtime(&currentTime);
		this->startTime = currentTime;

		// Sets 24 hr time.
		this->hour = tm_local->tm_hour;
		this->minute = tm_local->tm_min;
		this->second = tm_local->tm_sec;
	}

	[[maybe_unused]] Clock::Clock(unsigned int hour,
								  unsigned int minute,
								  unsigned int second,
								  bool set12HrClock,
								  bool setPM) {
		if (second >= 60) {
			throw out_of_range ("Second must be less than 60");
		}
		if (minute >= 60) {
			throw out_of_range ("Minute must be less than 60");
		}
		if (set12HrClock && hour > 12){
			throw out_of_range ("Hour must be less than or equal to 12");
		}
		else if (hour >= 24) {
			throw out_of_range ("Hour must be less than 24");
		}

		if (!set12HrClock || (setPM && hour == 12)) {
			this->hour = hour;
		}
		else if (setPM && hour < 12) {
			this->hour = hour + 12;
		}
		else {
			this->hour = 0;
		}
		this->minute = minute;
		this->second = second;
	}

	void Clock::addOneHour() {
		this->hour = (this->hour == 23) ? 0 : this->hour + 1;
	}

	void Clock::addOneMinute() {
		if (this->minute == 59) {
			this->minute = 0;
			addOneHour();
		}
		else {
			this->minute++;
		}
	}

	void Clock::addOneSecond() {
		if (this->second == 59) {
			this->second = 0;
			addOneMinute();
		}
		else {
			this->second++;
		}
	}

	string Clock::get24HrTime() const {
		ostringstream time24HrString;

		time24HrString << Utilities::leadingChar('0', 2, to_string(this->hour)) << ":";
		time24HrString << Utilities::leadingChar('0', 2, to_string(this->minute)) << ":";
		time24HrString << Utilities::leadingChar('0', 2, to_string(this->second));

		return time24HrString.str();
	}

	string Clock::get12HrTime() const {
		string amOrPm;
		unsigned int hourFor12HrTime = this->hour;
		if (hourFor12HrTime == 0) {
			hourFor12HrTime = 12;
			amOrPm = "A M";
		}
		else if (hourFor12HrTime == 12) {
			amOrPm = "P M";
		}
		else if (hourFor12HrTime > 12){
			hourFor12HrTime = hourFor12HrTime - 12;
			amOrPm = "P M";
		}
		else {
			amOrPm = "A M";
		}

		ostringstream time12HrString;

		time12HrString << Utilities::leadingChar('0', 2, to_string(hourFor12HrTime)) << ":";
		time12HrString << Utilities::leadingChar('0', 2, to_string(this->minute)) << ":";
		time12HrString << Utilities::leadingChar('0', 2, to_string(this->second)) << " " << amOrPm;

		return time12HrString.str();
	}

	void Clock::displayTime() {
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
		cout << "*      " << this->get12HrTime() << "       *";
		cout << Utilities::repeatingChar(' ', 3);
		cout << "*        " << this->get24HrTime() << "         *" << endl;
		// Bottom line.
		cout << Utilities::repeatingChar('*', 27);
		cout << Utilities::repeatingChar(' ', 3);
		cout << Utilities::repeatingChar('*', 27) << endl;
	}

	void Clock::displayClockMenu() {
		const unsigned int fixedMenuContentWidth = 7;
		unsigned int menuWidth = 0;
		for (string_view menuOption : menuOptions) {
			if (menuOption.length() > menuWidth) {
				menuWidth = menuOption.length();
			}
		}
		menuWidth += fixedMenuContentWidth + 6;

		cout << Utilities::repeatingChar('*', menuWidth) << endl;
		unsigned int i;
		for (i = 0; i < size(menuOptions) - 1; i++) {
			cout << "* " << i+1 << " - " << menuOptions[i];
			cout << Utilities::repeatingChar(' ', (menuWidth - fixedMenuContentWidth - menuOptions[i].length()));
			cout << "*" << endl;
		}
		cout << "* " << Utilities::repeatingChar('-', menuWidth - 4) << " *" << endl;
		cout << "* " << i+1 << " - " << menuOptions[i];
		cout << Utilities::repeatingChar(' ', (menuWidth - fixedMenuContentWidth - menuOptions[i].length()));
		cout << "*" << endl;
		cout << Utilities::repeatingChar('*', menuWidth) << endl;
	}

	unsigned int Clock::getClockMenuSelection() {
		string userInput;
		unsigned int userSelection = 0;

		while (userSelection == 0 || userSelection > size(menuOptions)) {
			cout << "=> ";
			cin >> userInput;

			// Check if user entered a valid menu option.
			try {
				// Attempt to parse the input as an unsigned int.
				userSelection = stoul(userInput);
				// Check that it is a positive integer.
				if ( userSelection == 0 || userSelection > size(menuOptions)) {
					throw out_of_range ("Not a valid menu option");
				}
			}
			catch (...) {
				// Prompt user for input again.
				Utilities::clearScreen();
				cout << "\nNot a valid menu option. Try again." << endl;
			}
		}

		return userSelection;
	}

	void Clock::updateClockTime() {
		// Determines elapsed time since clock last refreshed.
		long currentTime = time(nullptr);
		long timeElapsed = currentTime - this->startTime;
		this->startTime = currentTime;

		// Updates clock time.
		if(timeElapsed >= 1) {
			for (int i = 0; i < timeElapsed; i++) {
				addOneSecond();
			}
		}
	}

	bool Clock::enableAutoRefresh() {
		Utilities::clearScreen();
		char userRefreshSelection;
		cout << "Clock Auto Refresh" << endl <<endl;
		cout << "This will disable menu access and will start an infinite loop." << endl;
		cout << "Are you sure you want to continue (y/n) => ";
		cin >> userRefreshSelection;
		if (tolower(userRefreshSelection) == 'y') {
			return true;
		}
		else {
			return false;
		}
	}

} // ChadaTechClock
