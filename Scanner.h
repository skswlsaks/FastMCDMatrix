#ifndef __FastMCD__Scanner__
#define __FastMCD__Scanner__

#include <string>
#include <vector>
#include "matrix.h"

using namespace std;

class Scanner {
public:
    Scanner() {};
    ~Scanner() {};
    void file(int argc, char **argv);
    void loadfile(char **argv, int n, QSMatrix<double> &data);
    void split(const string& s, int rowNum, QSMatrix<double> &data);
    int getMatrixSize(char **argv);
    char deliminator = ',';
    int colNum = 1;
};

#endif /* defined(__FastMCD__Scanner__) */
