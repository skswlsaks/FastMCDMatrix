#ifndef __CHOLESKY_CPP
#define __CHOLESKY_CPP

#include "matrix.h"
#include "Cholesky.h"
#include <iostream>
#include <math.h>

using namespace std;



template <typename T>
QSMatrix<T> Cholesky<T>::decomposition(QSMatrix<T>& A) {
    int i ,j;
    int n = A.get_rows();
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
T Cholesky<T>::determinant(QSMatrix<T> &A) {
	int n = A.get_rows();
    QSMatrix<T> L(decomposition(A));
    T det = 1;
    for (int i = 0; i < n; ++i) {
        det *= L(i, i);
    }
    return pow(det, 2);
}

template <typename T>
QSMatrix<T> Cholesky<T>::inverse(QSMatrix<T> &A) {
	int n = A.get_rows();
    QSMatrix<T> L(decomposition(A));
    QSMatrix<T> inverseL(n, n, 0);
    T sum = 0;

    for (int i = 0; i < n; ++i) {
        inverseL(i, i) = 1 / L(i, i);
        for (int j = i + 1; j < n; ++j) {
            sum = 0;
            for (int k = i; k < j; ++k)
                sum -= L(j, k) * inverseL(k, i);
            inverseL(j, i) = sum / L(j, j);
        }
    }
    return inverseL;
}


#endif

