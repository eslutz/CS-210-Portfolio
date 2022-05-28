#include <iostream>

#include "Bank.h"

using namespace std;

int main() {
	Bank airgead = Bank::startInvestment();

	cout << airgead.getInvestmentLength();


	return 0;
}
