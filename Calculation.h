#ifndef FASTMCD2_CALCULATION_H
#define FASTMCD2_CALCULATION_H

#include "Scanner.h"
#include "Sampling.h"
#include "matrix.h"
#include <vector>
#include <algorithm>

using namespace std;

extern QSMatrix<double> data;

class Calculations {
public:
    Calculations() {};
    ~Calculations() {};
    vector<double> mean_col(QSMatrix<double> m);
    QSMatrix<double> covariance(vector<double> mean, QSMatrix<double> m);
    QSMatrix<double> transposeMultiply(vector<double> v);
    vector<double> mahDistance(vector<double> mean, QSMatrix<double> cov);
    double mahProduct(vector<double> centered, QSMatrix<double> inversecov);
    QSMatrix<double> Cstep(QSMatrix<double> Hold, int h);

    // Sort vector value and get sorted index
    template <typename T>
    static vector<size_t> sort_indexes(const vector<T> &v) {

        // initialize original index locations
        vector<size_t> idx(v.size());
        for (size_t i = 0; i != idx.size(); ++i) idx[i] = i;

        // sort indexes based on comparing values in v
        sort(idx.begin(), idx.end(),
             [&v](size_t i1, size_t i2) {return v[i1] < v[i2];});

        return idx;
    }
};




#endif //FASTMCD2_CALCULATION_H
