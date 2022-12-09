#pragma once
#include <vector>
#include <cmath>
class mnk_gradient
{
private:
	int power=1;
	int niter=100;
	double lmd=0.01;
	std::vector<double> params;
public:

	std::vector<double> predicted(std::vector<double> X);
	void Minimize(std::vector<double> X, std::vector<double> Y);

};

