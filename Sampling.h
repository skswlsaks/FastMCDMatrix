#ifndef FASTMCD2_SAMPLING_H
#define FASTMCD2_SAMPLING_H

#include <vector>
#include "matrix.h"

extern QSMatrix<double> data;

class Sampling {

public:

    Sampling() {};
    ~Sampling() {};

    double detOfSample(QSMatrix<double> s);
    QSMatrix<double> randomSampling(int p, int i);
};





#endif //FASTMCD2_SAMPLING_H
