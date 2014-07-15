#ifndef TENCDATAAPPROXIMATIONEVAL_H
#define	TENCDATAAPPROXIMATIONEVAL_H

#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "../TLibCommon/TypeDef.h"
#include "../TLibCommon/TComMv.h"

class TEncDataApproximationEval {
private:
	static Pel* backup;
	static Pel* faulty
	;
	static Int stride;
	static Int width, height;
	
	static std::fstream fout;

	
	
	
	static Int iSrchRngHorLeft, iSrchRngHorRight, iSrchRngVerTop, iSrchRngVerBottom;
		
public:
	static bool firstFrameFlag;	
	static UInt faultOcc; // means that we have a probability of 1/faultOcc to have a memory cell fault
	
	TEncDataApproximationEval();
	
	static void init(Int w, Int h);
	static void close();
	
	static void initSearchWindow(TComMv& mvLT, TComMv& mvRB, Int xCU, Int yCU);
	
	static void printSearchWindow(Pel* p, Int stride);
	static void saveSearchWindow(Pel* p, Int stride);
	static void recoverySearchWindow(Pel* p, Int stride);
	static void recoveryFaultySearchWindow(Pel* p, Int stride);
	
	static void printBackupLSamples();
		
	
	static void insertFaults();
	
};

#endif	/* TENCDATAAPPROXIMATIONEVAL_H */

