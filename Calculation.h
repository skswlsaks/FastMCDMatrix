#ifndef FASTMCD2_CALCULATION_H
#define FASTMCD2_CALCULATION_H

#include "matrix.h"
#include "Cholesky.h"
#include <vector>

using namespace std;


template <typename T> class Calculations {
private:
    QSMatrix<T> data;
public:
    Calculations(QSMatrix<T> d) {data = d;};
    ~Calculations() {};
    vector<T> mean_col(QSMatrix<T> &m);
    QSMatrix<T> covariance(vector<T> &mean, QSMatrix<T> &m);
    QSMatrix<T> transposeMultiply(vector<T> &v);
    vector<T> mahDistance(vector<T> &mean, QSMatrix<T> &cov);
    T mahProduct(vector<T> &centered, QSMatrix<T> &inversecov);
    QSMatrix<T> Cstep(QSMatrix<T> &Hold, int h);

    T median(vector<T> &v);

    // Sort vector value and get sorted index
    
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

#include "Calculation.cpp"


#endif //FASTMCD2_CALCULATION_H
