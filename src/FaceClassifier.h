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
	FaceClassifier(string, int);
	virtual ~FaceClassifier();

	void getWeights(ofstream &ofs, Mat &m, int classtype);
	void outputWeights(string file);


	void train();
	void test();

	void features(Mat &);
	f2d pixelDir(Mat &, i2d);

private:
	string base_dir;
	int width, height, numfeatures;
	int correct, tested;

	// images and associated label
    vector<Mat> images;
    vector<int> labels;
	Ptr<FaceRecognizer> model;
	double threshold;

	void addImage(string, int);
	bool test(string, int);
};

} /* namespace std */

#endif /* FACECLASSIFIER_H_ */
