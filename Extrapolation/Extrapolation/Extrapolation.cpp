#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
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
        smape += abs(y_true[i] - y_predicted[i]) / ((abs(y_true[i]) + abs(y_predicted[i])) / 2);
    }

    return smape / y_true.size() * 100;
}


double r2_score(std::vector<double> y_true, std::vector<double> y_predicted) {
    double mean = 0;


    for (int i(0); i < y_true.size(); ++i) {
        mean += y_true[i];
    }

    mean = mean / y_true.size();

    double ss_res = 0;
    double ss_tot = 0;

    for (int i(0); i < y_true.size(); ++i) {
        ss_res += (y_true[i] - y_predicted[i]) * (y_true[i] - y_predicted[i]);
        ss_tot += (y_true[i] - mean) * (y_true[i] - mean);
    }

    return 1 - ss_res / ss_tot;
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


void write_file(std::string file_path, std::vector<double> x_test, std::vector<double> y_test, std::vector<double> prediction) {
    std::ofstream fout;
    fout.open(file_path);

    if (fout.is_open()) {
        for (double x : x_test) {
            fout << x << ' ';
        }

        fout << std::endl;


        for (double y : y_test) {
            fout << y << ' ';
        }

        fout << std::endl;


        for (double pred : prediction) {
            fout << pred << ' ';
        }

        fout << std::endl;
    }
}


std::pair<std::vector<double>, std::vector<double>> split_vector(std::vector<double> vect, double split = 0.7) {
    std::size_t const half_size = (int)(vect.size() * 0.65);
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

<<<<<<< Updated upstream
        mnk_reg LSE(5, 0.7);

=======
        
        // data
>>>>>>> Stashed changes
        x = x_y.first;
        y = x_y.second;
        auto x_train_test = split_vector(x);
        auto y_train_test = split_vector(y);
        x_train = x_train_test.first;
        x_test = x_train_test.second;
        y_train = y_train_test.first;
        y_test = y_train_test.second;

        // LSE with regularisation
        mnk_reg LSE(-1, 0);  // 3 100

        auto start = std::chrono::high_resolution_clock::now();
        prediction = LSE.fit_predict(x_train, y_train, x_test);
        auto stop = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        std::cout << "LSE working: " << duration.count() << " microseconds" << std::endl;
        std::cout << "mean absolute error in file " << name << ": " << mae(y_test, prediction) << std::endl;
        std::cout << "r2 score in file " << name << ": " << r2_score(y_test, prediction) << std::endl;
        std::cout << "SMAPE in file " << name << ": " << SMAPE(y_test, prediction) << "%" << std::endl << std::endl;

        write_file("data/" + name + "_test", x_test, y_test, prediction);

    }


    return 0;
}
