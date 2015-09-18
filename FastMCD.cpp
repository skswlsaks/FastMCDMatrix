#include <iostream>
#include "Scanner.h"
#include "OpenGL/gl.h"
#include "OpenGL/glu.h"
#include "GLUT/glut.h"
#include "math.h"

using namespace std;

GLfloat xRotated, yRotated, zRotated;
void init(void)
{
    glClearColor(0,0,0,0);

}

void DrawCube(void)
{

    glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0,0.0,-10.5);
    glRotatef(xRotated,1.0,0.0,0.0);
    // rotation about Y axis
    glRotatef(yRotated,0.0,1.0,0.0);
    // rotation about Z axis
    glRotatef(zRotated,0.0,0.0,1.0);
    glBegin(GL_QUADS);        // Draw The Cube Using quads
    glColor3f(0.0f,1.0f,0.0f);    // Color Blue
    glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Bottom Left Of The Quad (Top)
    glVertex3f( 1.0f, 1.0f, 1.0f);    // Bottom Right Of The Quad (Top)
    glColor3f(1.0f,0.5f,0.0f);    // Color Orange
    glVertex3f( 1.0f,-1.0f, 1.0f);    // Top Right Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f, 1.0f);    // Top Left Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Bottom)
    glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Bottom)
    glColor3f(1.0f,0.0f,0.0f);    // Color Red
    glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Front)
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Front)
    glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Front)
    glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Front)
    glColor3f(1.0f,1.0f,0.0f);    // Color Yellow
    glVertex3f( 1.0f,-1.0f,-1.0f);    // Top Right Of The Quad (Back)
    glVertex3f(-1.0f,-1.0f,-1.0f);    // Top Left Of The Quad (Back)
    glVertex3f(-1.0f, 1.0f,-1.0f);    // Bottom Left Of The Quad (Back)
    glVertex3f( 1.0f, 1.0f,-1.0f);    // Bottom Right Of The Quad (Back)
    glColor3f(0.0f,0.0f,1.0f);    // Color Blue
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Left)
    glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Left)
    glColor3f(1.0f,0.0f,1.0f);    // Color Violet
    glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Right)
    glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Right)
    glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Right)
    glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Right)
    glEnd();            // End Drawing The Cube
    glFlush();
}


void animation(void)
{

    yRotated += 0.01;
    xRotated += 0.02;
    DrawCube();
}


void reshape(int x, int y)
{
    if (y == 0 || x == 0) return;  //Nothing is visible then, so return
    //Set a new projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //Angle of view:40 degrees
    //Near clipping plane distance: 0.5
    //Far clipping plane distance: 20.0

    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);  //Use the whole window for rendering
}


int main(int argc, char **argv) {


    //Scanner *scanner = new Scanner();
    // data = scanner->file(argc, argv);
    //cout << data.row(2)[0];
    //delete scanner;
    //Scanner scanner;

    /*vector<double> inner(2);
    vector<vector<double>> v1(2,inner);
    vector<vector<double>> v2(1,inner);
    v1[0][0] = 1;
    v1[0][1] = 2;
    v1[1][0] = 3;
    v1[1][1] = 4;
    scanner.printMatrix(v1, 4);
    MatrixOperation mo;
    scanner.printMatrix(mo.multiply(v1, v2), 3);*/
//
//    vector<double> v(3);
//    v[0] = 2;
//    v[1] = 2;
//    v[2] = 2;
//
//    QSMatrix<double> mat(3, 3, 0.0);
//    mat(0,0) = 4;
//    mat(0,1) = 12;
//    mat(0,2) = -16;
//    mat(1,0) = 12;
//    mat(1,1) = 37;
//    mat(1,2) = -43;
//    mat(2,0) = -16;
//    mat(2,1) = -43;
//    mat(2,2) = 98;
//
//    mat.print();
    //Cholesky<double> cho;


    //cho.decomposition(3,mat).print();


    glutInit(&argc, argv);
//we initizlilze the glut. functions
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(DrawCube);
    glutReshapeFunc(reshape);
//Set the function for the animation.
    glutIdleFunc(animation);
    glutMainLoop();
    return 0; 

    //return 1;

}

