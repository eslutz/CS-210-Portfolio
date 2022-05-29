//
// Created by Eric Slutz on 5/27/22.
//
#include <iostream>
#include <sstream>
#include <string>

#include "Bank.h"
#include "Utilities.h"

using namespace std;

// TODO: complete menu actions.
// TODO: check output formatting of numbers, verify only 2 decimal places displayed.
// TODO: check header tail spacing.

Bank::Bank(double t_initialInvestment, double t_monthlyDeposit, double t_annualInterestRate, int t_years) {
	this->m_initialInvestment = t_initialInvestment;
	this->m_monthlyDeposit = t_monthlyDeposit;
	this->m_annualInterestRate = t_annualInterestRate;
	this->m_months = t_years * 12;
}

Bank Bank::startInvestment() {
	const string START_INVESTMENT_HEADER = "data input";
	double initialInvestment = 0,
	monthlyDeposit = 0,
	interestRate = 0;
	int years = 0;
	bool getInput = true,
	invalidInput = false,
	invalidInitialInvestment = false,
	invalidMonthlyDeposit = false,
	invalidInterestRate = false,
	invalidYears = false;

	while (getInput) {
		Utilities::clearScreen();
		ostringstream invalidInputString;
		if (invalidInput) {
			invalidInputString << "Invalid ";
			if (invalidInitialInvestment) {
				invalidInputString << "initial investment amount, ";
			}
			if (invalidMonthlyDeposit) {
				invalidInputString << "monthly deposit amount, ";
			}
			if (invalidInterestRate) {
				invalidInputString << "interest rate amount, ";
			}
			if (invalidYears) {
				invalidInputString << "length of investment, ";
			}
			invalidInputString << "please try again ";
		}
		else {
			invalidInputString << "";
		}

		cout << Utilities::generateHeader(START_INVESTMENT_HEADER, HEADER_WIDTH, true, invalidInputString.str());

		cout << "Initial Investment Amount: $";
		cin >> initialInvestment;
		invalidInitialInvestment = Utilities::validateInput(cin.fail()) || initialInvestment < 0;
		cout << "Monthly Deposit: $";
		cin >> monthlyDeposit;
		invalidMonthlyDeposit = Utilities::validateInput(cin.fail()) || monthlyDeposit < 0;
		cout << "Annual Interest: %";
		cin >> interestRate;
		invalidInterestRate = Utilities::validateInput(cin.fail()) || interestRate < 0;
		cout << "Number of Years: ";
		cin >> years;
		invalidYears = Utilities::validateInput(cin.fail()) || years <= 0;

		if (invalidInitialInvestment || invalidMonthlyDeposit || invalidInterestRate || invalidYears) {
			invalidInput = true;
			continue;
		}

		cout << Utilities::repeatingChar('*', HEADER_WIDTH) << endl;

		getInput = !Utilities::confirmation("Are you satisfied with these investment options? (y/n) => ");
		invalidInput = false;
	}

	return {initialInvestment, monthlyDeposit, interestRate, years};
}

void Bank::bankMenu() {
	Utilities::clearScreen();
	const string MENU_HEADER = "airgad banking menu";
	cout << Utilities::generateHeader(MENU_HEADER, HEADER_WIDTH);

	for (int i = 0; i < size(bankMenuOptions); i++) {
		cout << i + 1 << ". - " << bankMenuOptions[i] << endl;
	}

	cout << Utilities::repeatingChar('*', HEADER_WIDTH) << endl;
}

/**
 * Gets input from the user for their menu selection.
 * Checks that it is a valid option.
 *
 * @return the users valid menu selection.
 */
unsigned int Bank::getBankMenuSelection() {
	// Declares variables for storing the users input and the users validated selection.
	string userInput;
	unsigned int userSelection = 0;

	// Loops until the user makes a valid menu selection.
	while (userSelection == 0 || userSelection > size(bankMenuOptions)) {
		// Gets the users input.
		cout << "=> ";
		cin >> userInput;

		// Check if user entered a valid menu option.
		try {
			// Attempt to parse the input as an unsigned int.
			userSelection = stoul(userInput);
			// Check that it is a positive integer and not larger than the available number of menu options.
			if (userSelection == 0 || userSelection > size(bankMenuOptions)) {
				throw out_of_range("Not a valid menu option");
			}
		}
			// User entered an invalid option.
		catch (...) {
			// Prompt user for input again.
			Utilities::clearScreen();
			bankMenu();
			cout << "Not a valid menu option. Try again." << endl;
		}
	}

	// Return the users validated menu selection.
	return userSelection;
}

string Bank::getInvestmentReport(bool includeMonthlyDeposit) {
	return std::string();
}

void Bank::setInitialInvestment() {
	const string INITIAL_INVESTMENT_HEADER = "adjust initial investment";
	bool getInput = true,
	invalidUpdatedInitialInvestment = false;
	double updatedInitialInvestment = 0;

	while (getInput) {
		Utilities::clearScreen();
		ostringstream invalidInputString;
		if (invalidUpdatedInitialInvestment) {
			invalidInputString << "Invalid initial investment amount, please try again ";
		}
		else {
			invalidInputString << "";
		}

		cout << Utilities::generateHeader(INITIAL_INVESTMENT_HEADER, HEADER_WIDTH, true, invalidInputString.str());
		cout << "Original Initial Investment Amount: $" << m_initialInvestment << endl;
		cout << "New Initial Investment Amount: $";
		cin >> updatedInitialInvestment;
		invalidUpdatedInitialInvestment = Utilities::validateInput(cin.fail()) || updatedInitialInvestment < 0;

		if (invalidUpdatedInitialInvestment) {
			continue;
		}

		cout << Utilities::repeatingChar('*', HEADER_WIDTH) << endl;

		getInput = !Utilities::confirmation("Are you satisfied with the new initial investment? (y/n) => ");
	}

	m_initialInvestment = updatedInitialInvestment;
}

void Bank::setMonthlyDepositAmount() {
	const string MONTHLY_DEPOSIT_HEADER = "adjust monthly deposit";
	bool getInput = true,
			invalidUpdatedMonthlyDeposit = false;
	double updatedMonthlyDeposit = 0;

	while (getInput) {
		Utilities::clearScreen();
		ostringstream invalidInputString;
		if (invalidUpdatedMonthlyDeposit) {
			invalidInputString << "Invalid monthly deposit amount, please try again ";
		}
		else {
			invalidInputString << "";
		}

		cout << Utilities::generateHeader(MONTHLY_DEPOSIT_HEADER, HEADER_WIDTH, false, invalidInputString.str());
		cout << "Original Monthly Deposit Amount: $" << m_monthlyDeposit << endl;
		cout << "New Monthly Deposit Amount: $";
		cin >> updatedMonthlyDeposit;
		invalidUpdatedMonthlyDeposit = Utilities::validateInput(cin.fail()) || updatedMonthlyDeposit < 0;

		if (invalidUpdatedMonthlyDeposit) {
			continue;
		}

		cout << Utilities::repeatingChar('*', HEADER_WIDTH) << endl;

		getInput = !Utilities::confirmation("Are you satisfied with the new monthly deposit amount? (y/n) => ");
	}

	m_monthlyDeposit = updatedMonthlyDeposit;
}

void Bank::setAnnualInterestRate() {
	const string INTEREST_RATE_HEADER = "adjust annual interest rate";
	bool getInput = true,
			invalidUpdatedInterestRate = false;
	double updatedInterestRate = 0;

	while (getInput) {
		Utilities::clearScreen();
		ostringstream invalidInputString;
		if (invalidUpdatedInterestRate) {
			invalidInputString << "Invalid interest rate, please try again ";
		}
		else {
			invalidInputString << "";
		}

		cout << Utilities::generateHeader(INTEREST_RATE_HEADER, HEADER_WIDTH, false, invalidInputString.str());
		cout << "Original Number: %" << m_annualInterestRate << endl;
		cout << "New Annual Interest: %";
		cin >> updatedInterestRate;
		invalidUpdatedInterestRate = Utilities::validateInput(cin.fail()) || updatedInterestRate < 0;

		if (invalidUpdatedInterestRate) {
			continue;
		}

		cout << Utilities::repeatingChar('*', HEADER_WIDTH) << endl;

		getInput = !Utilities::confirmation("Are you satisfied with the new annual interest rate? (y/n) => ");
	}

	m_annualInterestRate = updatedInterestRate;
}

void Bank::setLengthOfInvestment() {
	const string NUMBER_OF_YEARS_HEADER = "adjust length of investment";
	bool getInput = true,
			invalidUpdatedYears = false;
	unsigned int updatedYears = 0;

	while (getInput) {
		Utilities::clearScreen();
		ostringstream invalidInputString;
		if (invalidUpdatedYears) {
			invalidInputString << "Invalid length of investment, please try again ";
		}
		else {
			invalidInputString << "";
		}

		cout << Utilities::generateHeader(NUMBER_OF_YEARS_HEADER, HEADER_WIDTH, false, invalidInputString.str());
		cout << "Original Number of Years: " << m_months / 12 << endl;
		cout << "New Number of Years: ";
		cin >> updatedYears;
		invalidUpdatedYears = Utilities::validateInput(cin.fail()) || updatedYears <= 0;

		if (invalidUpdatedYears) {
			continue;
		}

		cout << Utilities::repeatingChar('*', HEADER_WIDTH) << endl;

		getInput = !Utilities::confirmation("Are you satisfied with the new length of investment? (y/n) => ");
	}

	m_months = updatedYears * 12;
}
