#include "common.h"
#include <omp.h>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <iostream>

// Put any static global variables here that you will use throughout the simulation.
double V_memo[100][10][10] = {};

double utility(double consumption, double expected_value) {
    double sigma = 0.5;
    double beta = 0.9;

    return std::pow(consumption, 1 - sigma) / (1 - sigma);
}

double value(t, x, e, T, vector<double>& capitals, vector<double>& shocks, std::vector<std::vector<double>>& P) {

    double best_value = -0.001;

    for (int ix = 0; ix < capitals.size(); ix++) {

        double expected_value = 0.0;

        // double check this indexing
        if (t < T - 1) {
            for (int ie = 0; ie < shocks.size(); ie++) {
                expected_value += P[e][ie] * (V_memo[t+1][ix][ie])
            }
        }

        double consumption = (1 + r) * capitals[x] + shocks[e] * w - capitals[ix]
        double utility = utility(consumption) + beta * expected_value;

        if (consumption <= 0) {
            utility = -0.00001
        }

        if (utility >= best_value) {
            best_value = utility;
        }

    }

    return best_value;
}

void lifecycle(int T, vector<double>& capitals, vector<double>& shocks, std::vector<std::vector<double>>& P) {

    double r = 0.05;
    double w = 10000;

    for (int x = 0; x < capitals.size(); x++) {
        for (int e = 0; e < shocks.size(); e++) {
            V_memo[T - 1][x][e] = utility((1 + r) * capitals[x] + shocks[e] * w);
        }
    }

    for (int t = T - 2; t >= 0; t--) {
        for (int x = 0; x < capitals.size(); x++) {
            for (int e = 0; e < shocks.size(); e++) {
                V_memo[t][x][e] = value(t, x, e, T, capitals, shocks, V_memo);
            }
        }
    }
}
