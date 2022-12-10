#pragma once
#include <vector>
#include <cmath>
class mnk_gradient
{
private:
	int power=1;
	int niter=1;
	double lmd=0;
	std::vector<double> params;
public:
	mnk_gradient(unsigned short int p, int n, double l)
	{
		power = p;
		niter = n;
		lmd = l;
	}
	
	void Minimize(std::vector<double> X, std::vector<double> Y);
	std::vector<double> Predicted(std::vector<double> X);
	std::vector<double> PredictValues(std::vector<double> X, std::vector<double> Y, std::vector<double> x_test);
};

