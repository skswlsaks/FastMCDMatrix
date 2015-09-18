#ifndef __QS_MATRIX_H
#define __QS_MATRIX_H

#include <vector>

template <typename T> class QSMatrix {
private:
    std::vector<std::vector<T> > mat;
    unsigned rows;
    unsigned cols;

public:
    QSMatrix() {};
    QSMatrix(unsigned _rows, unsigned _cols, const T& _initial);
    QSMatrix(const QSMatrix<T>& rhs);
    virtual ~QSMatrix();

    // Initialise matrix
    void init();

    // Resize
    void resize(unsigned _rows, unsigned _cols, const T& _initial);

    // Copy
    QSMatrix<T>& copy(const QSMatrix<T>& rhs);

    // Operator overloading, for "standard" mathematical matrix operations
    QSMatrix<T>& operator=(const QSMatrix<T>& rhs);

    // Matrix mathematical operations
    QSMatrix<T> operator+(const QSMatrix<T>& rhs);
    QSMatrix<T>& operator+=(const QSMatrix<T>& rhs);
    QSMatrix<T> operator-(const QSMatrix<T>& rhs);
    QSMatrix<T>& operator-=(const QSMatrix<T>& rhs);
    QSMatrix<T> operator*(const QSMatrix<T>& rhs);
    QSMatrix<T>& operator*=(const QSMatrix<T>& rhs);
    QSMatrix<T> transpose();

    // Matrix/scalar operations
    QSMatrix<T> operator+(const T& rhs);
    QSMatrix<T> operator-(const T& rhs);
    QSMatrix<T> operator*(const T& rhs);
    QSMatrix<T> operator/(const T& rhs);

    // Column wise minus
    QSMatrix<T> operator-(const std::vector<T>& rhs);

    // Matrix/vector operations
    std::vector<T> operator*(const std::vector<T>& rhs);
    std::vector<T> diag_vec();

    // Assign row and col
    std::vector<T> row(const unsigned& n);

    // Access the individual elements
    T& operator()(const unsigned& row, const unsigned& col);
    const T& operator()(const unsigned& row, const unsigned& col) const;

    // Print matrix
    void print();

    // Access the row and column sizes
    unsigned get_rows() const;
    unsigned get_cols() const;



};

#include "matrix.cpp"

#endif