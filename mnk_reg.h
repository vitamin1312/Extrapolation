#pragma once
#include<iostream>
#include <vector>
#include<math.h>

class mnk_reg
{
private:
	int power = 1;
	int lmd = 0;
	std::vector <double> K;
public:

	mnk_reg(int pow, int l)
	{
		power = pow;
		lmd = l;
	}

	std::vector <double> solve_matrix( std::vector<std::vector<double>>& a,  std::vector<double> &b);

	void fit(std::vector<double> X, std::vector<double> Y);

	std::vector<double> predict(std::vector<double> X);

	std:: vector<double> fit_predict(std::vector<double>X, std::vector<double>Y);
};

