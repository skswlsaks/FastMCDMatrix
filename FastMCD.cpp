#include <iostream>
#include "Scanner.h"
#include "Visualisation.h"
#include "Execution.h"

using namespace std;

extern QSMatrix<double> data;

int main(int argc, char **argv) {

    Scanner *scanner = new Scanner();
    scanner->file(argc, argv);

    
    Execution e;
    e.step4();

    delete scanner;
    
    Visualisation v;
    v.loadVisualisation(argc, argv);
    
    // TODO:
    /* 1) Further debugging on Execution step (it seems working now)
     * 2) Visualization with opengl or with other tools
     * 3) chi-square algorithm can be added
     */

    return 1;

}