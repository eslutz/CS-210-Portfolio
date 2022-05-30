/**
 * Eric Slutz
 * CS-210
 * Project 2
 *
 * Bank Class
 */

#include <iostream>
#include <numeric>
#include <sstream>

#include "Bank.h"
#include "Utilities.h"

using namespace std;

/**
 * Constructor for a bank.
 *
 * @param t_initialInvestment initial investment amount.
 * @param t_monthlyDeposit amount for monthly deposit.
 * @param t_annualInterestRate annual interest rate.
 * @param t_years length of the investment.
 */
Bank::Bank(double t_initialInvestment, double t_monthlyDeposit, double t_annualInterestRate, int t_years) {
	this->m_initialInvestment = t_initialInvestment;
	this->m_investmentBalance = t_initialInvestment;
	this->m_monthlyDeposit = t_monthlyDeposit;
	this->m_annualInterestRate = t_annualInterestRate;
	this->m_years = t_years;
}

/**
 * Gathers all the required information from the user to initialize a bank.
 * @return a new instance of a bank.
 */
Bank Bank::startInvestment() {
	// Constant for text to display in the header.
	const string START_INVESTMENT_HEADER = "data input";
	// Declare variables needed for creating a bank instance.
	double initialInvestment = 0,
	monthlyDeposit = 0,
	interestRate = 0;
	int years = 0;
	// Declare variables needed for tracking input validation.
	bool getInput = true,
	invalidInput = false,
	invalidInitialInvestment = false,
	invalidMonthlyDeposit = false,
	invalidInterestRate = false,
	invalidYears = false;

	// Loop until done getting input.
	while (getInput) {
		Utilities::clearScreen();
		ostringstream invalidInputString;

		// If any input is invalid, start building the error message.
		if (invalidInput) {
			invalidInputString << "Invalid ";
			// Add specific messaging based on which input is invalid.
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

		// Display header for gathering input.
		cout << Utilities::generateHeader(START_INVESTMENT_HEADER,
										  HEADER_WIDTH,
										  true,
										  invalidInputString.str());

		// Prompt, set, and validate input for each piece of needed info.
		cout << "Initial Investment Amount: $";
		cin >> initialInvestment;
		// Check that input is the expected type and in the expected range.
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

		// If any input is invalid, set invalidInput to true and skip to start of the loop.
		if (invalidInitialInvestment || invalidMonthlyDeposit || invalidInterestRate || invalidYears) {
			invalidInput = true;
			continue;
		}
		// Otherwise, reset invalidInput to false.
		else {
			invalidInput = false;
		}

		// If there is no invalid input, display a dividing line after input.
		cout << Utilities::repeatingChar('*', HEADER_WIDTH) << endl;

		// Confirm with the user that all of their input looks correct.
		getInput = !Utilities::confirmation("Are you satisfied with these investment options?");
	}

	// Return values for a new bank instance.
	return {initialInvestment,
			monthlyDeposit,
			interestRate,
			years};
}

/**
 * Displays the menu for the bank.
 *
 * @param t_menuInputError input error message.
 */
void Bank::bankMenu(const string& t_menuInputError) {
	Utilities::clearScreen();

	// Constant for text to display in the header.
	const string MENU_HEADER = "airgad banking menu";
	// Display header for the bank menu and any input error message, if there is one.
	cout << Utilities::generateHeader(MENU_HEADER,
									  HEADER_WIDTH,
									  false,
									  t_menuInputError);

	// Loop through menu options, displaying each one.
	for (int i = 0; i < size(bankMenuOptions); i++) {
		cout << i + 1 << " - " << bankMenuOptions[i] << endl;
	}

	// Display separating line at the end of the menu.
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
	unsigned int menuSelection = 0;
	bool validMenuSelection = true;
	ostringstream invalidInputString;

	// Loops until the user makes a valid menu selection.
	do {
		Utilities::clearScreen();
		if (!validMenuSelection) {
			invalidInputString << "Not a valid menu option, please try again ";
		}
		// Display the bank menu.
		bankMenu(invalidInputString.str());
		// Gets the users input.
		cout << "=> ";
		cin >> menuSelection;

		// Validates the user's selection is of the valid type and within the menu option range.
		validMenuSelection = !Utilities::validateInput(cin.fail())
				&& (menuSelection > 0 && menuSelection <= size(bankMenuOptions));
		// Resets the invalid input string.
		invalidInputString.str("");
	} while (!validMenuSelection);

	// Return the users validated menu selection.
	return menuSelection;
}

/**
 * Computes the interest and new balance for each year of the investment and generates a report to display.
 *
 * @param includeMonthlyDeposit true to include monthly deposits in the report, false to not include them.
 */
void Bank::getInvestmentReport(bool includeMonthlyDeposit) {
	Utilities::clearScreen();

	// Declares an output stream.
	ostringstream outputString;
	// Determines total width of the header based on the set width of each column.
	const int REPORT_WIDTH = accumulate(reportTableHeader.begin(),
										reportTableHeader.end(),
										0,
										[](const int prev_sum,
												const pair<const string, int>& entry)
												{ return prev_sum + entry.second; });

	// Sets the correct report title to display in the header.
	const string depositHeaderPreposition = includeMonthlyDeposit ? "with" : "without";
	const string INVESTMENT_REPORT_HEADER = "balance and interest "
			+ depositHeaderPreposition
			+ " additional monthly deposits";

	// Adds the report header to the output.
	outputString << Utilities::generateHeader(INVESTMENT_REPORT_HEADER, REPORT_WIDTH);
	// Adds each column header to the output.
	for (auto const& [key, val] : reportTableHeader) {
		outputString << Utilities::repeatingChar(' ', val, key);
	}
	// Adds row seperator after the column headers.
	outputString << endl << Utilities::repeatingChar('=', REPORT_WIDTH) << endl;

	// Generates the report.
	// Set starting balance equal to the initial investment.
	this->m_investmentBalance = this->m_initialInvestment;
	// Loop through each year, up to the number of years specified.
	for (int year = 1; year <= m_years; year++) {
		// Declare variable for storing the total interest earned for the year.
		double yearlyInterestEarned = 0;
		// Loop through each month of the year.
		for (int month = 1; month <= 12; month++) {
			// If include monthly deposit is selected, add it to the balance before computing interest.
			if (includeMonthlyDeposit) {
				this->m_investmentBalance += this->m_monthlyDeposit;
			}
			// Determine the amount of interested earned for the month.
			double monthlyInterestEarned = this->m_investmentBalance * ((this->m_annualInterestRate / 100.0) / 12);
			// Add the monthly interest to the yearly interest earned for the year.
			yearlyInterestEarned += monthlyInterestEarned;
			// Add the monthly interest to the total investment balance.
			this->m_investmentBalance += monthlyInterestEarned;
		}

		// Add each output item to a string array to iterate through with the matching column width
		string rowOutputValues[] = {to_string(year),
									"$" + Utilities::formatNumber(m_investmentBalance),
									"$" + Utilities::formatNumber(yearlyInterestEarned)};
		// Declare an index for iterating through the string out value array.
		int i = 0;
		// Loop through each column in the table header map to get the width of the column.
		for ( const auto& column : reportTableHeader) {
			outputString << Utilities::repeatingChar(' ',
													 column.second,
													 rowOutputValues[i]);
			i++;
		}
		outputString << endl;

		// If not the last row of data, add a blank line between each row.
		if (year != m_years) {
			outputString << endl;
		}
	}
	// Add a closing separator line to the report.
	outputString << Utilities::repeatingChar('*', REPORT_WIDTH) << endl;

	// Display the report.
	cout << outputString.str();

	// Wait for user input before returning to the menu.
	cout << "(press Enter to return to menu)";
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
}

/**
 * Gathers and validates input from the user to update the initial investment amount.
 */
void Bank::setInitialInvestment() {
	// Constant for text to display in the header.
	const string INITIAL_INVESTMENT_HEADER = "adjust initial investment";
	// Declare variables needed for getting and validating input.
	bool getInput = true,
	invalidUpdatedInitialInvestment = false;
	double updatedInitialInvestment = 0;

	// Loop until done getting input.
	while (getInput) {
		Utilities::clearScreen();
		ostringstream invalidInputString;

		// If input is invalid, build the error message.
		if (invalidUpdatedInitialInvestment) {
			invalidInputString << "Invalid initial investment amount, please try again ";
		}

		// Display header for updating initial investment.
		cout << Utilities::generateHeader(INITIAL_INVESTMENT_HEADER,
										  HEADER_WIDTH,
										  true,
										  invalidInputString.str());
		// Display original value.
		cout << "Original Initial Investment Amount: $" << m_initialInvestment << endl;
		// Prompt for and get the new value.
		cout << "New Initial Investment Amount: $";
		cin >> updatedInitialInvestment;
		// Validate the input.
		invalidUpdatedInitialInvestment = Utilities::validateInput(cin.fail())
				|| updatedInitialInvestment < 0;

		// If input invalid, skip to the start of the loop.
		if (invalidUpdatedInitialInvestment) {
			continue;
		}

		// Display separating line after getting input.
		cout << Utilities::repeatingChar('*', HEADER_WIDTH) << endl;

		// Confirm with the user that the input looks correct.
		getInput = !Utilities::confirmation("Are you satisfied with the new initial investment?");
	}

	// Set the new initial investment.
	m_initialInvestment = updatedInitialInvestment;
}

/**
 * Gathers and validates input from the user to update the monthly deposit amount.
 */
void Bank::setMonthlyDepositAmount() {
	// Constant for text to display in the header.
	const string MONTHLY_DEPOSIT_HEADER = "adjust monthly deposit";
	// Declare variables needed for getting and validating input.
	bool getInput = true,
	invalidUpdatedMonthlyDeposit = false;
	double updatedMonthlyDeposit = 0;

	// Loop until done getting input.
	while (getInput) {
		Utilities::clearScreen();
		ostringstream invalidInputString;

		// If input is invalid, build the error message.
		if (invalidUpdatedMonthlyDeposit) {
			invalidInputString << "Invalid monthly deposit amount, please try again ";
		}

		// Display header for updating initial investment.
		cout << Utilities::generateHeader(MONTHLY_DEPOSIT_HEADER,
										  HEADER_WIDTH,
										  false,
										  invalidInputString.str());
		// Display original value.
		cout << "Original Monthly Deposit Amount: $" << m_monthlyDeposit << endl;
		// Prompt for and get the new value.
		cout << "New Monthly Deposit Amount: $";
		cin >> updatedMonthlyDeposit;
		// Validate the input.
		invalidUpdatedMonthlyDeposit = Utilities::validateInput(cin.fail())
				|| updatedMonthlyDeposit < 0;

		// If input invalid, skip to the start of the loop.
		if (invalidUpdatedMonthlyDeposit) {
			continue;
		}

		// Display separating line after getting input.
		cout << Utilities::repeatingChar('*', HEADER_WIDTH) << endl;

		// Confirm with the user that the input looks correct.
		getInput = !Utilities::confirmation("Are you satisfied with the new monthly deposit?");
	}

	// Set the new monthly deposit.
	m_monthlyDeposit = updatedMonthlyDeposit;
}

/**
 * Gathers and validates input from the user to update the annual interest rate.
 */
void Bank::setAnnualInterestRate() {
	// Constant for text to display in the header.
	const string INTEREST_RATE_HEADER = "adjust annual interest rate";
	// Declare variables needed for getting and validating input.
	bool getInput = true,
	invalidUpdatedInterestRate = false;
	double updatedInterestRate = 0;

	// Loop until done getting input.
	while (getInput) {
		Utilities::clearScreen();
		ostringstream invalidInputString;

		// If input is invalid, build the error message.
		if (invalidUpdatedInterestRate) {
			invalidInputString << "Invalid interest rate, please try again ";
		}

		// Display header for updating initial investment.
		cout << Utilities::generateHeader(INTEREST_RATE_HEADER,
										  HEADER_WIDTH,
										  false,
										  invalidInputString.str());
		// Display original value.
		cout << "Original Number: %" << m_annualInterestRate << endl;
		// Prompt for and get the new value.
		cout << "New Annual Interest: %";
		cin >> updatedInterestRate;
		// Validate the input.
		invalidUpdatedInterestRate = Utilities::validateInput(cin.fail())
				|| updatedInterestRate < 0;

		// If input invalid, skip to the start of the loop.
		if (invalidUpdatedInterestRate) {
			continue;
		}

		// Display separating line after getting input.
		cout << Utilities::repeatingChar('*', HEADER_WIDTH) << endl;

		// Confirm with the user that the input looks correct.
		getInput = !Utilities::confirmation("Are you satisfied with the new annual interest rate?");
	}

	// Set the new annual interest rate.
	m_annualInterestRate = updatedInterestRate;
}

/**
 * Gathers and validates input from the user to update the number of years.
 */
void Bank::setLengthOfInvestment() {
	// Constant for text to display in the header.
	const string NUMBER_OF_YEARS_HEADER = "adjust length of investment";
	// Declare variables needed for getting and validating input.
	bool getInput = true,
	invalidUpdatedYears = false;
	unsigned int updatedYears = 0;

	// Loop until done getting input.
	while (getInput) {
		Utilities::clearScreen();
		ostringstream invalidInputString;

		// If input is invalid, build the error message.
		if (invalidUpdatedYears) {
			invalidInputString << "Invalid length of investment, please try again ";
		}

		// Display header for updating initial investment.
		cout << Utilities::generateHeader(NUMBER_OF_YEARS_HEADER, HEADER_WIDTH, false, invalidInputString.str());
		// Display original value.
		cout << "Original Number of Years: " << m_years << endl;
		cout << "New Number of Years: ";
		// Prompt for and get the new value.
		cin >> updatedYears;
		// Validate the input.
		invalidUpdatedYears = Utilities::validateInput(cin.fail()) || updatedYears <= 0;

		// If input invalid, skip to the start of the loop.
		if (invalidUpdatedYears) {
			continue;
		}

		// Display separating line after getting input.
		cout << Utilities::repeatingChar('*', HEADER_WIDTH) << endl;

		// Confirm with the user that the input looks correct.
		getInput = !Utilities::confirmation("Are you satisfied with the new length of investment?");
	}

	// Set the new annual length of investment.
	m_years = updatedYears;
}
