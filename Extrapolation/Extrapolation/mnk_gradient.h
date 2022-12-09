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

	
	void Minimize(std::vector<double> X, std::vector<double> Y);
	std::vector<double> Predicted(std::vector<double> X);
	std::vector<double> PredictValues(std::vector<double> X, std::vector<double> Y, std::vector<double> x_test);
};

