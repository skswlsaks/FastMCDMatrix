#ifndef __Anomaly__Visualisation__
#define __Anomaly__Visualisation__

#include <stdio.h>
#include <math.h>
#include <vector>
#include "OpenGL/gl.h"
#include "OpenGL/glu.h"
#include "GLUT/glut.h"
#include "matrix.h"
#include "Execution.h"

extern QSMatrix<double> data;

class Visualisation {
private:
    

public:
    Visualisation() {};
    ~Visualisation() {};
    int loadVisualisation(int argc, char * argv[]);
    void initialSetup(void);
    
//    static vector<int> getInd() {
//        return o_ind;
//    }
    

    
    
    static void changeSize(GLsizei w, GLsizei h) {
        GLfloat sideRange = 200;
        
        glViewport(0,0,w,h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-sideRange, sideRange, -sideRange, sideRange, sideRange, -sideRange);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }
    
};

#endif /* defined(__Anomaly__Visualisation__) */
