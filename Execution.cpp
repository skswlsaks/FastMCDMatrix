#include "Execution.h"
//#include <omp.h>



vector<int> Execution::outlierDetection() {
	Calculations<double> cal(data);

	vector<double> mu = cal.mean_col(data);
	QSMatrix<double> s = cal.covariance(mu, data);

	QSMatrix<double> H_MCD = step4();
	vector<double> mu_MCD = cal.mean_col(H_MCD);
	QSMatrix<double> s_MCD = cal.covariance(mu, H_MCD);
	vector<double> mah_MCD = cal.mahDistance(mu_MCD, s_MCD);

	QSMatrix<double> s_MCD_rw = reweight(mah_MCD, s_MCD);
	vector<double> mah_MCD_rw = cal.mahDistance(mu_MCD, s_MCD_rw);

	vector<int> outlier_ind;
	int q = data.get_cols();
	for (unsigned i = 0; i < data.get_rows(); ++i) {
		if (mah_MCD_rw[i] > chisq[q-1])
			outlier_ind.push_back(i);
	}
	int numOfOutlier = outlier_ind.size();
	QSMatrix<double> outliers(numOfOutlier, q, 0);
	for (int i = 0; i < numOfOutlier; ++i)
		outliers.row_copy(i, data.row(outlier_ind[i]));

	vector<double> muOut = cal.mean_col(outliers);
	QSMatrix<double> SOut = cal.covariance(muOut, outliers);
	vector<double> mahaOut = cal.mahDistance(muOut, SOut);

	vector<int> final_Outlier_ind;
	for (unsigned i = 0; i < data.get_rows(); ++i) {
		if (mahaOut[i] < mah_MCD_rw[i])
			final_Outlier_ind.push_back(i);
	}

	return final_Outlier_ind;
}

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
        #pragma omp for
        for (int i = 0; i < 500; ++i) {
            QSMatrix<double> J;
            int tmppp = i;
            //do {
            J = s.randomSampling(p + 1, ++tmppp);
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

    cout << "Here" << endl;
    
    vector<size_t> index = Calculations<double>::sort_indexes(res);
    
    vector<double> res2(10);
    vector<QSMatrix<double>> sets2(10);
    for (int i = 0; i < 10; ++i) {
    	QSMatrix<double> H = sets[index[i]];
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

QSMatrix<double> Execution::reweight(vector<double> mah, QSMatrix<double> s) {
	Calculations<double> cal(data);
	QSMatrix<double> s_rw = s * (cal.median(mah) / chisq[data.get_cols()-1]);
	return s_rw;
}
