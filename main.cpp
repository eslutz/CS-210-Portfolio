#include <iostream>

#include "Bank.h"

using namespace std;

int main() {
	bool quitProgram = false;
	Bank airgead = Bank::startInvestment();

	while (!quitProgram) {
		auto userSelection = Bank::getBankMenuSelection();
		switch (userSelection) {
			case 1:
				airgead.getInvestmentReport(true);
				break;
			case 2:
				airgead.getInvestmentReport();
				break;
			case 3:
				airgead.setInitialInvestment();
				break;
			case 4:
				airgead.setMonthlyDepositAmount();
				break;
			case 5:
				airgead.setAnnualInterestRate();
				break;
			case 6:
				airgead.setLengthOfInvestment();
				break;
			case 7:
				quitProgram = true;
				cout << endl << "Thank you for investing with Airgad Banking!" << endl;
				break;
		}
	}

	return 0;
}
