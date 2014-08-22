/*
 * Process.h
 *
 *  Created on: 12/08/2014
 *      Author: remnanjona
 */

#ifndef PROCESS_H_
#define PROCESS_H_

#include <string>

namespace std {

class Process {
public:
	Process(string, string);
	virtual ~Process();

	void sobel();
	void removeNoiseMedian(int);
	void removeNoiseMean(int);
	void removeNoiseFourier();
	void enhance();
	void threshold_i(double, int);

private:
	string infile, outfile;
};

} /* namespace std */

#endif /* PROCESS_H_ */
