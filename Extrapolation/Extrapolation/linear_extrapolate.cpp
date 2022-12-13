#include <vector>

std::vector<double> linear_extrapolate(std::vector<double> X, std::vector<double> Y, std::vector<double> x_predict)
{
    double diff_sum = 0;
    for (size_t i = 1; i < X.size(); ++i)
    {
        diff_sum += Y[i] - Y[i - 1];
    }

      double last_x = X.back();
     double last_y = Y.back();

     double N = last_x - X[0];

     double delta = diff_sum / N;

    std::vector<double> result;

    for ( double x;;)
    {
        result.push_back((x - last_x) * delta + last_y);
    }

    return result;

}