#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include "math.h"
#include "mnk_reg.h"
#include "mnk_gradient.h"
#include "exp_smoothing.h"



long double mae(std::vector<double> y_true, std::vector<double> y_predicted) {

    if (y_true.size() == y_predicted.size()) {

        long double mae = 0;

        for (int i(0); i < y_true.size(); ++i) {
            mae += abs(y_true[i] - y_predicted[i]);
        }

        return mae / y_true.size();
    }

    return -1;
}


long double SMAPE(std::vector<double> y_true, std::vector<double> y_predicted) {

    if (y_true.size() == y_predicted.size()) {

        long double smape = 0;

        for (int i(0); i < y_true.size(); ++i) {
            smape += abs(y_true[i] - y_predicted[i]) / ((abs(y_true[i]) + abs(y_predicted[i])) / 2);
        }

        return smape / y_true.size() * 100;
    }

    return -1;
}


long double r2_score(std::vector<double> y_true, std::vector<double> y_predicted) {
    
    if (y_true.size() == y_predicted.size()) {
        long double mean = 0;

        for (int i(0); i < y_true.size(); ++i) {
            mean += y_true[i];
        }

        mean = mean / y_true.size();

        long double ss_res = 0;
        long double ss_tot = 0;

        for (int i(0); i < y_true.size(); ++i) {
            ss_res += (y_true[i] - y_predicted[i]) * (y_true[i] - y_predicted[i]);
            ss_tot += (y_true[i] - mean) * (y_true[i] - mean);
        }

        return 1 - ss_res / ss_tot;
    }

    return -1;
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

    std::vector<double> x;
    std::vector<double> y;

    if (fin.is_open()) {
        
        double value;

        do {
            fin >> value;
            x.push_back(value);
        } while (fin.peek() != '\n');

        do {
            fin >> value;
            y.push_back(value);
        } while (fin.peek() != '\n');

        if (x.size() == y.size())
            return std::make_pair(x, y);
    }

    x.clear();
    y.clear();

    std::cout << "There are some problems with reading or with data" << std::endl;

    return std::make_pair(x, y);
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

    else
        std::cout << "There are some problems with file" << std::endl;
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


        x = x_y.first;
        y = x_y.second;
        auto x_train_test = split_vector(x);
        auto y_train_test = split_vector(y);
        x_train = x_train_test.first;
        x_test = x_train_test.second;
        y_train = y_train_test.first;
        y_test = y_train_test.second;


        // LSE with regularisation
        mnk_reg LSE_REG(3, 100);  // 3 100

        auto start1 = std::chrono::high_resolution_clock::now();
        prediction = LSE_REG.fit_predict(x_train, y_train, x_test);
        auto stop1 = std::chrono::high_resolution_clock::now();

        auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start1);

        std::cout << "LSE_REG working: " << duration1.count() << " microseconds" << std::endl;
        std::cout << "mean absolute error in file " << name << ": " << mae(y_test, prediction) << std::endl;
        std::cout << "r2 score in file " << name << ": " << r2_score(y_test, prediction) << std::endl;
        std::cout << "SMAPE in file " << name << ": " << SMAPE(y_test, prediction) << "%" << std::endl << std::endl;

        //write_file("data/" + name + "_test", x_test, y_test, prediction);


        // LSE with GD
        mnk_gradient LSE(3, 10, 1000);

        auto start2 = std::chrono::high_resolution_clock::now();
        prediction = LSE.PredictValues(x_train, y_train, x_test);
        auto stop2 = std::chrono::high_resolution_clock::now();

        auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);

        std::cout << "LSE_GRAD working: " << duration2.count() << " microseconds" << std::endl;
        std::cout << "mean absolute error in file " << name << ": " << mae(y_test, prediction) << std::endl;
        std::cout << "r2 score in file " << name << ": " << r2_score(y_test, prediction) << std::endl;
        std::cout << "SMAPE in file " << name << ": " << SMAPE(y_test, prediction) << "%" << std::endl << std::endl;

        //write_file("data/" + name + "_test", x_test, y_test, prediction);

        // EXP_SMOOTHING

        //auto start3 = std::chrono::high_resolution_clock::now();
        ////prediction = exponential_smoothing(x_train, y_train, x_test, 0.5, 1);
        //auto stop3 = std::chrono::high_resolution_clock::now();

        //auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(stop3- start3);

        //std::cout << "LSE_GRAD working: " << duration2.count() << " microseconds" << std::endl;
        //std::cout << "mean absolute error in file " << name << ": " << mae(y_test, prediction) << std::endl;
        //std::cout << "r2 score in file " << name << ": " << r2_score(y_test, prediction) << std::endl;
        //std::cout << "SMAPE in file " << name << ": " << SMAPE(y_test, prediction) << "%" << std::endl << std::endl;

        ////write_file("data/" + name + "_test", x_test, y_test, prediction);


        //// LINEAR EXT

        //auto start4 = std::chrono::high_resolution_clock::now();
        ////prediction = LSE.LINEAR_EXTRAPOLATION(x_train, y_train, x_test);
        //auto stop4 = std::chrono::high_resolution_clock::now();

        //auto duration4 = std::chrono::duration_cast<std::chrono::microseconds>(stop4 - start4);

        //std::cout << "LSE_GRAD working: " << duration2.count() << " microseconds" << std::endl;
        //std::cout << "mean absolute error in file " << name << ": " << mae(y_test, prediction) << std::endl;
        //std::cout << "r2 score in file " << name << ": " << r2_score(y_test, prediction) << std::endl;
        //std::cout << "SMAPE in file " << name << ": " << SMAPE(y_test, prediction) << "%" << std::endl << std::endl;

        ////write_file("data/" + name + "_test", x_test, y_test, prediction);
    }

    return 0;
}
