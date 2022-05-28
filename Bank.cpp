//
// Created by Eric Slutz on 5/27/22.
//
#include <iostream>

#include "Bank.h"
#include "Utilities.h"

using namespace std;

Bank::Bank(double t_initialInvestment, double t_monthlyDeposit, double t_annualInterestRate, unsigned int t_years) {
	this->m_initialInvestment = t_initialInvestment;
	this->m_monthlyDeposit = t_monthlyDeposit;
	this->m_annualInterestRate = t_annualInterestRate;
	this->m_months = t_years * 12;
}

Bank Bank::startInvestment() {
	double initialInvestment, monthlyDeposit, interestRate;
	unsigned int years;

	cout << Utilities::repeatingChar('*', 64) << endl;
	cout << Utilities::alternatingChar('*', ' ', 26) << " DATA INPUT " << Utilities::alternatingChar(' ', '*', 26) << endl;
	cout << Utilities::repeatingChar('*', 64) << endl;

	cout << "Initial Investment Amount: $";
	cin >> initialInvestment;
	cout << "Monthly Deposit: $";
	cin >> monthlyDeposit;
	cout << "Annual Interest: %";
	cin >> interestRate;
	cout << "Number of Years: ";
	cin >> years;

	return {initialInvestment, monthlyDeposit, interestRate, years};
}
