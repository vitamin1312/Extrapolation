#pragma once
#include <iostream>
#include <vector>

const float ErrIncorrectAlpha = -1.0;

/*
Реализация молели экспоненциального сглаживания.

@param[in] time_series Временной ряд.
@param[in] alpha Коэффициент сглаживания между 0 и 1.
@param[in] s0 инициализированное первое значение S.

@return Прогнозное значение.
*/
float exponential_smoothing(std::vector<double> x, std::vector<double> y, std::vector<double> x1, float alpha, float s0);



