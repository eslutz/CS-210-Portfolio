//
// Created by Eric Slutz on 5/27/22.
//

#ifndef PROJECT_2_BANK_H
#define PROJECT_2_BANK_H

#include <string>
#include <vector>

using namespace std;

class Bank {
private:
	static constexpr string_view bankMenuOptions [] = {
			"View Investment Report With Monthly Deposits",
			"View Investment Report Without Monthly Deposits",
			"Adjust Initial Investment Amount",
			"Adjust Monthly Deposit Amount",
			"Adjust Interest Rate",
			"Adjust Number of Years",
			"Quit"
	};
	static const int HEADER_WIDTH = 64;
	double m_initialInvestment;
	double m_monthlyDeposit;
	double m_annualInterestRate;
	unsigned int m_months;
	vector<double> m_balance;
	vector<double> m_interestEarned;
public:
	Bank(double t_initialInvestment, double t_monthlyDeposit, double t_annualInterestRate, int t_years);
	static void bankMenu(const string& t_menuInputError);
	static unsigned int getBankMenuSelection();
	static Bank startInvestment();
	string getInvestmentReport(bool includeMonthlyDeposit = false);
	void setInitialInvestment();
	void setMonthlyDepositAmount();
	void setAnnualInterestRate();
	void setLengthOfInvestment();


};

#endif //PROJECT_2_BANK_H
