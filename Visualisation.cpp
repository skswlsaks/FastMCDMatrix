#ifndef __VISUALISATION_CPP
#define __VISUALISATION_CPP
#include "Visualisation.h"
#include "OpenGL/gl.h"
#include "OpenGL/glu.h"
#include "GLUT/glut.h"


int Visualisation::loadVisualisation(int argc, char * argv[]) {
    //int argc = 1;
    //char *argv[1] = {(char*)"Something"};
    glutInit(&argc, (char **)argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("First Program");
    setupCallRenderer();
    initialSetup();
    setupCallReshape();
    glutMainLoop();
    return 0;
}

void Visualisation::initialSetup(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
}


#endif