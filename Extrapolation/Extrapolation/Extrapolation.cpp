#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "math.h"


double mae(std::vector<double> y_true, std::vector<double> y_predicted) {
    double mae = 0;

    for (int i(0); i < y_true.size(); ++i) {
        mae += abs(y_true[i] - y_predicted[i]);
    }

    return mae/y_true.size();
}


std::ostream& operator << (std::ostream& out, std::vector<double>& vect) {
    for (double elem : vect) {
        std::cout << elem << ' ';
    }
    return out;
}


std::pair<std::vector<double>, std::vector<double>> read_file(std::string file_path) {
    std::fstream fin;
    fin.open(file_path);

    if (fin.is_open()) {
        std::vector<double> x;
        std::vector<double> y;

        double value;

        do {
            fin >> value;
            x.push_back(value);
        } while (fin.peek() != '\n');

        do {
            fin >> value;
            y.push_back(value);
        } while (fin.peek() != '\n');

        if (x.size() == y.size()) {
            auto result = std::make_pair(x, y);

            return result;
        }
    }
}


std::pair<std::vector<double>, std::vector<double>> split_vector(std::vector<double> vect, double split = 0.7) {
    std::size_t const half_size = (int)(vect.size() * 0.7);
    std::vector<double> down(vect.begin(), vect.begin() + half_size);
    std::vector<double> up(vect.begin() + half_size, vect.end());

    return std::make_pair(down, up);
}


int main()
{
    auto x_y = read_file("data/1");
    std::vector<double> x, y, x_train, y_train, x_test, y_test;

    x = x_y.first;
    y = x_y.second;

    auto x_train_test = split_vector(x);
    auto y_train_test = split_vector(y);

    x_train = x_train_test.first;
    x_test = x_train_test.second;

    y_train = y_train_test.first;
    y_test = y_train_test.second;

    /*
    prediction = Extrapolator(x_train, y_train, x_test)

    std::cout << "mae of this method: " << mae(y_test, prediction) << std::endl;
    */   

}
