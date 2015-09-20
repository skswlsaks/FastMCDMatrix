#include <iostream>
#include "Scanner.h"
#include "OpenGL/gl.h"
#include "OpenGL/glu.h"
#include "GLUT/glut.h"
#include "math.h"
#include "Sampling.h"
#include "Cholesky.h"
#include "Calculation.h"

using namespace std;

extern QSMatrix<double> data;

int main(int argc, char **argv) {


    Scanner *scanner = new Scanner();
    scanner->file(argc, argv);
    //data.print();
    
    Sampling sam;
    QSMatrix<double> sample = sam.randomSampling(3, 1);
    sample.print();


    Calculations<double> cal(data);
    
    delete scanner;

    /*vector<double> inner(2);
    vector<vector<double>> v1(2,inner);
    vector<vector<double>> v2(1,inner);
    v1[0][0] = 1;
    v1[0][1] = 2;
    v1[1][0] = 3;
    v1[1][1] = 4;
    scanner.printMatrix(v1, 4);
    MatrixOperation mo;
    scanner.printMatrix(mo.multiply(v1, v2), 3);*/
//
//    vector<double> v(3);
//    v[0] = 2;
//    v[1] = 2;
//    v[2] = 2;
//
//    QSMatrix<double> mat(3, 3, 0.0);
//    mat(0,0) = 25;
//    mat(0,1) = 15;
//    mat(0,2) = -5;
//    mat(1,0) = 15;
//    mat(1,1) = 18;
//    mat(1,2) = 0;
//    mat(2,0) = -5;
//    mat(2,1) = 0;
//    mat(2,2) = 11;
    
    vector<double> m = cal.mean_col(sample);
    QSMatrix<double> cov = cal.covariance(m, sample);
    cov.print();
    vector<double> md = cal.mahDistance(m, cov);
    cout << md[0] << endl;
    cout << md[1] << endl;
    cout << md[1238] << endl;
//
//    mat.print();
//    Cholesky<double> cho;
//    
//    //cho.decomposition(mat).print();
//    cout << cho.determinant(mat) << endl;
//    mat.print();
//    (cho.inverse(mat) * mat).print();


    return 1;

}

