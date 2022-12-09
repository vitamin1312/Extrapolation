#include "mnk_gradient.h"
using namespace std;

std::vector<double> mnk_gradient::predicted(std::vector<double> X)
{
	vector<double> pred;

	return pred;
}


void mnk_gradient::Minimize(vector<double> X, vector<double> Y)
{
	vector<double> grad;
	for (int i = 0; i < power+1; i++)
		params.push_back(i+1);
	

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
		}
		for (int k = 0; k < params.size(); k++)
			params[k] -= lmd * grad[k];
		iter++;
	}
}
