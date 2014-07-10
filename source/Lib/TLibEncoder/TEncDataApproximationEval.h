#ifndef TENCDATAAPPROXIMATIONEVAL_H
#define	TENCDATAAPPROXIMATIONEVAL_H

#include <fstream>

#include "../TLibCommon/TypeDef.h"

class TEncDataApproximationEval {
private:
	static Pel* backup;
	static Int stride;
	static Int width, height;
	
	static std::fstream fout;
	static bool firstFrameFlag;
		
public:
	
	TEncDataApproximationEval();
	
	static void init(Int w, Int h);
	static void close();
	
	static void printLumaSamplesData(Pel* p, Int stride);
	
};

#endif	/* TENCDATAAPPROXIMATIONEVAL_H */

