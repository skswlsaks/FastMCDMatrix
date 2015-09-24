#include "Sampling.h"
#include "matrix.h"
#include "Calculation.h"
#include "Cholesky.h"
#include <vector>
#include <ctime>
#include <algorithm>
#include <stdlib.h>

using namespace std;

// p is column number of data, i is counter for random number
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
		srand((i + 1) * (count + 1) * (int) time(0));
		int tmp = rand() % n;
		if (find(indexOfData, indexOfData + p, tmp) == indexOfData + p) {
			sample.row_copy(count, data.row(tmp));
			indexOfData[count] = tmp;
			++count;
		}
	} while (count < p);
//	double det = detOfSample(sample);
//	if (det == 0) {
//
//	}
	return sample;
}

double Sampling::detOfSample(QSMatrix<double> s) {
	Calculations<double> cal(data);
	vector<double> mu = cal.mean_col(s);
	QSMatrix<double> cov = cal.covariance(mu, s);
	cov.print();
	Cholesky<double> cho;
	double det = cho.determinant(cov);
	return det;
}

