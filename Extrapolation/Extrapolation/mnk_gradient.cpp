#include "mnk_gradient.h"
using namespace std;

std::vector<double> mnk_gradient::predicted(std::vector<double> params)
{
	vector<double> pred;

	return pred;
}


vector<double> mnk_gradient::Minimize(vector<double> X, vector<double> Y, int power)
{
	vector<double> params;
	vector<double> grad;
	double eps = 0.1;
	double appr = 0.1;
	double gradsum;
	for (int i = 0; i < power+1; i++)
	{
		params.push_back(i+1);
		grad.push_back(i*params[i]*pow(X[i], i));
	}
	double polynom;
	for (int j=0; j<Y.size(); j++)
	{
		if ((Y[j] - polynom) >= appr)
		{
			for (int i(0); i < params.size(); i++)
			{
				gradsum += pow(grad[i], 2);
				params[i] -= eps/sqrt(gradsum) * grad[i];
				grad[i] = (i * params[i] * pow(X[i], i));

			}
		}
	}

	return params;
}
