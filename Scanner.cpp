#include <iostream>
#include "Scanner.h"
#include <vector>
#include <fstream>
#include "matrix.h"

using namespace std;

QSMatrix<double> data;

void Scanner::split(const string& s, int rowNum, QSMatrix<double> &data) {
    int count = 0;
    int i = 0;
    int j = (int) s.find(deliminator);
    i = ++j;
    j = (int) s.find(deliminator, j);

    while (count < colNum) {
        string tmp = s.substr(i, j-i);
        data(rowNum, count) = atof(tmp.c_str());
        i = ++j;
        j = (int) s.find(deliminator, j);

        ++count;
    }
}

void Scanner::loadfile(char **argv, int n, QSMatrix<double> &data) {

    ifstream in(argv[1]);
    string tmp;
    int rowNumCount = 0;
    // Get rid of first line (they are titles)
    getline(in, tmp, '\n');

    while (!in.eof()) {
        if(rowNumCount == n) break;
        getline(in, tmp, '\n');
        split(tmp, rowNumCount, data);
        tmp.clear();
        ++rowNumCount;
    }
}

int Scanner::getMatrixSize(char **argv) {
    ifstream in(argv[1]);
    if (!in)
        cout << "ERROR loading file!" << endl;
    string tmp;
    int rowNum = 0;
    while (!in.eof()) {
        getline(in, tmp, '\n');
        ++rowNum;
    }
    return rowNum - 2;
}

void Scanner::file(int argc, char **argv) {

    //if (argc < 2)
        //return ;
    int n = getMatrixSize(argv);
    //QSMatrix<double> data(n, colNum, 0);
    data.resize(n, colNum, 0);
    loadfile(argv, n, data);
    //printMatrix(data, n);
    //return data;
}
