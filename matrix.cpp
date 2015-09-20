#ifndef __QS_MATRIX_CPP
#define __QS_MATRIX_CPP

#include "matrix.h"
#include <iostream>

using namespace std;

// Parameter Constructor
template<typename T>
QSMatrix<T>::QSMatrix(unsigned _rows, unsigned _cols, const T& _initial) {
    mat.resize(_rows);
    for (unsigned i=0; i<mat.size(); i++) {
        mat[i].resize(_cols, _initial);
    }
    rows = _rows;
    cols = _cols;
}

// Copy Constructor
template<typename T>
QSMatrix<T>::QSMatrix(const QSMatrix<T>& rhs) {
    mat = rhs.mat;
    rows = rhs.get_rows();
    cols = rhs.get_cols();
}

// (Virtual) Destructor
template<typename T>
QSMatrix<T>::~QSMatrix() {}

// Initialise matrix to 0
template<typename T>
void QSMatrix<T>::init() {
    for (unsigned i=0; i<rows; i++) {
        for (unsigned j=0; j<cols; j++) {
            mat[i][j] = 0;
        }
    }
}

// Resize
template <typename T>
void QSMatrix<T>::resize(unsigned _rows, unsigned _cols, const T& _initial) {
    QSMatrix<T> tmp(_rows, _cols, _initial);
    mat = tmp.mat;
    rows = _rows;
    cols = _cols;
}

// Copy
template <typename T>
QSMatrix<T>& QSMatrix<T>::copy(const QSMatrix <T> &rhs) {
    mat = rhs.mat;
    rows = rhs.get_rows();
    cols = rhs.get_cols();
}

// Assignment Operator
template<typename T>
QSMatrix<T>& QSMatrix<T>::operator=(const QSMatrix<T>& rhs) {
    if (&rhs == this)
        return *this;

    unsigned new_rows = rhs.get_rows();
    unsigned new_cols = rhs.get_cols();

    mat.resize(new_rows);
    for (unsigned i=0; i<mat.size(); i++) {
        mat[i].resize(new_cols);
    }

    for (unsigned i=0; i<new_rows; i++) {
        for (unsigned j=0; j<new_cols; j++) {
            mat[i][j] = rhs(i, j);
        }
    }
    rows = new_rows;
    cols = new_cols;

    return *this;
}

// Addition of two matrices
template<typename T>
QSMatrix<T> QSMatrix<T>::operator+(const QSMatrix<T>& rhs) {
    QSMatrix result(rows, cols, 0.0);

    for (unsigned i=0; i<rows; i++) {
        for (unsigned j=0; j<cols; j++) {
            result(i,j) = this->mat[i][j] + rhs(i,j);
        }
    }

    return result;
}

// Cumulative addition of this matrix and another
template<typename T>
QSMatrix<T>& QSMatrix<T>::operator+=(const QSMatrix<T>& rhs) {
    unsigned rows = rhs.get_rows();
    unsigned cols = rhs.get_cols();

    for (unsigned i=0; i<rows; i++) {
        for (unsigned j=0; j<cols; j++) {
            this->mat[i][j] += rhs(i,j);
        }
    }

    return *this;
}

// Subtraction of this matrix and another
template<typename T>
QSMatrix<T> QSMatrix<T>::operator-(const QSMatrix<T>& rhs) {
    unsigned rows = rhs.get_rows();
    unsigned cols = rhs.get_cols();
    QSMatrix result(rows, cols, 0.0);

    for (unsigned i=0; i<rows; i++) {
        for (unsigned j=0; j<cols; j++) {
            result(i,j) = this->mat[i][j] - rhs(i,j);
        }
    }

    return result;
}

// Cumulative subtraction of this matrix and another
template<typename T>
QSMatrix<T>& QSMatrix<T>::operator-=(const QSMatrix<T>& rhs) {
    unsigned rows = rhs.get_rows();
    unsigned cols = rhs.get_cols();

    for (unsigned i=0; i<rows; i++) {
        for (unsigned j=0; j<cols; j++) {
            this->mat[i][j] -= rhs(i,j);
        }
    }

    return *this;
}

// Left multiplication of this matrix and another
template<typename T>
inline QSMatrix<T> QSMatrix<T>::operator*(const QSMatrix<T>& rhs) {
    unsigned rows1 = rhs.get_rows();
    unsigned cols1 = rhs.get_cols();
    QSMatrix result(rows, cols1, 0.0);
    #pragma omp parallel for
    for (unsigned i=0; i<rows; i++) {
        for (unsigned j=0; j<cols1; j++) {
            for (unsigned k=0; k<rows1; k++) {
                result(i,j) += this->mat[i][k] * rhs(k,j);
            }
        }
    }

    return result;
}


// Cumulative left multiplication of this matrix and another
template<typename T>
QSMatrix<T>& QSMatrix<T>::operator*=(const QSMatrix<T>& rhs) {
    QSMatrix result = (*this) * rhs;
    (*this) = result;
    return *this;
}

// Calculate a transpose of this matrix
template<typename T>
QSMatrix<T> QSMatrix<T>::transpose() {
    QSMatrix result(cols, rows, 0.0);
    #pragma omp parallel for
    for (unsigned i=0; i<cols; i++) {
        for (unsigned j=0; j<rows; j++) {
            result(i,j) = this->mat[j][i];
        }
    }

    return result;
}

// Matrix/scalar addition
template<typename T>
QSMatrix<T> QSMatrix<T>::operator+(const T& rhs) {
    QSMatrix result(rows, cols, 0.0);
    #pragma omp parallel for
    for (unsigned i=0; i<rows; i++) {
        for (unsigned j=0; j<cols; j++) {
            result(i,j) = this->mat[i][j] + rhs;
        }
    }

    return result;
}

// Matrix/scalar subtraction
template<typename T>
QSMatrix<T> QSMatrix<T>::operator-(const T& rhs) {
    QSMatrix result(rows, cols, 0.0);
    #pragma omp parallel for
    for (unsigned i=0; i<rows; i++) {
        for (unsigned j=0; j<cols; j++) {
            result(i,j) = this->mat[i][j] - rhs;
        }
    }

    return result;
}

// Matrix/scalar multiplication
template<typename T>
QSMatrix<T> QSMatrix<T>::operator*(const T& rhs) {
    QSMatrix result(rows, cols, 0.0);
    #pragma omp parallel for
    for (unsigned i=0; i<rows; i++) {
        for (unsigned j=0; j<cols; j++) {
            result(i,j) = this->mat[i][j] * rhs;
        }
    }

    return result;
}

// Matrix/scalar division
template<typename T>
QSMatrix<T> QSMatrix<T>::operator/(const T& rhs) {
    QSMatrix result(rows, cols, 0.0);
    #pragma omp parallel for
    for (unsigned i=0; i<rows; i++) {
        for (unsigned j=0; j<cols; j++) {
            result(i,j) = this->mat[i][j] / rhs;
        }
    }

    return result;
}

// Column wise minus
template<typename T>
QSMatrix<T> QSMatrix<T>::operator-(const std::vector<T>& rhs) {
    QSMatrix result(rows, cols, 0);
    #pragma omp parallel for
    for (unsigned i=0; i<rows; i++) {
        for (unsigned j=0; j<cols; j++) {
            result(i,j) = this->mat[i][j] - rhs[j];
        }
    }
    return result;
}


// Multiply a matrix with a vector
template<typename T>
std::vector<T> QSMatrix<T>::operator*(const std::vector<T>& rhs) {
    std::vector<T> result(rhs.size(), 0.0);
    for (unsigned i=0; i<rows; i++) {
        T sum = 0;
        for (unsigned j=0; j<cols; j++) {
            sum += this->mat[i][j] * rhs[j];
        }
        result[i] = sum;
    }
    return result;
}

// Obtain a vector of the diagonal elements
template<typename T>
std::vector<T> QSMatrix<T>::diag_vec() {
    std::vector<T> result(rows, 0.0);

    for (unsigned i=0; i<rows; i++) {
        result[i] = this->mat[i][i];
    }

    return result;
}

template<typename T>
std::vector<T> QSMatrix<T>::row(const unsigned& n) {
    return this->mat[n];
}

// Copy entire row
template<typename T>
void QSMatrix<T>::row_copy(int row, std::vector<T> v) {
    (this->mat[row]) = v;
}

// Access the individual elements
template<typename T>
T& QSMatrix<T>::operator()(const unsigned& row, const unsigned& col) {
    return this->mat[row][col];
}

// Access the individual elements (const)
template<typename T>
const T& QSMatrix<T>::operator()(const unsigned& row, const unsigned& col) const {
    return this->mat[row][col];
}

// Print matrix
template<typename T>
void QSMatrix<T>::print() {
    for (int i=0; i < rows; i++) {
        for (int j=0; j < cols; j++) {
            if (j != 0) {
                cout << "\t";
            }
            cout << this->mat[i][j];
        }
        cout << endl;
    }
}

// Get the number of rows of the matrix
template<typename T>
unsigned QSMatrix<T>::get_rows() const {
    return this->rows;
}

// Get the number of columns of the matrix
template<typename T>
unsigned QSMatrix<T>::get_cols() const {
    return this->cols;
}


#endif