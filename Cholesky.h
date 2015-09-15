#ifndef FASTMCD2_MATRIXOPERATION_H
#define FASTMCD2_MATRIXOPERATION_H

#include "matrix.h"
#include <vector>

using namespace std;

template <typename T> class Cholesky {
private:

public:
    Cholesky() {};
    ~Cholesky() {};

    QSMatrix<T> decomposition(int n, QSMatrix<T>& A);
    T determinant(int n, QSMatrix<T>& A);

};

#include "Cholesky.cpp"

#endif

