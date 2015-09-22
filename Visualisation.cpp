#include "Visualisation.h"


int Visualisation::loadVisualisation(void) {
    glutInit();
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("First Program");
    glutDisplayFunc(renderer2);
    initialSetup();
    glutReshapeFunc(changeSize());
    glutMainLoop();
    return 0;
}


void Visualisation::initialSetup(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void Visualisation::renderer2(void) {
    //GLfloat ang, x, y, z = -50;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glRotatef(45,0,1,0);
    glRotatef(45, 0, 1, 1);
    glPushMatrix();
    
    glColor3f(1,0,0);
    glBegin(GL_LINES);
    glVertex3f(-250.0f, 0, 0);
    glVertex3f(250.0f, 0, 0);
    glVertex3f(0, -250.0f, 0);
    glVertex3f(0, 250.0f, 0);
    glVertex3f(0, 0, -250.0f);
    glVertex3f(0, 0, 250.0f);
    glEnd();
    glPopMatrix();
    glFlush();
}

void Visualisation::changeSize(GLsizei w, GLsizei h) {
    GLfloat sideRange = 200;
    
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-sideRange, sideRange, -sideRange, sideRange, sideRange, -sideRange);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}