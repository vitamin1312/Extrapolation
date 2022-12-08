#pragma once
#include <vector>
#include <cmath>
class mnk_gradient
{
private:
	int rate=1;
	double lmd;
	std::vector<double> params;
public:

	std::vector<double> predicted(std::vector<double> params);
	std::vector<double> Minimize(std::vector<double> X, std::vector<double> Y, int power);

};

