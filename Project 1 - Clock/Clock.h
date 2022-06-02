/**
 * Eric Slutz
 * CS-210
 * Project 1
 *
 * Clock Header
 */

#ifndef PROJECT_1_CLOCK_H
#define PROJECT_1_CLOCK_H

#include <string>

using namespace std;

namespace ChadaTechClock {

	/**
	 * Clock class for defining the functionality of a clock.
	 */
	class Clock {
	private:
		// Menu options for what can be done with the clock.
		constexpr static string_view menuOptions[] = {
				"Add One Hour",
				"Add One Minute",
				"Add One Second",
				"Exit",
				"Enable Clock Auto Refresh"
		};
		// Private variables.
		unsigned int hour;
		unsigned int minute;
		unsigned int second;
		unsigned int timeLastRefreshed;
		// Private method.
		[[nodiscard]] string getFormattedTime(bool clock12Hr = false) const;
	public:
		Clock();
		void displayTime();
		static void displayClockMenu();
		static unsigned int getClockMenuSelection();
		void addOneHour();
		void addOneMinute();
		void addOneSecond();
		void updateClockTime();
		static bool enableAutoRefresh();
	};

}

#endif //PROJECT_1_CLOCK_H
