/**
 * Eric Slutz
 * CS-210
 * Project 2
 *
 * Bank Header
 */

#ifndef PROJECT_2_BANK_H
#define PROJECT_2_BANK_H

#include <map>

using namespace std;

/**
 * Bank class for defining the functionality of a bank.
 */
class Bank {
private:
	// Menu options for what can be done with the bank.
	static constexpr string_view bankMenuOptions [] = {
			"View Investment Report With Monthly Deposits",
			"View Investment Report Without Monthly Deposits",
			"Adjust Initial Investment Amount",
			"Adjust Monthly Deposit Amount",
			"Adjust Interest Rate",
			"Adjust Number of Years",
			"Quit"
	};
	// Column titles for the investment reports.
	static const inline map<string, int> reportTableHeader = {
			{"Year", 6},
			{"Year End Balance", 42},
			{"Year End Earned Interest", 42}
	};
	// Private constant for keeping the header width consistent.
	static const int HEADER_WIDTH = 64;
	// Private variables.
	double m_initialInvestment;
	double m_monthlyDeposit;
	double m_annualInterestRate;
	double m_investmentBalance{};
	unsigned int m_years;
public:
	Bank(double t_initialInvestment, double t_monthlyDeposit, double t_annualInterestRate, int t_years);
	static void bankMenu(const string& t_menuInputError = "");
	static unsigned int getBankMenuSelection();
	static Bank startInvestment();
	void getInvestmentReport(bool includeMonthlyDeposit = false);
	void setInitialInvestment();
	void setMonthlyDepositAmount();
	void setAnnualInterestRate();
	void setLengthOfInvestment();
};

#endif //PROJECT_2_BANK_H
