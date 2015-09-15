#ifndef FASTMCD2_SAMPLING_H
#define FASTMCD2_SAMPLING_H


#include <vector>
#include "matrix.h"

using namespace std;

class Sampling {
private:
    QSMatrix<double> data;

public:

    Sampling(QSMatrix<double>& dat) :data(dat) {};
    ~Sampling() {};


    QSMatrix<double> randomSampling(int p, int i);
};





#endif //FASTMCD2_SAMPLING_H
