/*
 * gfile.hpp
 *
 *  Created on: Sep 30, 2017
 *      Author: Tala Abuadas
 */

#ifndef GFILE_HPP_
#define GFILE_HPP_
#include "simpledraw.hpp"

int saveBmp(const char *ptrcFileName, int nX, int nY, int nWidth, int nHeight)
{
    BITMAPFILEHEADER bf;
    BITMAPINFOHEADER bi;

    unsigned char *ptrImage = (unsigned char*) malloc(sizeof(unsigned char)*nWidth*nHeight*3 + (4-(3*nWidth)%4)*nHeight);

	FILE *ptrFile = fopen(ptrcFileName, "wb");

	glReadPixels(nX, nY, nWidth, nHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, ptrImage);

	memset(&bf, 0, sizeof(bf));
	memset(&bi, 0, sizeof(bi));

	bf.bfType = 0x4d42;
	bf.bfSize = sizeof(bf) + sizeof(bi) + nWidth*nHeight*3 + (4-(3*nWidth)%4)*nHeight;
	bf.bfOffBits = sizeof(bf) + sizeof(bi);
	bi.biSize = sizeof(bi);
	bi.biWidth = nWidth + nWidth%4;
	bi.biHeight = nHeight;
	bi.biPlanes = 1;
	bi.biBitCount = 24;
	bi.biSizeImage = nWidth*nHeight*3 + (4-(3*nWidth)%4)*nHeight;

	fwrite(&bf, sizeof(bf), 1, ptrFile);
	fwrite(&bi, sizeof(bi), 1, ptrFile);
	fwrite(ptrImage, sizeof(unsigned char), nWidth*nHeight*3 + (4-(3*nWidth)%4)*nHeight, ptrFile);

	fclose(ptrFile);
	free(ptrImage);
}

void saveSvg(const char* fileName) {
	FILE *outFile;
	outFile = fopen(fileName, "w");
	char tmp[500];
	int objWidth, objHeight;

	sprintf(tmp, "<?xml version=\"1.0\" standalone=\"no\"?>\n");
	fputs(tmp, outFile);
	sprintf(tmp, "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n");
	fputs(tmp, outFile);
	sprintf(tmp, "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n");
	fputs(tmp, outFile);
	sprintf(tmp,
			"<svg width=\"%d\" height=\"%d\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">\n",
			winWidth, winHeight);
	fputs(tmp, outFile);

	for (int i = 0; i < numObj; i++) {
		if (list[i].t == 1) {
			int topX, topY;

			if (list[i].x2 >= list[i].x1)
			{
				objWidth = list[i].x2 - list[i].x1;
				topX = list[i].x1;
			}
			else
			{
				objWidth = list[i].x1 - list[i].x2;
				topX = list[i].x2;
			}

			if (list[i].y2 >= list[i].y1)
			{
				objHeight = list[i].y2 - list[i].y1;
				topY = list[i].y1;
			}
			else
			{
				objHeight = list[i].y1 - list[i].y2;
				topY = list[i].y2;
			}

			if (list[i].s == 1) {
				sprintf(tmp,
						"<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" style=\"fill:rgb(%d,%d,%d);stroke-width:1;stroke:rgb(%d,%d,%d)\"/>\n",
						topX, topY, objWidth, objHeight,
						(int) (list[i].r * 255), (int) (list[i].g * 255), (int) (list[i].b * 255),
						(int) (list[i].r * 255), (int) (list[i].g * 255), (int) (list[i].b * 255));
				fputs(tmp, outFile);
			}
			else if (list[i].s == 2)
			{
				sprintf(tmp,
						"<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" style=\"fill:none;stroke-width:1;stroke:rgb(%d,%d,%d)\"/>\n",
						topX, topY, objWidth, objHeight,
						(int) (list[i].r * 255), (int) (list[i].g * 255), (int) (list[i].b * 255));
				fputs(tmp, outFile);
			}
		}
		else if (list[i].t == 2) {
			int r = getCircleRadius(list[i].x1, list[i].y1, list[i].x2, list[i].y2);

			if (list[i].s == 1) {
				sprintf(tmp,
						"<circle cx=\"%d\" cy=\"%d\" r=\"%d\" style=\"fill:rgb(%d,%d,%d);stroke-width:2;stroke:rgb(%d,%d,%d)\"/>\n",
						list[i].x1, list[i].y1, r,
						(int) (list[i].r * 255), (int) (list[i].g * 255), (int) (list[i].b * 255),
						(int) (list[i].r * 255), (int) (list[i].g * 255), (int) (list[i].b * 255));
				fputs(tmp, outFile);
			}
			else if (list[i].s == 2)
			{
				sprintf(tmp,
						"<circle cx=\"%d\" cy=\"%d\" r=\"%d\" style=\"fill:none;stroke-width:2;stroke:rgb(%d,%d,%d)\"/>\n",
						list[i].x1, list[i].y1, r,
						(int) (list[i].r * 255), (int) (list[i].g * 255), (int) (list[i].b * 255));
				fputs(tmp, outFile);
			}
		}
	}

	fclose(outFile);
}

void readSvg(const char* fileName) {
	FILE *in;
	char int_chr;
	char prev;
	numObj = 0;
	selection = 0;
	move = 0;

	glutPostRedisplay();

	in = fopen(fileName, "r");

	do {
		prev = int_chr;
		int_chr = fgetc(in);

		if (int_chr == 'r' && prev == '<') {
			list[numObj].t = 1;

			fscanf(in, "ect x=\" %d \" y=\" %d \" width=\" %d \" height=\" %d \" style=\"fill:",
					&list[numObj].x1, &list[numObj].y1, &list[numObj].x2,
					&list[numObj].y2);
			list[numObj].x2 += list[numObj].x1;
			list[numObj].y2 += list[numObj].y1;


			if ((int_chr = fgetc(in)) == 'r') {
				fscanf(in, "gb( %f , %f , %f )", &list[numObj].r,
						&list[numObj].g, &list[numObj].b);
				list[numObj].s = 1;
			} else {
				fscanf(in, "one;stroke-width:1;stroke:rgb( %f , %f , %f )",
						&list[numObj].r, &list[numObj].g, &list[numObj].b);
				list[numObj].s = 2;
			}

			list[numObj].r = list[numObj].r / 255;
			list[numObj].g = list[numObj].g / 255;
			list[numObj].b = list[numObj].b / 255;


			numObj++;
		}
		else if (int_chr == 'c' && prev == '<') {
			list[numObj].t = 2;
			int r;
			const float PI = 3.14159;

			fscanf(in, "ircle cx=\" %d \" cy=\" %d \" r=\" %d \" style=\"fill:",
					&list[numObj].x1, &list[numObj].y1, &r);
			list[numObj].x2 = list[numObj].x1 + r * cos(PI);
			list[numObj].y2 = list[numObj].y1 + r * sin(PI);

			if ((int_chr = fgetc(in)) == 'r') {
				fscanf(in, "gb( %f , %f , %f )", &list[numObj].r,
						&list[numObj].g, &list[numObj].b);
				list[numObj].s = 1;
			} else {
				fscanf(in, "one;stroke-width:2;stroke:rgb( %f , %f , %f )",
						&list[numObj].r, &list[numObj].g, &list[numObj].b);
				list[numObj].s = 2;
			}

			list[numObj].r = list[numObj].r / 255;
			list[numObj].g = list[numObj].g / 255;
			list[numObj].b = list[numObj].b / 255;

			numObj++;
		}
	} while (int_chr != EOF);

	fclose(in);
}



#endif /* GFILE_HPP_ */
