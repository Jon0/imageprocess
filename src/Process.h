/*
 * Process.h
 *
 *  Created on: 17/08/2014
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
	void removeNoiseMedian();
	void removeNoiseFourier();
	void enhance();
	void highlight();

private:
	string infile, outfile;
};

} /* namespace std */

#endif /* PROCESS_H_ */
