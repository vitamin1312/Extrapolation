#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
std::vector<double> middle_extrapolate(std::vector<double> X, std::vector<double> Y, std::vector<double> x_predict)
{
    double diff_sum = 0;
    for (size_t i = 0; i < X.size(); ++i) // определяем среднее значение уровней ряда
    {
        diff_sum += Y[i];
    }

    const double last_x = X.back();
    const double last_y = Y.back();

    const double N = last_x - X[0];

    const double y_med = diff_sum / N; // полученное среднее значение уровней ряда

    double delta;
    delta=0;

    for (size_t i = 0; i < X.size(); ++i) // ищем среднеквадратическое отклонение
    {
        delta += (Y[i] - y_med) * (Y[i] - y_med);
    }

    delta = std::sqrt(delta / N); // полученное среднеквадратическое отклонение

    std::vector<double> result;

    for (const double& x : x_predict) // вычисляем прогнозируемые значения
    {
        result.push_back(delta * (x - last_x) + y_med);
    }

    return result;

}
