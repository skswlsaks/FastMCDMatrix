#include <iostream>
#include "Scanner.h"
#include "Visualisation.h"
#include "Execution.h"
#include "OpenGL/gl.h"
#include "OpenGL/glu.h"
#include "GLUT/glut.h"

using namespace std;

extern QSMatrix<double> data;

vector<int> ind;

void renderer2();
void initialSetup();
int loadVisualisation(int argc, char * argv[], vector<int> o_ind);

int main(int argc, char **argv) {

    Scanner *scanner = new Scanner();
    scanner->file(argc, argv);

    
    //Execution e;
    //ind = e.outlierDetection();

    delete scanner;
    
    Visualisation v;
    loadVisualisation(argc, argv, ind);
    
    // TODO:
    /* 1) Further debugging on Execution step (it seems working now)
     * 2) Visualization with opengl or with other tools
     * 3) chi-square algorithm can be added
     */

    return 1;
}

void initialSetup(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

int loadVisualisation(int argc, char * argv[], vector<int> o_ind) {
    //int argc = 1;
    //char *argv[1] = {(char*)"Something"};
    glutInit(&argc, (char **)argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("First Program");
    glutDisplayFunc(renderer2);
    initialSetup();
    glutReshapeFunc(Visualisation::changeSize);
    glutMainLoop();
    return 0;
}

void renderer2() {
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
    
    // All data points
    glColor3f(0, 0, 1);
    glScalef(20, 20, 20);
    glPointSize(4);
    glBegin(GL_POINTS);
    
    for (unsigned i = 0; i < data.get_rows(); ++i) {
        glVertex3d(data(i, 0), data(i, 1), data(i, 2));
    }
    
    glEnd();
    
    
    // Outlier points
    /*glColor3f(0, 1, 0);
    glScalef(20, 20, 20);
    glPointSize(4);
    
    glBegin(GL_POINTS);
    for(unsigned i = 0; i < o_ind.size(); ++i) {
        glVertex3d(data(o_ind[i], 0),
                   data(o_ind[i], 1),
                   data(o_ind[i], 2));
    }
    glEnd();*/
    glPopMatrix();
    glFlush();
}
