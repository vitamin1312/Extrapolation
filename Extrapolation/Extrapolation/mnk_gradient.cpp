#include "mnk_gradient.h"
using namespace std;


void mnk_gradient::Minimize(vector<double> X, vector<double> Y)
{
	vector<double> grad;
	vector<double> gsum;
	for (int i = 0; i < power+1; i++)
	{
		params.push_back(i + 1);
		grad.push_back(0);
		gsum.push_back(0);
	}

	

	int iter = 0;
	while (iter < niter)
	{
		for (int p=0; p<params.size(); p++)
		{
			double psum = 0;
			for (int i = 0; i < Y.size(); i++)
			{
				double sum = -Y[i];
				for (int j = 0; j < params.size(); j++)
					sum += params[j] * pow(X[i], j);
				psum += sum * pow(X[i], p);
			}
			grad[p] = psum;
			gsum[p] += pow(grad[p], 2);
		}
		for (int k = 0; k < params.size(); k++)
			params[k] -= ((double)(lmd/sqrt(gsum[k]))) * grad[k];
		iter++;
	}
}


std::vector<double> mnk_gradient::Predicted(std::vector<double> X)
{
	vector<double> pred;
	for (auto x_value : X)
	{
		double sum = 0;
		for (int i = 0; i < params.size(); i++)
			sum += params[i] * pow(x_value, i);
		pred.push_back(sum);
	}

	return pred;
}

std::vector<double> mnk_gradient::PredictValues(std::vector<double> X, std::vector<double> Y, std::vector<double> x_test)
{
	Minimize(X, Y);
	return Predicted(x_test);
}
