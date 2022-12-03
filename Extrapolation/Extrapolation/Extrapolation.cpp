#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "math.h"
#include "mnk_reg.h"


double mae(std::vector<double> y_true, std::vector<double> y_predicted) {
    double mae = 0;

    for (int i(0); i < y_true.size(); ++i) {
        mae += abs(y_true[i] - y_predicted[i]);
    }

    return mae/y_true.size();
}


double SMAPE(std::vector<double> y_true, std::vector<double> y_predicted) {
    double smape = 0;

    for (int i(0); i < y_true.size(); ++i) {
        smape += abs(y_true[i] - y_predicted[i]) / ((abs(y_true[i] + abs(y_predicted[i]))) / 2);
    }

    return smape / y_true.size() * 100;
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

    std::vector<std::string> file_names = {"0", "1", "2", "3", "4"};

    std::vector<double> x, y, x_train, y_train, x_test, y_test, prediction;


    for (std::string& name : file_names) {
        auto x_y = read_file("data/" + name);

        mnk_reg LSE(3, 1);

        x = x_y.first;
        y = x_y.second;
        auto x_train_test = split_vector(x);
        auto y_train_test = split_vector(y);
        x_train = x_train_test.first;
        x_test = x_train_test.second;
        y_train = y_train_test.first;
        y_test = y_train_test.second;

        prediction = LSE.fit_predict(x_train, y_train);
        
        std::cout << "mae error in file " << name << ": " << mae(y_train, prediction) << std::endl;
        std::cout << "SMAPE error in file " << name << ": " << SMAPE(y_train, prediction) << "%" << std::endl << std::endl;
    }

    std::vector<double> y_1 = { 3, -0.5, 2, 7 };
    std::vector<double> y_2 = { 2.5, 0.0, 2, 8 };

    std::cout << "_______________________" << std::endl << SMAPE(y_1, y_2);

    return 0;
}
