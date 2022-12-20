#include <iostream>
#include <chrono>
#include "math.h"
#include "mnk_reg.h"
#include "mnk_gradient.h"
#include "exp_smoothing.h"
#include "linear_extrapolate.h"
#include "middle_extrapolate.h"
#include "utils.h"


int main()
{

    std::vector<std::string> file_names = {"0", "1", "2", "3", "4"};
    std::vector<double> x, y, x_train, y_train, x_test, y_test, prediction;


    for (std::string& name : file_names) {
        auto x_y = read_file("data/" + name);


        x = x_y.first;
        y = x_y.second;
        auto x_train_test = split_vector(x, 0.7);
        auto y_train_test = split_vector(y, 0.7);
        x_train = x_train_test.first;
        x_test = x_train_test.second;
        y_train = y_train_test.first;
        y_test = y_train_test.second;


        // LSE with regularisation
        mnk_reg LSE_REG(3, 91);

        auto start1 = std::chrono::high_resolution_clock::now();
        prediction = LSE_REG.fit_predict(x_train, y_train, x_test);
        auto stop1 = std::chrono::high_resolution_clock::now();

        auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start1);

        std::cout << "LSE REG:" << std::endl;
        print_results(duration1.count(), name, y_test, prediction);

        // LSE with GD
        mnk_gradient LSE(3, 10, 1000);

        auto start2 = std::chrono::high_resolution_clock::now();
        prediction = LSE.PredictValues(x_train, y_train, x_test);
        auto stop2 = std::chrono::high_resolution_clock::now();

        auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);

        std::cout << "LSE GD:" << std::endl;
        print_results(duration2.count(), name, y_test, prediction);

        //EXP_SMOOTHING
        auto start3 = std::chrono::high_resolution_clock::now();
        prediction = exponential_smoothing(x_train, y_train, x_test, 0.85);
        auto stop3 = std::chrono::high_resolution_clock::now();

        auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(stop3- start3);

        std::cout << "EXP SMOOTHING:" << std::endl;
        print_results(duration3.count(), name, y_test, prediction);


        // LINEAR EXT
        auto start4 = std::chrono::high_resolution_clock::now();
        prediction = linear_extrapolate(x_train, y_train, x_test);
        auto stop4 = std::chrono::high_resolution_clock::now();

        auto duration4 = std::chrono::duration_cast<std::chrono::microseconds>(stop4 - start4);

        std::cout << "LINEAR EXT:" << std::endl;
        print_results(duration4.count(), name, y_test, prediction);

        // MIDDLE EXT
        auto start5 = std::chrono::high_resolution_clock::now();
        prediction = middle_extrapolate(x_train, y_train, x_test);
        auto stop5 = std::chrono::high_resolution_clock::now();

        auto duration5 = std::chrono::duration_cast<std::chrono::microseconds>(stop5 - start5);

        std::cout << "MIDDLE EXT: " << std::endl;
        print_results(duration5.count(), name, y_test, prediction);
    }

    return 0;
}


