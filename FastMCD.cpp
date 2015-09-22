#include <iostream>
#include "Scanner.h"
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

    //Execution e;
    //e.step4();

    delete scanner;
    
    // TODO:
    /* 1) Further debugging on Execution step (it seems working now)
     * 2) Visualization with opengl or with other tools
     * 3) chi-square algorithm can be added
     */

    return 1;

}

