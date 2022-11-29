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
	std::vector <double> solve_matrix( std::vector<std::vector<double>>& a,  std::vector<double> &b);

	std::vector<double> fit(std::vector<double> X, std::vector<double> Y);

	std::vector<double> predict(std::vector<double> X);

};

