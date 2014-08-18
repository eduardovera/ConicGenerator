/**
 Conic Generator
 Main.cpp
 @author Eduardo Vera Sousa
*/

#include "stdafx.h"
#include <iostream>
#include <opencv2\opencv.hpp>
#include "Eigen\Dense"
#include <float.h>

using namespace std;
using namespace Eigen;
using namespace cv;

VectorXf getCoefficients(Vector2i points[]) {
	Mat1f matrixPoints(5, 6);
	Mat1f matrixResults(6, 1, 0.0);
	Mat1f X;

	for (int j = 0; j < matrixPoints.rows; j++) {
		matrixPoints(j, 0) = points[j][0] * points[j][0];
		matrixPoints(j, 1) = points[j][0] * points[j][1];
		matrixPoints(j, 2) = points[j][1] * points[j][1];
		matrixPoints(j, 3) = points[j][0];
		matrixPoints(j, 4) = points[j][1];
		matrixPoints(j, 5) = 1;
	}

	SVD::solveZ(matrixPoints, X);

	VectorXf coefficients(6);

	for (int i = 0; i < X.rows; i++) {
		coefficients(i) = X(i, 0);
	}
	return coefficients;
}

void colorPixel(Vector2i point, Mat3i *image) {
	(*image).at<Vec3i>(point[0], point[1]) = Vec3i(0, 0, 0);
}

Vector2i getBestPixelAroundPoint(Vector2i point, VectorXf coefficients) {
	Vector2i bestPixel = point;
	float minValue = FLT_MAX;
	float value = 0;

	for (int j = point[1] - 1; j <= point[1] + 1; j++) {
		for (int i = point[0] - 1; i <= point[0] + 1; i++) {
			if (i != point[0] || j != point[1]) {
				if (i > 0 && i < 100 && j > 0 && j < 100) {
					value = coefficients[0] * (i*i) + coefficients[1] * (i*j) + coefficients[2] * (j*j) + coefficients[3] * (i) + coefficients[4] * (j) + coefficients[5];
					if (value < minValue) {
						minValue = value;
						bestPixel = Vector2i(i, j);
					}
				}
			}
		}
	}
	return bestPixel;
}

void drawPoints(Vector2i *points, int length, VectorXf coefficients) {
	Mat3i image(500, 500, Vec3i(255, 255, 255));

	// ALTERNATIVA 1 (WHY?)
/*	for (int i = 0; i < length; i++) {
		int k = 100;
		colorPixel(points[i], &image);
		Vector2i p = points[i];
		while (k != 0) {
			p = getBestPixelAroundPoint(p, coefficients);
			colorPixel(p, &image);
			k--;
		}
	}
*/

	// ALTERNATIVA 2
	float value = 0;
	for (int j = 0; j < image.rows; j++) {
		for (int i = 0; i < image.cols; i++) {
			value = coefficients[0] * (i*i) + coefficients[1] * (i*j) + coefficients[2] * (j*j) + coefficients[3] * (i)+coefficients[4] * (j)+coefficients[5];
			//TODO Definir margem de erro.
			if (abs(value) <= 0.004) {
				colorPixel(Vector2i(i, j), &image);
			}
		}
	}
	namedWindow("ConicGenerator", CV_WINDOW_FULLSCREEN);
	imshow("ConicGenerator", image);
	imwrite("C:\\Users\\Eduardo\\Teste.png", image);

}


int main() {
	Vector2i points[5];
	
	/*	
	points[0] = Vector2i(10, 10);
	points[1] = Vector2i(20, 20);
	points[2] = Vector2i(30, 30);
	points[3] = Vector2i(40, 30);
	points[4] = Vector2i(50, 30);
	*/

	points[0] = Vector2i(100, 100);
	points[1] = Vector2i(100, 230);
	points[2] = Vector2i(60, 100);
	points[3] = Vector2i(60, 150);
	points[4] = Vector2i(70, 50);


	VectorXf coefficients = getCoefficients(points);
	
	float type = (coefficients[1] * coefficients[1]) - 4 * (coefficients[0]) * (coefficients[2]);

	cout << "CONIC SECTION TYPE: ";

	if (type < 0) {
		cout << "ELLIPSE" << endl;
	} else if (type == 0) {
		cout << "PARABOLA" << endl;
	} else {
		cout << "HYPERBOLA" << endl;
	}

	//TODO melhorar a assinatura do método. (REFERENCIAR ARRAY CORRETAMENTE)
	drawPoints(&points[0], 5, coefficients);
	waitKey();
}

