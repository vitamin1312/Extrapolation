#include "utils.h"


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


std::pair<std::vector<double>, std::vector<double>> split_vector(std::vector<double> vect, double split) {
    std::size_t const half_size = (int)(vect.size() * split);
    std::vector<double> down(vect.begin(), vect.begin() + half_size);
    std::vector<double> up(vect.begin() + half_size, vect.end());

    return std::make_pair(down, up);
}
