/*
 * Process.cpp
 *
 *  Created on: 12/08/2014
 *      Author: remnanjona
 */

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Process.h"

using namespace cv;
namespace std {

Process::Process(string in, string out) {
	infile = in;
	outfile = out;
}

Process::~Process() {
	// TODO Auto-generated destructor stub
}

void Process::sobel() {
	Mat image = imread(infile, CV_LOAD_IMAGE_COLOR);
	Mat greyimage, sobel_x_s, sobel_y_s;

	// convert to grey image
	cvtColor(image, greyimage, CV_RGB2GRAY);

	// some values may become negative
	// signed pixel values are required
	int ddepth = CV_16S;
	int scale = 1;
	int delta = 0;

	// calculate x gradient using sobel 3x3 matrix
	Sobel(greyimage, sobel_x_s, ddepth, 1, 0);

	// calculate y gradient using sobel 3x3 matrix
	Sobel(greyimage, sobel_y_s, ddepth, 0, 1);

	// power of 2 on sobel x and y components
	pow(sobel_x_s, 2.0, sobel_x_s);
	pow(sobel_y_s, 2.0, sobel_y_s);

	// weighted sum of two arrays (sobel = 0.5 * sobel_x_u + 0.5 * sobel_y_u)
	Mat sobel;
	addWeighted(sobel_x_s, 1.0, sobel_y_s, 1.0, 0, sobel, CV_32F);
	sqrt(sobel, sobel);

	imwrite(outfile, sobel);
}

void Process::removeNoiseMedian(int size) {
	Mat image = imread(infile, CV_LOAD_IMAGE_COLOR);

	Mat result;
	medianBlur( image, result, size );

	imwrite(outfile, result);
}

void Process::removeNoiseMean(int s) {
	Mat image = imread(infile, CV_LOAD_IMAGE_COLOR);
	blur( image, image, Size( s, s ) ); // mean filter
	imwrite(outfile, image);
}

void Process::removeNoiseFourier() {
	Mat image = imread(infile, CV_LOAD_IMAGE_COLOR);
    Mat greyimage;
    cvtColor(image, greyimage, CV_BGR2GRAY);

    Mat padded;                            //expand input image to optimal size
    int m = getOptimalDFTSize( greyimage.rows );
    int n = getOptimalDFTSize( greyimage.cols ); // on the border add zero values
    copyMakeBorder(greyimage, padded, 0, m - greyimage.rows, 0, n - greyimage.cols, BORDER_CONSTANT, Scalar::all(0));

    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);         // Add to the expanded another plane with zeros

    dft(complexI, complexI);            // this way the result may fit in the source matrix

	// compute the magnitude and switch to logarithmic scale
	// => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
	split(complexI, planes);    // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
	magnitude(planes[0], planes[1], planes[0]);         // planes[0] = magnitude
	Mat magI = planes[0];

	magI += Scalar::all(1);                    // switch to logarithmic scale
	log(magI, magI);

	// crop the spectrum, if it has an odd number of rows or columns
	magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

	// rearrange the quadrants of Fourier image  so that the origin is at the image center
	int cx = magI.cols / 2;
	int cy = magI.rows / 2;

	Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
	Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
	Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
	Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right

	Mat tmp;                      // swap quadrants (Top-Left with Bottom-Right)
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);                // swap quadrant (Top-Right with Bottom-Left)
	q2.copyTo(q1);
	tmp.copyTo(q2);

	normalize(magI, magI, 0, 1, CV_MINMAX); // Transform the matrix with float values into a
											// viewable image form (float between values 0 and 1)

	imwrite(outfile, complexI);
}

void Process::enhance() {
	Mat image = imread(infile, CV_LOAD_IMAGE_COLOR);
	int ddepth = -1;

	// 3 x 3 matrix
	Mat M = (Mat_<double>(3, 3) <<
			0, -1, 0,
			-1, 5, -1,
			0, -1, 0);

    // use filter
    filter2D(image, image, ddepth, M );

	imwrite(outfile, image);
}

void Process::threshold_i(double power, int thres) {
	Mat image = imread(infile, CV_LOAD_IMAGE_COLOR);
	if (image.channels() >= 3) {
		cvtColor( image, image, CV_RGB2GRAY );
	}
	normalize(image, image, 0, 1, NORM_MINMAX, CV_32F);
	pow(image, power, image);
	blur( image, image, Size( 3, 3 ) );
	normalize(image, image, 0, 255, NORM_MINMAX);
	threshold(image, image, thres, 255, THRESH_BINARY);
	imwrite(outfile, image);
}

} /* namespace std */
