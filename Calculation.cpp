#include <vector>
#include "Calculation.h"

vector<double> Calculations::mean_col(QSMatrix<double> m) {
    int cols = m.get_cols();
    int rows = m.get_rows();
    vector<double> result(cols);
    double sum = 0;
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            sum += m(j, i);
        }
        result[i] = sum/rows;
        sum = 0;
    }
    return result;
}

QSMatrix<double> Calculations::covariance(QSMatrix<double> m) {
    int cols = m.get_cols();
    int rows = m.get_rows();
    QSMatrix<double> centered(rows, cols, 0);
    centered = m - mean_col(m);
    QSMatrix<double> sum(cols, cols, 0);
    for (int i = 0; i < rows; ++i) {
        vector<double> tmp = centered.row(i);
        sum += transposeMultiply(tmp);
    }
    return sum/(rows-1);
}

vector<double> Calculations::mahDistance(vector<double> mean,
                                         QSMatrix<double> cov) {
    int n = data.get_rows();
    int m = data.get_cols();
    vector<double> md(n);

    for (int i = 0; i < n; ++i) {
        vector<double> tmp(n);
        for (int j = 0; j < m; ++j)
            tmp[j] = (data.row(i))[j] - mean[j];


    }


}


// Transpose matrix and multiply itself
QSMatrix<double> Calculations::transposeMultiply(vector<double> v) {
    int size = v.size();
    QSMatrix<double> result(size, size, 0);
    #pragma omp parallel for
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result(i, j) = v[i] * v[j];
        }
    }
    return result;
};