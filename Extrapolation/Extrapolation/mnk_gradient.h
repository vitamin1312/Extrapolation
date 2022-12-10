#pragma once
#include <vector>
#include <cmath>
class mnk_gradient
{
private:
	int power=3;
	int niter=10000;
	double lmd=0.0000000000001;
	std::vector<double> params;
public:

	
	void Minimize(std::vector<double> X, std::vector<double> Y);
	std::vector<double> Predicted(std::vector<double> X);
	std::vector<double> PredictValues(std::vector<double> X, std::vector<double> Y, std::vector<double> x_test);
};

