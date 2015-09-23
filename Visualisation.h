#ifndef __Anomaly__Visualisation__
#define __Anomaly__Visualisation__

#include <stdio.h>
#include <math.h>
#include "OpenGL/gl.h"
#include "OpenGL/glu.h"
#include "GLUT/glut.h"
#include "matrix.h"

extern QSMatrix<double> data;

class Visualisation {
private:

    void setupCallRenderer() {
        ::glutDisplayFunc(Visualisation::renderer2);
    }
    void setupCallReshape() {
        ::glutReshapeFunc(Visualisation::changeSize);
    }
    
public:
    Visualisation() {};
    ~Visualisation() {};
    int loadVisualisation(int argc, char * argv[]);
    void initialSetup(void);
    
    
    static void renderer2(void) {
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

        glColor3f(0, 0, 1);
        glScalef(20, 20, 20);
        glPointSize(4);
        glBegin(GL_POINTS);
        
        for (int i = 0; i < data.get_rows(); ++i) {
            glVertex3d(data(i, 0), data(i, 1), data(i, 2));
        }
        
        glEnd();
        glPopMatrix();
        glFlush();
    }
    
    
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
