//
// Created by Eric Slutz on 5/18/22.
//

#ifndef PROJECT_1_CLOCK_H
#define PROJECT_1_CLOCK_H

#include <string>

using namespace std;

namespace ChadaTechClock {

	class Clock {
	private:
		constexpr static string_view menuOptions[] = {
				"Add One Hour",
				"Add One Minute",
				"Add One Second",
				"Exit",
				"Enable Clock Auto Refresh"
		};
		unsigned int hour;
		unsigned int minute;
		unsigned int second;
		unsigned int startTime;
		[[nodiscard]] string get24HrTime() const;
		[[nodiscard]] string get12HrTime() const;
	public:
		Clock();
		[[maybe_unused]] Clock(unsigned int hour,
									  unsigned int minute,
									  unsigned int second,
									  bool set12HrClock = false,
									  bool setPM = false);
		void displayTime();
		static void displayClockMenu();
		static unsigned int getClockMenuSelection();
		void addOneHour();
		void addOneMinute();
		void addOneSecond();
		void updateClockTime();
		bool enableAutoRefresh();
	};

} // ChadaTechClock

#endif //PROJECT_1_CLOCK_H
