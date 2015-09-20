#ifndef __CALCULATION_CPP
#define __CALCULATION_CPP

#include "Calculation.h"


template <typename T>
vector<T> Calculations<T>::mean_col(QSMatrix<T> &m) {
    int cols = m.get_cols();
    int rows = m.get_rows();
    vector<T> result(cols);
    T sum = 0;
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            sum += m(j, i);
        }
        result[i] = sum/rows;
        sum = 0;
    }
    return result;
}

template <typename T>
QSMatrix<T> Calculations<T>::covariance(vector<T> &mean,
                                        QSMatrix<T> &m) {
    int cols = m.get_cols();
    int rows = m.get_rows();
    QSMatrix<T> centered(rows, cols, 0);
    centered = m - mean;
    QSMatrix<T> sum(cols, cols, 0);
    for (int i = 0; i < rows; ++i) {
        vector<T> tmp = centered.row(i);
        sum += transposeMultiply(tmp);
    }
    return sum/(rows-1);
}

template <typename T>
vector<T> Calculations<T>::mahDistance(vector<T> &mean,
                                       QSMatrix<T> &cov) {
    int n = data.get_rows();
    int m = data.get_cols();
    vector<T> md(n);

    Cholesky<T> cho;
    cov = cho.inverse(cov);

    for (int i = 0; i < n; ++i) {
        vector<T> tmp(n);
        for (int j = 0; j < m; ++j)
            tmp[j] = (data.row(i))[j] - mean[j];
        md[i] = mahProduct(tmp, cov);
    }
    return md;
}

template <typename T>
T Calculations<T>::mahProduct(vector<T> &centered,
                              QSMatrix<T> &inversecov) {
    vector<T> tmp = inversecov * centered;
    T sum = 0;
    for (int i = 0; i < centered.size(); ++i) {
        sum += centered[i] * tmp[i];
    }
    return sum;
}

// Transpose matrix and multiply itself
template <typename T>
QSMatrix<T> Calculations<T>::transposeMultiply(vector<T> &v) {
    int size = (int) v.size();
    QSMatrix<T> result(size, size, 0);
    #pragma omp parallel for
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result(i, j) = v[i] * v[j];
        }
    }
    return result;
};

template <typename T>
QSMatrix<T> Calculations<T>::Cstep(QSMatrix<T> &Hold, int h) {
    vector<T> Told = mean_col(Hold);
    QSMatrix<T> Sold = covariance(Told, Hold);
    vector<T> md = mahDistance(Told, Sold);
    vector<size_t> index = sort_indexes(md);
    QSMatrix<T> out(h, Hold.get_cols(), 0);
    for (int i = 0; i < h; ++i) {
        out.row(i) = data.row((const unsigned int &) index[i]);
    }
    return out;
}

template <typename T>
T Calculations<T>::median(vector<T> &v) {
	int size = (int) v.size();
	return v[(int) (size+1)/2];
}

#endif