#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Invest{
public:
	void Hello();
	void SetUserInput(double t_initial, double t_dep, double t_annInt, int t_years);
	void CurrBalNoDep();
	void CurrBalWDep();
	void Print();
	void EndScreen();
	vector <string> yesDeposit;
	vector <string> noDeposit;

private:
	double m_investAmt;
	double m_deposit;
	double m_compInt;
	int m_numYears;

};

