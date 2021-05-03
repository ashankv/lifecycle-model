#include "common.h"
#include <chrono>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#include <omp.h>

// ==============
// Main Function
// ==============

int main(int argc, char** argv) {

    int T = 100;
    std::vector<double> capitals;

    int val = 0;
    for (int i = 0; i < 1000; i++) {
        capitals.push_back(val);
        val += 1000;
    }
    // {0, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000};
    std::vector<double> shocks{1.18772385, 1.10189006, 0.82298979, 0.92860231, 0.94838258, 0.99519267, 1.09067468, 0.80034082, 1.1473326 , 1.0216626};

    std::vector<double> row1{0.09499198921358697, 0.07836207799929175, 0.1113794682731536, 0.10318927619035567, 0.10126831761478525, 0.1158373680829497, 0.08447551247185746, 0.05933922013713437, 0.11402908968418325, 0.13712768033270206};
    std::vector<double> row2{0.07995729751530604, 0.12392808926938513, 0.11937492004881822, 0.07844653290627483, 0.09943986211280402, 0.08702972478002097, 0.07923486031562091, 0.12037054467944906, 0.12044945424166184, 0.09176871413065894};
    std::vector<double> row3{0.10339126044011591, 0.05362920133381445, 0.11543510213464003, 0.14169492611769846, 0.10178139652357225, 0.07329580266790234, 0.12449024571568178, 0.10144911881898722, 0.08222855427510861, 0.10260439197247916};
    std::vector<double> row4{0.12393535913327362, 0.10485192572502545, 0.10045127205122084, 0.12229400758097923, 0.09080528928866764, 0.08031072364239747, 0.10148977147079341, 0.09574667734077387, 0.09447973387363195, 0.08563523989323639};
    std::vector<double> row5{0.14029327725694724, 0.09385280650011672, 0.06900605992400559, 0.0832795132884853, 0.0856833257613877, 0.11170541574435049, 0.09519466516291494, 0.10741912377306731, 0.11276145359758678, 0.10080435899113803};
    std::vector<double> row6{0.11300803745008611, 0.043314794535302306, 0.07390761852057079, 0.11056480334420563, 0.10025926878218175, 0.10898125800355701, 0.10107260957448909, 0.14752018645224418, 0.08509076855288886, 0.1162806547844743};
    std::vector<double> row7{0.08860458485102164, 0.17295404348008306, 0.0694672651669179, 0.10438628545950343, 0.05541813107924698, 0.13809738916845693, 0.09241714632114034, 0.062365349884321, 0.10341095574433107, 0.11287884884497743};
    std::vector<double> row8{0.10227816300699534, 0.08597407720696984, 0.10561642131419433, 0.14752502699251588, 0.11593891906480845, 0.0947412450744879, 0.09617529104974576, 0.09317020162840595, 0.0659356600516059, 0.09264499461027062};
    std::vector<double> row9{0.13660086447671932, 0.08665612822143293, 0.08817033743609531, 0.11270023606984933, 0.07394995046476806, 0.11499403521315354, 0.11646138135935875, 0.1260211093855396, 0.10358540480336667, 0.04086055256971649};
    std::vector<double> row10{0.07098989621435017, 0.11317429535323907, 0.12889981137334117, 0.07890501094481545, 0.11866647483078345, 0.08942329328886595, 0.10629927651961767, 0.10750051862851014, 0.11277960729191831, 0.07336181555455866};

    std::vector<std::vector<double>> P{row1, row2, row3, row4, row5, row6, row7, row8, row9, row10};

//     double P[10][10] = {{0.09499198921358697, 0.07836207799929175, 0.1113794682731536, 0.10318927619035567, 0.10126831761478525, 0.1158373680829497, 0.08447551247185746, 0.05933922013713437, 0.11402908968418325, 0.13712768033270206},
// {0.07995729751530604, 0.12392808926938513, 0.11937492004881822, 0.07844653290627483, 0.09943986211280402, 0.08702972478002097, 0.07923486031562091, 0.12037054467944906, 0.12044945424166184, 0.09176871413065894},
// {0.10339126044011591, 0.05362920133381445, 0.11543510213464003, 0.14169492611769846, 0.10178139652357225, 0.07329580266790234, 0.12449024571568178, 0.10144911881898722, 0.08222855427510861, 0.10260439197247916},
// {0.12393535913327362, 0.10485192572502545, 0.10045127205122084, 0.12229400758097923, 0.09080528928866764, 0.08031072364239747, 0.10148977147079341, 0.09574667734077387, 0.09447973387363195, 0.08563523989323639},
// {0.14029327725694724, 0.09385280650011672, 0.06900605992400559, 0.0832795132884853, 0.0856833257613877, 0.11170541574435049, 0.09519466516291494, 0.10741912377306731, 0.11276145359758678, 0.10080435899113803},
// {0.11300803745008611, 0.043314794535302306, 0.07390761852057079, 0.11056480334420563, 0.10025926878218175, 0.10898125800355701, 0.10107260957448909, 0.14752018645224418, 0.08509076855288886, 0.1162806547844743},
// {0.08860458485102164, 0.17295404348008306, 0.0694672651669179, 0.10438628545950343, 0.05541813107924698, 0.13809738916845693, 0.09241714632114034, 0.062365349884321, 0.10341095574433107, 0.11287884884497743},
// {0.10227816300699534, 0.08597407720696984, 0.10561642131419433, 0.14752502699251588, 0.11593891906480845, 0.0947412450744879, 0.09617529104974576, 0.09317020162840595, 0.0659356600516059, 0.09264499461027062},
// {0.13660086447671932, 0.08665612822143293, 0.08817033743609531, 0.11270023606984933, 0.07394995046476806, 0.11499403521315354, 0.11646138135935875, 0.1260211093855396, 0.10358540480336667, 0.04086055256971649},
// {0.07098989621435017, 0.11317429535323907, 0.12889981137334117, 0.07890501094481545, 0.11866647483078345, 0.08942329328886595, 0.10629927651961767, 0.10750051862851014, 0.11277960729191831, 0.07336181555455866}};

    // Algorithm
    auto start_time = std::chrono::steady_clock::now();

// #ifdef _OPENMP
// #pragma omp parallel default(shared)
// #endif
    // {
    lifecycle(T, capitals, shocks, P);
    // }

    auto end_time = std::chrono::steady_clock::now();

    std::chrono::duration<double> diff = end_time - start_time;
    double seconds = diff.count();

    // Finalize
    std::cout << "Simulation Time = " << seconds << " seconds.\n";
}
