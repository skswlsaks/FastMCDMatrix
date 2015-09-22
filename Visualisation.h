#ifndef __Anomaly__Visualisation__
#define __Anomaly__Visualisation__

#include <stdio.h>
#include <math.h>
#include "OpenGL/gl.h"
#include "OpenGL/glu.h"
#include "GLUT/glut.h"


class Visualisation {
public:
    int loadVisualisation(void);
    void renderer2(void);
    void changeSize(GLsizei w, GLsizei h);
    void initialSetup(void);
};




#endif /* defined(__Anomaly__Visualisation__) */
