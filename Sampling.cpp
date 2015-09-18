#include "Sampling.h"
#include "matrix.h"
#include <vector>
#include <ctime>
#include <algorithm>
#include <stdlib.h>

using namespace std;


QSMatrix<double> Sampling::randomSampling(int p, int i) {
    int indexOfData[p];
    for (int j = 0; j < p; ++j) {
        indexOfData[j] = -1;
    }

    int count = 0;
    int n = data.get_rows();
    int cols = data.get_cols();
    QSMatrix<double> sample(p, cols, 0);
    do {
        srand((i+1) * (count+1) * (int) time(0));
        int tmp = rand() % n;
        if (find(indexOfData, indexOfData+p, tmp)
                == indexOfData+p) {
            sample.row_copy(count, data.row(tmp));
            indexOfData[count] = tmp;
            ++count;
        }
    } while (count < p);
    return sample;
}
