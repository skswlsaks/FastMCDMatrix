#include <iostream>
#include "Scanner.h"
#include <vector>
#include "matrix.h"
#include "Cholesky.h"

using namespace std;



int main(int argc, char **argv) {

    //Scanner *scanner = new Scanner();
    // data = scanner->file(argc, argv);
    //cout << data.row(2)[0];
    //delete scanner;
    //Scanner scanner;

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

    vector<double> v(3);
    v[0] = 2;
    v[1] = 2;
    v[2] = 2;

    QSMatrix<double> mat(3, 3, 0.0);
    mat(0,0) = 4;
    mat(0,1) = 12;
    mat(0,2) = -16;
    mat(1,0) = 12;
    mat(1,1) = 37;
    mat(1,2) = -43;
    mat(2,0) = -16;
    mat(2,1) = -43;
    mat(2,2) = 98;

    mat.print();
    //Cholesky<double> cho;


    //cho.decomposition(3,mat).print();


    return 1;

}

