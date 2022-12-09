#include "mnk_reg.h"
#include <vector>
#include <iostream>
#include<math.h>

using namespace std;


vector <double> mnk_reg:: solve_matrix( vector<vector<double>> &a,  vector<double> &b)
{
    vector <vector<double>> matr ;
    for (auto &p : a)
    {
        matr.push_back(p);
    }
    int num = 0;
    for (auto &p : matr)
    {
        p.push_back(b[num]);
        num++;
    }
    
    int length = a.size();
   
    for (int i(0); i < length; i++)
    {
        if (matr[i][i] == 0)
            matr[i].swap(matr[(1 + i) % length]);
        double delitel = matr[i][i];
        for (auto& p : matr[i])
            p /= delitel;

        for (int j = i + 1; j < length; j++)
        {
            double l = matr[j][i];
            for (int k = 0; k <= length; k++)
                matr[j][k] -= matr[i][k] * l;
        }
    }
    for (int i = length - 1; i > 0; --i)
        for (int j = i-1; j >= 0; --j)
        {
            double h = matr[j][i];
            for (int k(0); k <= length; ++k)
                matr[j][k] -= matr[i][k] * h;
        }

    vector<double> x;
    for (auto p : matr)
        x.push_back(p[length]);

    return x;
}

void mnk_reg::fit(vector<double> X, vector<double> Y)
{
    vector<vector<double>> A;
    vector<double> B;
    for (int i(0); i <= power; ++i)
    {
        vector<double> curr;
        for (int j(0); j <= power; ++j)
        {
            if (i == j)
            {
                double sum = 0;
                for (auto p : X)
                    sum += pow(p, i + j) + 2 * lmd;
                curr.push_back(sum);
            }
            else
            {
                double sum = 0;
                for (auto p : X)
                    sum += pow(p, i + j);
                curr.push_back(sum);
            }

        }
        A.push_back(curr);
    }
    for (int i(0); i <= power; ++i)
    {
        int sum = 0;
        for (int j(0); j < X.size(); ++j)
            sum += Y[j] * pow(X[j], i); \
            B.push_back(sum);
    }
    K = solve_matrix(A, B);
}

vector<double> mnk_reg:: predict(vector<double> X)
{
    int length = X.size();
    vector<double> Y;

    for (int i(0); i < length; ++i)
    {
        double sum = 0;
        for (int j(0); j < K.size(); ++j)
            sum+= K[j] * pow(X[i], j);
        Y.push_back(sum);
    }
    return Y;
}

vector<double> mnk_reg::fit_predict(std::vector<double>X, std::vector<double>Y, std::vector<double> x_test)
{
    set_params(X.size());
    fit(X,Y);
    return predict(x_test);
}
void mnk_reg::set_params(int count)
{
    lmd *= count;
}