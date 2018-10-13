/*
 * dataview.hpp
 *
 *  Created on: Sep 30, 2017
 *      Author: Tala Abuadas
 */

#ifndef DATAVIEW_HPP_
#define DATAVIEW_HPP_

#include "simpledraw.hpp"

void barGraph() {
	glColor3f(0.0, 0.0, 0.0);
	drawRectangle(40, 20, 602, 439, true);

	glColor3f(1.0, 0.0, 0.0);
	drawRectangle(192, 439 - data[0] * 3, 274, 439, false);

	glColor3f(0.0, 1.0, 0.0);
	drawRectangle(286, 439 - data[1] * 3, 368, 439, false);

	glColor3f(0.0, 0.0, 1.0);
	drawRectangle(380, 439 - data[2] * 3,  462, 439, false);
}

void pieGraph() {
	GLfloat DEG2RAD = 3.14159/180;
	GLfloat degInRad = 0;
	GLfloat colours[3][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}};
	int radius = getCircleRadius(300, 200, 350, 350);
	int i, j;


	for (j = 0; j < 3; j++) {
		glColor3fv(colours[j]);

		glBegin(GL_POLYGON);
		glVertex2f(321, 230);

		for (i = 0; i < 360 * data[j] / 100; i++) {
			degInRad += DEG2RAD;
			glVertex2f(321 + cos(degInRad) * radius, 230 + sin(degInRad) * radius);
		}

		glEnd();
		degInRad -= DEG2RAD;
	}
}

#endif /* DATAVIEW_HPP_ */
