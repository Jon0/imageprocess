#include "Process.h"

using namespace std;

int main() {
	Process p1("/vol/courses/comp422/images/test-pattern.tif", "edge.jpg");
	p1.sobel();

	Process p2("/vol/courses/comp422/images/ckt-board-saltpep.tif", "median_smooth.jpg");
	p2.removeNoiseMedian();

	//Process p3("/vol/courses/comp422/images/ckt-board-saltpep.tif", "fourier_smooth.jpg");
	//p3.removeNoiseFourier();

	Process p4("/vol/courses/comp422/images/blurry-moon.tif", "enhance.jpg");
	p4.enhance();


	return 0;
}