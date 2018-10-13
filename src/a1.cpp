/*
 * a1.cpp
 *
 *  Created on: Sep 28, 2017
 *      Author: Tala Abuadas
 */

#include "simpledraw.hpp"
#include "menu.hpp"
#include "graphics.hpp"
#include "dataview.hpp"

void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winWidth, winHeight, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glFlush();
}

void drawList() {
	glClear(GL_COLOR_BUFFER_BIT);

	if (tool == 3) {
		barGraph();
	}
	else if (tool == 4) {
		pieGraph();
	}
	else {
		for (int i = 0; i <= numObj; i++) {
			glColor3f(list[i].r, list[i].g, list[i].b);
			if (list[i].t == 1) {
				drawRectangle(list[i].x1, list[i].y1, list[i].x2, list[i].y2, list[i].s != 2);
			}
			else if (list[i].t == 2) {
				drawCircle(list[i].x1, list[i].y1, list[i].x2, list[i].y2, list[i].s != 2);
			}
		}
		glColor3f(line.r, line.g, line.b);
		if (line.t == 1) {
			drawRectangle(line.x1, line.y1, line.x2, line.y2, line.s != 2);
		} else if (line.t == 2) {
			drawCircle(line.x1, line.y1, line.x2, line.y2, line.s != 2);
		}
	}

	glFlush();
}

void mouseDraw(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	if (tool == 1) {
		if (button == GLUT_LEFT_BUTTON && numObj < MaxNumObj - 1) {
			if (action == GLUT_DOWN) {
				list[numObj].x1 = xMouse;
				list[numObj].y1 = yMouse;
				list[numObj].x2 = xMouse;
				list[numObj].y2 = yMouse;
				list[numObj].t = type;
				list[numObj].s = 2;
				list[numObj].r = red;
				list[numObj].g = green;
				list[numObj].b = blue;
			}
			else if (action == GLUT_UP && last == GLUT_DOWN) {
				list[numObj].x2 = xMouse;
				list[numObj].y2 = yMouse;
				list[numObj].s = style;
				numObj++;
			}
			glutPostRedisplay();
		}
	}
	else if (tool == 2) {
		if (button == GLUT_LEFT_BUTTON) {
			if (action == GLUT_DOWN) {
				if (selection == 1) {
					selected = findObject(xMouse, yMouse);

					if (selected == -1) {
						deselectObject();
					}
					else {
						line.x1 = list[selected].x1;
						line.y1 = list[selected].y1;
						line.x2 = list[selected].x2;
						line.y2 = list[selected].y2;
						line.t = list[selected].t;
						line.s = 2;
						line.r = 0.0;
						line.g = 0.5;
						line.b = 0.5;

						if (move == 1) {
							xbegin = xMouse;
							ybegin = yMouse;
							oldLoc.x1 = list[selected].x1;
							oldLoc.y1 = list[selected].y1;
							oldLoc.x2 = list[selected].x2;
							oldLoc.y2 = list[selected].y2;
							oldLoc.t = list[selected].t;
							oldLoc.s = list[selected].s;
							oldLoc.r = list[selected].r;
							oldLoc.g = list[selected].g;
							oldLoc.b = list[selected].b;
							currM = 1;
						}
					}
				}
			}
			else if (action == GLUT_UP && last == GLUT_DOWN) {
				if (move == 1 && selected != -1) {
					int dx = xMouse - xbegin;
					int dy = yMouse - ybegin;

					list[selected].x1 = oldLoc.x1 + dx;
					list[selected].y1 = oldLoc.y1 + dy;
					list[selected].x2 = oldLoc.x2 + dx;
					list[selected].y2 = oldLoc.y2 + dy;
					line.x1 = oldLoc.x1 + dx;
					line.y1 = oldLoc.y1 + dy;
					line.x2 = oldLoc.x2 + dx;
					line.y2 = oldLoc.y2 + dy;
					currM = 0;
				}
			}

			glutPostRedisplay();
		}
		else if (button == GLUT_MIDDLE_BUTTON) {
			deleteObject(selected);
		}
	}

	last = action;
	glFlush();
}

void Motion(GLint x, GLint y) {
	list[numObj].x2 = x;
	list[numObj].y2 = y;

	if (currM == 1) {
		int dx = x - xbegin;
		int dy = y - ybegin;

		list[selected].x1 = oldLoc.x1 + dx;
		list[selected].y1 = oldLoc.y1 + dy;
		list[selected].x2 = oldLoc.x2 + dx;
		list[selected].y2 = oldLoc.y2 + dy;
		line.x1 = oldLoc.x1 + dx;
		line.y1 = oldLoc.y1 + dy;
		line.x2 = oldLoc.x2 + dx;
		line.y2 = oldLoc.y2 + dy;
	}

	glutPostRedisplay();
	glFlush();
}

void winReshapeFcn(GLint newWidth, GLint newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, GLdouble(newWidth), GLdouble(newHeight), 0.0);
	winWidth = newWidth;
	winHeight = newHeight;
	drawList();
	glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    int colour_menu;
    colour_menu = glutCreateMenu (colourMenu);
    glutAddMenuEntry("White", 1);
    glutAddMenuEntry("Black", 2);
    glutAddMenuEntry("Red", 3);
    glutAddMenuEntry("Yellow", 4);
    glutAddMenuEntry("Green", 5);
    glutAddMenuEntry("Cyan", 6);
    glutAddMenuEntry("Blue", 7);
    glutAddMenuEntry("Magenta", 8);

    int draw_menu;
    draw_menu = glutCreateMenu(drawMenu);
    glutAddMenuEntry("Rectangle", 1);
    glutAddMenuEntry("Circle", 2);

    int style_menu;
    style_menu = glutCreateMenu(styleMenu);
    glutAddMenuEntry("Filled", 1);
    glutAddMenuEntry("Outline", 2);

    int edit_menu;
    edit_menu = glutCreateMenu(editMenu);
    glutAddMenuEntry("Select", 1);
    glutAddMenuEntry("Deselect", 2);
    glutAddMenuEntry("Remove", 3);
    glutAddMenuEntry("Bring to Front", 4);
    glutAddMenuEntry("Bring to Back", 5);
    glutAddMenuEntry("Move", 6);

    int file_menu;
    file_menu = glutCreateMenu(fileMenu);
    glutAddMenuEntry("Open SVG File", 1);
    glutAddMenuEntry("Save SVG File", 2);
    glutAddMenuEntry("Export Bitmap File", 3);

    int data_menu;
    data_menu = glutCreateMenu(dataMenu);
    glutAddMenuEntry("Bar", 1);
    glutAddMenuEntry("Pie", 2);

    glutCreateMenu (mainMenu); // Create main pop-up menu.
    glutAddMenuEntry ("New", 1);
    glutAddSubMenu("Draw", draw_menu);
    glutAddSubMenu("Style", style_menu);
    glutAddSubMenu("Colours", colour_menu);
    glutAddSubMenu("Edit", edit_menu);
    glutAddSubMenu("File Operations", file_menu);
    glutAddSubMenu("Data Visualization", data_menu);
    glutAddMenuEntry("Quit", 2);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("SimpleDraw Sample for Assignment 1 (Tala Abuadas)");

    init();
    glutDisplayFunc(drawList);
    glutReshapeFunc(winReshapeFcn);
    glutMouseFunc(mouseDraw);
    glutMotionFunc(Motion);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
}
