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
