#ifndef __CHOLESKY_CPP
#define __CHOLESKY_CPP

#include "matrix.h"
#include "Cholesky.h"
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;



template <typename T>
QSMatrix<T> Cholesky<T>::decomposition(int n, QSMatrix<T>& A) {
    int i ,j;
    QSMatrix<T> p(n, 1, 0);
    QSMatrix<T> out(n, n, 0);
    T s = 0;

    QSMatrix<T> a(A);

    for (i = 0; i < n; ++i) {
        s = a(i, i);
        p.init();
        for (j = i; j < n; ++j) {
            if (i == j)
              s = sqrt(s) / s;
            p(j, 0) = a(j, i) * s;
            out(j, i) = a(j, i) * s;
        }
        a -= p * p.transpose();
    }
    return out;
}

template <typename T>
T Cholesky<T>::determinant(int n, QSMatrix<T> &A) {
    QSMatrix<T> decomp(decomposition(n, A));
    T det = 1;
    for (int i = 0; i < n; ++i) {
        det *= decomp(i, i);
    }
    return pow(det, 2);
}





#endif

