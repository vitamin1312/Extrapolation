#pragma once
#include "utils.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>



long double mae(std::vector<double> y_true, std::vector<double> y_predicted);

long double SMAPE(std::vector<double> y_true, std::vector<double> y_predicted);

long double r2_score(std::vector<double> y_true, std::vector<double> y_predicted);

std::ostream& operator << (std::ostream& out, std::vector<double>& vect);

std::pair<std::vector<double>, std::vector<double>> read_file(std::string file_path);

void write_file(std::string file_path, std::vector<double> x_test, std::vector<double> y_test, std::vector<double> prediction);

std::pair<std::vector<double>, std::vector<double>> split_vector(std::vector<double> vect, double split);