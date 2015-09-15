#ifndef FASTMCD2_CALCULATION_H
#define FASTMCD2_CALCULATION_H

#include "Scanner.h"
#include "Sampling.h"
#include "matrix.h"
#include <vector>

using namespace std;

extern QSMatrix<double> data;

class Calculations {
public:
    Calculations() {};
    ~Calculations() {};
    vector<double> mean_col(QSMatrix<double> m);
    QSMatrix<double> covariance(QSMatrix<double> m);
    QSMatrix<double> transposeMultiply(vector<double> v);
    vector<double> mahDistance(vector<double> mean, QSMatrix<double> cov);
    QSMatrix<double> Cstep(QSMatrix<double> Hold, int h);
};




#endif //FASTMCD2_CALCULATION_H
