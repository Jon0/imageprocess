#include <vector>
#include <string>

#include "FaceClassifier.h"
#include "Process.h"

using namespace std;




void parse_args(vector<string> args) {
	for (int i = 0; i < args.size(); ++i) {
		string &s = args[i];
		if (s == "-facedetect") {
			string &indir = args[++i];
			int features = atoi(args[++i].c_str());
			FaceClassifier fc(indir, features);
			fc.train();
			fc.test();
		}
		if (s == "-sobel") {
			string &infile = args[++i];
			Process p(infile, "sobel.jpg");
			p.sobel();
		}
		else if (s == "-noise") {
			string &infile = args[++i];
			Process p1(infile, "noise_median_3.jpg");
			p1.removeNoiseMedian(3);

			Process p2(infile, "noise_median_5.jpg");
			p2.removeNoiseMedian(5);

			Process p3(infile, "noise_mean.jpg");
			p3.removeNoiseMean(3);
		}
		else if (s == "-threshold") {
			string &infile = args[++i];
			Process p1(infile, "thres_220.jpg");
			p1.threshold_i(1.0, 220);

			Process p2(infile, "thres_230.jpg");
			p2.threshold_i(1.0, 230);
		}
		else if (s == "-enhance") {
			string &infile = args[++i];
			Process p1(infile, "enhance.jpg");
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
