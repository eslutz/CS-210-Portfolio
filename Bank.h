//
// Created by Eric Slutz on 5/27/22.
//

#ifndef PROJECT_2_BANK_H
#define PROJECT_2_BANK_H

#include <vector>

using namespace std;

class Bank {
private:
	double m_initialInvestment;
	double m_monthlyDeposit;
	double m_annualInterestRate;
	unsigned int m_months;
	vector<double> m_balance;
	vector<double> m_interestEarned;
	double computeInterest();
public:
	Bank(double t_initialInvestment, double t_monthlyDeposit, double t_annualInterestRate, unsigned int t_years);
	double getInitialInvestment();
	void setInitialInvestment(double t_investmentAmount);
	double getMonthlyDeposit();
	void setMonthlyDeposit(double t_monthlyDeposit);
	double getAnnualInterestRate();
	void setAnnualInterestRate(double t_annualInterestRate);
	double getInvestmentLength(){return m_months;};
	void setInvestmentLength(double t_years);
	static void bankMenu();
	static Bank startInvestment();
	string getInvestmentReport(bool includeMonthlyDeposit = false);
};

#endif //PROJECT_2_BANK_H
