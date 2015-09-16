#include <vector>
#include "Calculation.h"
#include "Cholesky.h"



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

QSMatrix<double> Calculations::covariance(vector<double> mean,
                                          QSMatrix<double> m) {
    int cols = m.get_cols();
    int rows = m.get_rows();
    QSMatrix<double> centered(rows, cols, 0);
    centered = m - mean;
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

    Cholesky<double> cho;
    cov = cho.inverse(cov.get_rows(), cov);

    for (int i = 0; i < n; ++i) {
        vector<double> tmp(n);
        for (int j = 0; j < m; ++j)
            tmp[j] = (data.row(i))[j] - mean[j];
        md[i] = mahProduct(tmp, cov);
    }
    return md;
}

double Calculations::mahProduct(vector<double> centered,
                                QSMatrix<double> inversecov) {
    vector<double> tmp = inversecov * centered;
    double sum = 0;
    for (int i = 0; i < centered.size(); ++i) {
        sum += centered[i] * tmp[i];
    }
    return sum;
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

QSMatrix<double> Calculations::Cstep(QSMatrix<double> Hold, int h) {
    vector<double> Told = mean_col(Hold);
    QSMatrix<double> Sold = covariance(Told, Hold);
    vector<double> md = mahDistance(Told, Sold);
    vector<size_t> index = sort_indexes(md);
    QSMatrix<double> out(h, Hold.get_cols(), 0);
    for (int i = 0; i < h; ++i) {
        out.row(i) = data.row((const unsigned int &) index[i]);
    }
    return out;
}