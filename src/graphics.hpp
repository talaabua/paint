/*
 * graphics.hpp
 *
 *  Created on: Sep 30, 2017
 *      Author: Tala Abuadas
 */

#ifndef GRAPHICS_HPP_
#define GRAPHICS_HPP_

#include "simpledraw.hpp"

void setPixel(GLint x, GLint y) {
	glPointSize(3.0);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

int getCircleRadius(GLint x1, GLint y1, GLint x2, GLint y2) {
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int findObject(GLint x, GLint y) {
	for (int i = numObj - 1; i >= 0; i--) {
		if (list[i].t == 1) {
			if ((list[i].x1 <= x && list[i].y1 <= y && list[i].x2 >= x && list[i].y2 >= y) || (list[i].x1 < x && list[i].y1 > y && list[i].x2 > x && list[i].y2 < y) || (list[i].x1 > x && list[i].y1 > y && list[i].x2 < x && list[i].y2 < y) || (list[i].x1 > x && list[i].y1 < y && list[i].x2 < x && list[i].y2 > y)) {
				return i;
			}
		}
		else if (list[i].t == 2) {
			int r = getCircleRadius(list[i].x1, list[i].y1, list[i].x2, list[i].y2);
			int d = sqrt(pow(x - list[i].x1, 2) + pow(y - list[i].y1, 2));
			if (d <= r) {
				return i;
			}
		}
	}
	return -1;
}

void deselectObject() {
	selected = -1;
	line.t = 0;
}

void deleteObject(GLint j)   // j is an index for the selected object
{
	if (j != -1) {
		GLint i;
		for (i = j; i < numObj; i++)
		{
		  list[i].x1 = list[i+1].x1;
		  list[i].y1 = list[i+1].y1;
		  list[i].x2 = list[i+1].x2;
		  list[i].y2 = list[i+1].y2;
		  list[i].r = list[i+1].r;
		  list[i].g = list[i+1].g;
		  list[i].b = list[i+1].b;
		  list[i].t = list[i+1].t;
		  list[i].s = list[i+1].s;
		}
		numObj--;
		deselectObject();
	}
}

void bringToFront(GLint j) {
	if (j != -1) {
		Obj temp = list[j];
		GLint i;
		for (i = j; i < numObj - 1; i++) {
			list[i].x1 = list[i+1].x1;
			list[i].y1 = list[i+1].y1;
			list[i].x2 = list[i+1].x2;
			list[i].y2 = list[i+1].y2;
			list[i].r = list[i+1].r;
			list[i].g = list[i+1].g;
			list[i].b = list[i+1].b;
			list[i].t = list[i+1].t;
			list[i].s = list[i+1].s;
		}
		list[numObj - 1].x1 = temp.x1;
		list[numObj - 1].y1 = temp.y1;
		list[numObj - 1].x2 = temp.x2;
		list[numObj - 1].y2 = temp.y2;
		list[numObj - 1].r = temp.r;
		list[numObj - 1].g = temp.g;
		list[numObj - 1].b = temp.b;
		list[numObj - 1].t = temp.t;
		list[numObj - 1].s = temp.s;
		if (selected == j)
			selected = numObj - 1;
	}
}

void bringToBack(GLint j) {
	if (j != -1) {
		Obj temp = list[j];
		GLint i;
		for (i = j; i > 0; i--) {
			list[i].x1 = list[i-1].x1;
			list[i].y1 = list[i-1].y1;
			list[i].x2 = list[i-1].x2;
			list[i].y2 = list[i-1].y2;
			list[i].r = list[i-1].r;
			list[i].g = list[i-1].g;
			list[i].b = list[i-1].b;
			list[i].t = list[i-1].t;
			list[i].s = list[i-1].s;
		}
		list[0].x1 = temp.x1;
		list[0].y1 = temp.y1;
		list[0].x2 = temp.x2;
		list[0].y2 = temp.y2;
		list[0].r = temp.r;
		list[0].g = temp.g;
		list[0].b = temp.b;
		list[0].t = temp.t;
		list[0].s = temp.s;
		if (selected == j)
			selected = 0;
	}
}

void drawRectangle(GLint x1, GLint y1, GLint x2, GLint y2, bool fill) {
	if (!fill) {
		glBegin(GL_LINE_LOOP);
		glVertex2i(x1, y1);
		glVertex2i(x1, y2);
		glVertex2i(x2, y2);
		glVertex2i(x2, y1);
		glEnd();
	} else {
		glRecti(x1, y1, x2, y2);
	}
}

void circlePlotPoints(GLint xc, GLint yc, GLint x, GLint y) {
	setPixel(xc + x, yc + y); setPixel(xc - x, yc + y);
	setPixel(xc + x, yc - y); setPixel(xc - x, yc - y);
	setPixel(xc + y, yc + x); setPixel(xc - y, yc + x);
	setPixel(xc + y, yc - x); setPixel(xc - y, yc - x);
}

void circlePlotPointsFill(GLint xc, GLint yc, GLint x, GLint y) {
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glVertex2i(xc - x, yc + y); glVertex2i(xc + x, yc + y);
	glVertex2i(xc - x, yc - y); glVertex2i(xc + x, yc - y);
	glVertex2i(xc - y, yc + x); glVertex2i(xc + y, yc + x);
	glVertex2i(xc - y, yc - x); glVertex2i(xc + y, yc - x);
	glEnd();
}

void drawCircle(GLint x1, GLint y1, GLint x2, GLint y2, bool fill) {
	int r = getCircleRadius(x1, y1, x2, y2);
	GLint p = 1 - r;
	GLint x = 0, y = r;
	circlePlotPoints(x1, y1, x, y);
	while (x < y) {
	x++;
	if (p < 0) { p += 2 * x + 1; }
	else { y--; p += 2 * (x - y) + 1; }
	if (fill) circlePlotPointsFill(x1, y1, x, y);
	else circlePlotPoints(x1, y1, x, y);
	}
}



#endif /* GRAPHICS_HPP_ */
