#include "Execution.h"


QSMatrix<double> Execution::step4() {
    Sampling s;
    Calculations<double> cal(data);
    Cholesky<double> cho;
    int n = (int) data.get_rows();
    int p = (int) data.get_cols();
    int h = (n + p + 1) / 2;

    vector<double> res(500);
    vector<QSMatrix<double>> sets(500);

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
            vector<double> mean_tmp = cal.mean_col(Hnew);
            QSMatrix<double> cov = cal.covariance(mean_tmp, Hnew);
            res[i] = cho.determinant(cov);
            sets[i] = (Hnew);
        }
    };

    vector<size_t> index = Calculations<double>::sort_indexes(res);
    
    vector<double> res2(10);
    vector<QSMatrix<double>> sets2(10);
    for (int i = 0; i < 10; ++i) {
    	QSMatrix<double> H = sets[i];
    	for (int j = 0; j < 10; ++j) {
    		H = cal.Cstep(H, h);
    	}
    	vector<double> mean_tmp = cal.mean_col(H);
    	QSMatrix<double> cov = cal.covariance(mean_tmp, H);
    	res2[i] = cho.determinant(cov);
    	sets2[i] = H;
    }
    index = Calculations<double>::sort_indexes(res2);
    return sets2[index[0]];
}

void Execution::reweight(QSMatrix<double> Hnew) {
	Calculations<double> cal(data);
	vector<double> mu = cal.mean_col(Hnew);
	QSMatrix<double> s = cal.covariance(mu, Hnew);
	vector<double> md = cal.mahDistance(mu, s);
	QSMatrix<double> s_rw = s * (cal.median(md) / chisq[mu.size()-1]);
	vector<double> md_rw = cal.mahDistance(mu, s_rw);

}
