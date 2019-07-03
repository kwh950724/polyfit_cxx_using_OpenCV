// OpenCV Headers
#include "opencv2/opencv.hpp"
// C++ Headers
#include <iostream>

using namespace std;
using namespace cv;

void cvPolyfit(Mat &src_x, Mat &src_y, Mat &dst, int order) {
	Mat X, copy;
	X = Mat::zeros(src_x.rows, order+1, CV_32FC1);
	for(int i=0; i<=order; i++) {
		copy = src_x.clone();
		pow(copy, i, copy);
		Mat M1 = X.col(i);
		copy.col(0).copyTo(M1);
	}
	Mat X_t, X_inv;
	transpose(X, X_t);
	Mat temp = X_t * X;
	Mat temp2;
	invert(temp, temp2);
	Mat temp3 = temp2 * X_t;
	Mat W = temp3 * src_y;
	dst = W.clone();
}

int main(void) {
	int rows = 10;
	int cols = 1;

	Mat x(rows, cols, CV_32F);
	Mat y(rows, cols, CV_32F);
	// Setting inputs.
	for(int i=0;i<10;i++) {
		x.at<float>(0, i) = i;
		y.at<float>(0, i) = 1.032 * pow(i, 2) + 3.02 * i + 3.45;
	}

	int fit_order = 2;

	Mat fit_weights(fit_order + 1, 1, CV_32FC1);
	

	cvPolyfit(x, y, fit_weights, fit_order);
	// Printing coefficient of function.
	cout<<fit_weights.at<float>(0, 0)<<endl; 
	cout<<fit_weights.at<float>(1, 0)<<endl; 
	cout<<fit_weights.at<float>(2, 0)<<endl; 
}

