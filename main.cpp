// Name:
// Quarter, Year:
// Lab:
//
// This file is to be modified by the student.
// main.cpp
////////////////////////////////////////////////////////////
#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include <vector>
#include <cstdio>
#include <math.h>
#include "vec.h"
#include <iostream>

using namespace std;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
vector<vec2> ctrlPoints; //vector to hold the control points

//Return factorial
float factorial(int n) {
	if (n == 0) {
		return 1;
	}
	return n * factorial(n - 1);
}

//Return combination
float combination(int n, int k) {
	return factorial(n) / (factorial(n) * factorial(n - k));
}

//Return binomial
float binomial(int n, int k, float t) {
	return combination(n, k) * pow(t, k) * pow(1 - t, n - k);
}

void GL_render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();

/*
    glBegin(GL_LINES);
    glColor3f(1.0f,0.0f,0.0f);
    glEnd();
    // just for example, remove if desired
    glVertex2f(-.5f,-.5f);
    glVertex2f(.5f,-.5f);
    glVertex2f(.5f,.5f);
    glVertex2f(-.5f,.5f);*/

    //Initialize line using GL_LINE_STRIP
    glBegin(GL_LINE_STRIP);
    //Iterate between 0 and 1; increment by 0.01
    for (float t = 0.0; t < 1.0; t += 0.01) {
	    vec2 tmp;
	    for (unsigned int i = 0; i < ctrlPoints.size(); i++) {
		    tmp = tmp + (binomial(ctrlPoints.size() - 1, i, t) * combination(ctrlPoints.size() - 1, i) * ctrlPoints.at(i));
	    }
	    glColor3f(1.0f, 0.0f, 0.0f);
	    glVertex2f(tmp[0], tmp[1]);
    }
    glEnd();
    glFlush();
}

void GL_mouse(int button,int state,int x,int y)
{
    y=WINDOW_HEIGHT-y;
    GLdouble mv_mat[16];
    GLdouble proj_mat[16];
    GLint vp_mat[4];
    glGetDoublev(GL_MODELVIEW_MATRIX,mv_mat);
    glGetDoublev(GL_PROJECTION_MATRIX,proj_mat);
    glGetIntegerv(GL_VIEWPORT,vp_mat);

    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        double px,py,dummy_z; // we don't care about the z-value but need something to pass in
        gluUnProject(x,y,0,mv_mat,proj_mat,vp_mat,&px,&py,&dummy_z);
	ctrlPoints.push_back(vec2(px, py)); //Push the coordinates where the mouse was clicked
        glutPostRedisplay();
    }
}

//Initializes OpenGL attributes
void GLInit(int* argc, char** argv)
{
    glutInit(argc, argv);
    //glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    //glMatrixMode(GL_PROJECTION_MATRIX);
    //glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
    glutCreateWindow("CS 130 - <Insert Name Here>");
    glutDisplayFunc(GL_render);
    glutMouseFunc(GL_mouse);
}

int main(int argc, char** argv)
{
    GLInit(&argc, argv);
    glutMainLoop();
    return 0;
}
