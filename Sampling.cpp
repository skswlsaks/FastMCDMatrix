#include "Sampling.h"
#include "matrix.h"
#include <vector>
#include <ctime>
#include <algorithm>
#include <stdlib.h>

using namespace std;


QSMatrix<double> Sampling::randomSampling(int p, int i) {
    int indexOfData[p];
    for (int i = 0; i < p; ++i) {
        indexOfData[i] = -1;
    }

    int count = 0;
    int n = data.get_cols();
    QSMatrix<double> sample(p, n, 0);
    do {
        srand((i+1) * (count+1) * (int) time(0));
        int tmp = rand() % n;
        if (find(indexOfData, indexOfData+p, tmp)
                == indexOfData+p) {
            sample.row(count) = data.row(tmp);
            indexOfData[count] = tmp;
            ++count;
        }
    } while (count < p);
    return sample;
}
