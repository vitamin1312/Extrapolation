#include "exp_smoothing.h"
#include <iostream>
#include <vector>

std::vector<double> exponential_smoothing(std::vector<double> x, std::vector<double> y, std::vector<double> x1, double alpha) {
	std::vector<double> prediction;

	if (alpha > 0 && alpha < 1)
	{
		double predict_value = y[y.size() - 1];
		double fact_value = y[y.size() - 2];

		int len = x1.size();

		for (int i(0); i < len; i++) {

			predict_value = alpha * fact_value + (1 - alpha) * predict_value;
			prediction.push_back(predict_value);
			fact_value = predict_value;
		}
	}
	//for (std::vector<double>::iterator r = y.begin(); r != y.end(); r++) {  // йюй асдрн дкъ с
	//	fact_value = *r;
	//	predict_value = alpha * fact_value + (1 - alpha) * predict_value;
	//}

	return prediction;
}