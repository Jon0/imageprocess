#include <vector>
#include <string>

#include "FaceClassifier.h"
#include "Process.h"

using namespace std;

void parse_args(vector<string> args) {
	for (string s: args) {
		if (s == "-facedetect") {
			FaceClassifier fc;
			fc.train();
			fc.test();
		}
		if (s == "-sobel") {
			Process p("images/test-pattern.tif", "sobel.jpg");
			p.sobel();
		}
		else if (s == "-noise") {
			Process p1("images/ckt-board-saltpep.tif", "noise_median_3.jpg");
			p1.removeNoiseMedian(3);

			Process p2("images/ckt-board-saltpep.tif", "noise_median_5.jpg");
			p2.removeNoiseMedian(5);

			Process p3("images/ckt-board-saltpep.tif", "noise_mean.jpg");
			p3.removeNoiseMean(3);
		}
		else if (s == "-threshold") {
			Process p1("images/hubble.tif", "thres_220.jpg");
			p1.threshold_i(1.0, 220);

			Process p2("images/hubble.tif", "thres_230.jpg");
			p2.threshold_i(1.0, 230);
		}
		else if (s == "-enhance") {
			Process p1("images/blurry-moon.tif", "enhance.jpg");
			p1.enhance();
		}
	}

}

int main(int argc, char *argv[]) {
	vector<string> args;
	for (int i = 0; i < argc; ++i) {
		args.push_back( string(argv[i]) );
	}
	parse_args(args);
	return 0;
}
