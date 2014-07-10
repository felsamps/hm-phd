#ifndef TENCDATAAPPROXIMATIONEVAL_H
#define	TENCDATAAPPROXIMATIONEVAL_H

#include <fstream>
#include <cstdlib>
#include <ctime>

#include "../TLibCommon/TypeDef.h"

class TEncDataApproximationEval {
private:
	static Pel* backup;
	static Int stride;
	static Int width, height;
	
	static std::fstream fout;
	static bool firstFrameFlag;
	
	static const UInt faultOcc = 1e2; // means that we have a probability of 1/faultOcc to have a memory cell fault
		
public:
	
	TEncDataApproximationEval();
	
	static void init(Int w, Int h);
	static void close();
	
	static void printLSamples(Pel* p, Int stride);
	static void printBackupLSamples();
	
	static void copyLumaSamples(Pel* p, Int stride);
	
	static void insertFaults();
	
};

#endif	/* TENCDATAAPPROXIMATIONEVAL_H */

