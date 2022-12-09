#pragma once
#include<iostream>
#include <vector>
#include<math.h>

class mnk_reg
{
private:
	unsigned short int power = 1;
	double lmd = 0;
	std::vector <double> K;
public:

	mnk_reg(unsigned short int pow, double l)
	{
		power = pow;
		lmd = l;
	}

	std::vector <double> solve_matrix( std::vector<std::vector<double>>& a,  std::vector<double> &b);

	void fit(std::vector<double> X, std::vector<double> Y);

	std::vector<double> predict(std::vector<double> X);

	std:: vector<double> fit_predict(std::vector<double>X, std::vector<double>Y, std::vector<double> x_test);

	void set_params(int count);
};

