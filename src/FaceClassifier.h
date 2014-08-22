/*
 * FaceClassifier.h
 *
 *  Created on: 11/08/2014
 *      Author: remnanjona
 */

#ifndef FACECLASSIFIER_H_
#define FACECLASSIFIER_H_

#include <opencv2/core/core.hpp>
#include <opencv2/contrib/contrib.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
namespace std {

typedef pair<int, int> i2d;
typedef pair<double, double> f2d;


class FaceClassifier {
public:
	FaceClassifier();
	virtual ~FaceClassifier();


	void train();
	void test();



	void features(Mat &);
	f2d pixelDir(Mat &, i2d);

private:
	int width, height;
	int correct, tested;

	// images and associated label
    vector<Mat> images;
    vector<int> labels;
	Ptr<FaceRecognizer> model;

	void addImage(string, int);
	void test(string, int);
};

} /* namespace std */

#endif /* FACECLASSIFIER_H_ */
