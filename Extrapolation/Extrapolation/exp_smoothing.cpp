#include "exp_smoothing.h"
#include <iostream>
#include <vector>

float exponential_smoothing(std::vector<double> x, std::vector<double> y, std::vector<double> x1, float alpha, float s0) {
	if (alpha > 1 || alpha < 0) {
		// если параметр alpha задан не корректно, возвращается ошибка
		return ErrIncorrectAlpha;
	}

	float predict_value = s0;
	float fact_value;

	for (std::vector<double>::iterator r = x.begin(); r != x.end(); r++) {
		fact_value = *r;
		predict_value = alpha * fact_value + (1 - alpha) * predict_value;
	}

	//for (std::vector<double>::iterator r = y.begin(); r != y.end(); r++) {  // КАК БУДТО ДЛЯ У
	//	fact_value = *r;
	//	predict_value = alpha * fact_value + (1 - alpha) * predict_value;
	//}

	return predict_value;
}