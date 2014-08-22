/*
 * FaceClassifier.cpp
 *
 *  Created on: 11/08/2014
 *      Author: remnanjona
 */

#include <iostream>
#include <fstream>
#include <vector>

#include "Directory.h"
#include "FaceClassifier.h"

using namespace cv;
namespace std {

static Mat normalise(Mat in) {
    // make normalised image
    Mat dst;
    switch(in.channels()) {
    case 1:
        normalize(in, dst, 0, 255, NORM_MINMAX, CV_8UC1);
        break;
    case 3:
        normalize(in, dst, 0, 255, NORM_MINMAX, CV_8UC3);
        break;
    default:
        in.copyTo(dst);
        break;
    }
    return dst;
}

FaceClassifier::FaceClassifier() {
	base_dir = "/local/scratch/";
	width = 19;
	height = 19;
	numfeatures = 16;
	correct = 0;
	tested = 0;
	model = createEigenFaceRecognizer(numfeatures);
    //model = createLBPHFaceRecognizer(1, 8, 8, 8);
}

FaceClassifier::~FaceClassifier() {}

void FaceClassifier::getWeights(ofstream &ofs, Mat &m, int classtype) {
	Mat weights = model->getMat("eigenvalues");
	for (int w = 0; w < weights.cols; ++w) {
		double wval = weights.at<double>(w, 0);
		ofs << wval << " ";
	}
	ofs << classtype;
	ofs << endl;
}

void FaceClassifier::outputWeights(string file) {
	ofstream ofs (file, ofstream::out);
	for (int i = 0; i < images.size(); ++i) {
		getWeights(ofs, images[i], labels[i]);
	}
}

void FaceClassifier::addImage(string fname, int classtype) {
	Mat in = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
	if (in.cols == width && in.rows == height) {

		// normalise input
		in = normalise(in);
		images.push_back(in);
		labels.push_back(classtype);
	}
}

void FaceClassifier::train() {
	Directory train_f(base_dir+"train/face/");
	Directory train_n(base_dir+"train/non-face/");

	// make list of images and labels
	for ( string fname: train_f.fileList() ) {
		addImage(fname, 1);
	}
	for ( string fname: train_n.fileList() ) {
		addImage(fname, -1);
	}
	model->train(images, labels);
}

void FaceClassifier::test() {
	Directory test_f(base_dir+"test/face/");
	Directory test_n(base_dir+"test/non-face/");

	int face = 0, cface = 0, notface = 0, cnotface = 0;

	for ( string fname: test_f.fileList() ) {
		if (test(fname, 1)) cface++;
		face++;
	}
	for ( string fname: test_n.fileList() ) {
		if (test(fname, -1)) cnotface++;
		notface++;
	}

	cout << "TPF " << (float) cface / (float) face << endl;
	cout << "FPF " << (float) (notface-cnotface) / (float) notface << endl;
	cout << "correct " << (float) correct / (float) tested << endl;
}

bool FaceClassifier::test(string file, int expected) {
	Mat in = imread(file, CV_LOAD_IMAGE_GRAYSCALE);
	if (in.cols == width && in.rows == height) {

		// normalise input
		in = normalise(in);
		int predictedLabel = -1;
		double confidence = 0.0;
		model->predict(in, predictedLabel, confidence);
		if (predictedLabel == expected) {
			correct++;
		}
	    tested++;
	    cout << "predict " << predictedLabel << " [" << expected << "] (" << (float) correct / (float) tested << ")" << endl;
	    return predictedLabel == expected;
	}
	return false;
}

void FaceClassifier::features(Mat &m) {
	int width = m.cols;
	int height = m.rows;

	Mat out = Mat(width - 2, height - 2, CV_8UC3);

	for (int x = 1; x < width - 1; ++x) {
		for (int y = 1; y < height - 1; ++y) {
			f2d pd = pixelDir(m, i2d(x, y));
			Vec3b &pixel = out.at<Vec3b>(x - 1, y - 1);
			pixel.val[0] = 0;
			pixel.val[1] = abs(pd.first * 50);
			pixel.val[2] = abs(pd.second * 50);

		}
	}

	imwrite("out/test.jpg", out);
}

f2d FaceClassifier::pixelDir(Mat &m, i2d p) {

	Mat n = Mat(m, Rect(p.first - 1, p.second - 1, 3, 3));

	double h = n.at<double>(0, 0);
	double l = h;
	i2d hp = i2d(0, 0);
	i2d	lp = hp;

	for (int x = 0; x < 3; ++x) {
		for (int y = 0; y < 3; ++y) {
			double pp = n.at<double>(x, y);
			if (pp > h) {
				h = pp;
				hp = i2d(x, y);
			}
			else if (pp < l) {
				l = pp;
				lp = i2d(x, y);
			}
		}
	}

	double scale = (hp.first*hp.first + hp.second*hp.second) - (lp.first*lp.first + lp.second*lp.second);

	return f2d(scale*(hp.first - lp.first), scale*(hp.second - lp.second));
}

} /* namespace std */
