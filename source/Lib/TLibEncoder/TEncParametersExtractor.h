#ifndef TENCPARAMETERSEXTRACTOR_H
#define	TENCPARAMETERSEXTRACTOR_H

#include <fstream>

#include "TLibCommon/TComDataCU.h"
#include "TEncAnalyze.h"

class TEncParametersExtractor {
	static bool*** skipMap;
	static std::fstream fpSkip;
	static UInt width, height, framesToBeCoded;
	
public:
	TEncParametersExtractor();
	
	static void init(UInt w, UInt h, UInt f);
	static void updateCTU(TComDataCU* pcCU); /*do it recursively*/
	static void xUpdateCTU(UInt size, UInt x, UInt y, UInt idx, Char* preds, Char* parts, bool* skips);
	
	static void report();
	
	static void close();
								
private:

};

#endif	/* TENCPARAMETERSEXTRACTOR_H */

