/*
 * simpledraw.hpp
 *
 *  Created on: Sep 30, 2017
 *      Author: Tala Abuadas
 */

#ifndef SIMPLEDRAW_HPP_
#define SIMPLEDRAW_HPP_

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include <iostream>

using namespace std;

#define MaxNumObj 100
#define GL_BGR_EXT 0x80E0

void mainMenu(GLint menuOption);
void setPixel(GLint, GLint);
int getCircleRadius(GLint, GLint, GLint, GLint);

int findObject(GLint, GLint);
void deselectObject();
void deleteObject(GLint);
void bringToFront(GLint);
void bringToBack(GLint);

void drawRectangle(GLint, GLint, GLint, GLint, bool);
void circlePlotPoints(GLint, GLint, GLint, GLint);
void circlePlotPointsFill(GLint, GLint, GLint, GLint);
void drawCircle(GLint, GLint, GLint, GLint, bool);

typedef class modelObject {
	public:
		GLint x1, y1, x2, y2, t, s;
		GLfloat r, g, b;
} Obj;

typedef class Point {
	public:
		GLint x, y;
		GLfloat r, g, b;
} Pt;

Obj list[100], line, oldLoc;
GLsizei winWidth = 640, winHeight = 480;
GLint tool = 1, type = 1, style = 2, selected = -1, selection = 0,
move = 0, currM = 0, xbegin, ybegin, numObj = 0, last = 0;
GLfloat red = 1.0, green = 0.0, blue = 0.0;
GLint data[] = {40, 16, 45};

#endif /* SIMPLEDRAW_HPP_ */
