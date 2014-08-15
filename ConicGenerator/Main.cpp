/**
 Conic Generator
 Main.cpp
 @author Eduardo Vera Sousa
*/

#include "stdafx.h"
#include <opencv2\opencv.hpp>

using namespace cv;
using namespace std;


int main() {
	Vec2i points[5];
	points[0] = Vec2i(10, 10);
	points[1] = Vec2i(20, 20);
	points[2] = Vec2i(30, 30);
	points[3] = Vec2i(40, 30);
	points[4] = Vec2i(50, 30);

	Mat1i matrixPoints(5, 6);
	Mat1i matrixResult(6, 1);

	for (int j = 0; j < matrixPoints.rows; j++) {
		matrixPoints.at<int>(j, 0) = points[j].val[0] * points[j].val[0];
		matrixPoints.at<int>(j, 1) = points[j].val[0] * points[j].val[1];
		matrixPoints.at<int>(j, 2) = points[j].val[1] * points[j].val[1];
		matrixPoints.at<int>(j, 3) = points[j].val[0];
		matrixPoints.at<int>(j, 4) = points[j].val[1];
		matrixPoints.at<int>(j, 5) = 1;
		matrixResult.at<int>(j, 0) = 0;
	}

	for (int j = 0; j < matrixPoints.rows; j++) {
		for (int i = 0; i < matrixPoints.cols; i++) {
			cout << matrixPoints.at<int>(j, i) << " ";
		}
		cout << endl;
	}
	getchar();
}

