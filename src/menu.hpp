/*
 * menu.hpp
 *
 *  Created on: Sep 30, 2017
 *      Author: Tala Abuadas
 */

#ifndef MENU_HPP_
#define MENU_HPP_
#include "simpledraw.hpp"
#include "gfile.hpp"

void mainMenu (GLint menu)
{
   switch (menu) {
	   case 1:
		   for (int i = 0; i < numObj; i++) {
			   list[i].t = 0;
		   }

		   tool = 1;
		   numObj = 0;
		   move = 0;

		   deselectObject();

		   break;
	   case 2:
		   exit(0);
   }

   glutPostRedisplay();
}

void colourMenu (GLint colour)
{
	if (tool > 2) {
		tool = 1;
	}

	switch (colour) {
		case 1:
			red = 1.0; green = 1.0; blue = 1.0; break; // white
		case 2:
			red = 0.0, green = 0.0, blue = 0.0; break; // black
		case 3:
			red = 1.0; green = 0.0; blue = 0.0; break; // red
		case 4:
			red = 1.0, green = 1.0, blue = 0.0; break; // yellow
		case 5:
			red = 0.0; green = 1.0; blue = 0.0; break; // green
		case 6:
			red = 0.0, green = 1.0, blue = 1.0; break; // cyan
		case 7:
			red = 0.0; green = 0.0; blue = 1.0; break; // blue
		case 8:
			red = 1.0, green = 0.0, blue = 1.0; // magenta
	}

   glutPostRedisplay();
}

void drawMenu (GLint shape) {
	selection = 0;
	tool = 1;
	type = shape;
}

void styleMenu (GLint shapeStyle) {
	selection = 0;
	tool = 1;
	style = shapeStyle;
}

void editMenu (GLint edit) {
	tool = 2;

	switch (edit) {
		case 1:
			selection = 1;
			break;
		case 2:
			deselectObject();
			break;
		case 3:
			deleteObject(selected);
			break;
		case 4:
			bringToFront(selected);
			break;
		case 5:
			bringToBack(selected);
			break;
		case 6:
			move = 1;
	}

	glutPostRedisplay();
}

void fileMenu (GLint file) {
	if (tool > 2) {
		tool = 1;
	}

	switch (file) {
		case 1:
			readSvg("output.xml");
			break;
		case 2:
			saveSvg("output.xml");
			break;
		case 3:
			saveBmp("output.bmp", 0, 0, winWidth, winHeight);
	}
}

void dataMenu (GLint data) {
	switch (data) {
		case 1:
			tool = 3;
			break;
		case 2:
			tool = 4;
	}

	glutPostRedisplay();
}

#endif /* MENU_HPP_ */
