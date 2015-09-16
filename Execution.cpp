#include "Execution.h"
#include "Cholesky.h"


QSMatrix<double> Execution::step4() {
    Sampling s;
    Calculations cal;
    Cholesky<double> cho;
    int n = (int) data.get_rows();
    int p = (int) data.get_cols();
    int h = (n + p + 1) / 2;

    vector<double> res(500);
    vector<QSMatrix<double>> sets;

    #pragma omp parallel
    {
        for (int i = 0; i < 500; ++i) {
            QSMatrix<double> J;
            int tmppp = i;
            //do {
            J = s.randomSampling(p + 1, ++tmppp);
            J.print();
            //} while(true);
            vector<double> mu0 = cal.mean_col(J);
            QSMatrix<double> S0 = cal.covariance(mu0, J);
            QSMatrix<double> Hnew = cal.Cstep(J, h);
            Hnew = cal.Cstep(Hnew, h);
            Hnew = cal.Cstep(Hnew, h);
            QSMatrix<double> cov = cal.covariance(cal.mean_col(Hnew), Hnew);
            res[i] = cho.determinant(cov.get_rows(), cov);
            sets.push_back(Hnew);
        }
    };

    vector<size_t> index = Calculations::sort_indexes(res);
    


}


