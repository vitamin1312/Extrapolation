#include "exp_smoothing.h"
#include <iostream>
#include <vector>

std::vector<double> exponential_smoothing(std::vector<double> x, std::vector<double> y, std::vector<double> x1, double alpha) {
	if (alpha > 1 || alpha < 0) {
		std::vector <double> result = {};
	/// если параметр alpha задан не корректно, возвращается ошибка
	return result;
	}

	std::vector<double> prediction;

	double predict_value = y[y.size() - 1];
	double fact_value = y[y.size() - 2];

	int len = x1.size();

	for (int i(0); i < len;i++) {

		predict_value = alpha * fact_value + (1 - alpha) * predict_value;
		prediction.push_back(predict_value);
		fact_value = predict_value;
	}

	//for (std::vector<double>::iterator r = y.begin(); r != y.end(); r++) {  // КАК БУДТО ДЛЯ У
	//	fact_value = *r;
	//	predict_value = alpha * fact_value + (1 - alpha) * predict_value;
	//}

	return prediction;
}