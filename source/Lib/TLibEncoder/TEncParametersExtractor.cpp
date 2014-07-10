#include "TEncParametersExtractor.h"

bool*** TEncParametersExtractor::skipMap;
std::fstream TEncParametersExtractor::fpSkip;
UInt TEncParametersExtractor::width, TEncParametersExtractor::height, TEncParametersExtractor::framesToBeCoded;

TEncParametersExtractor::TEncParametersExtractor() {
}

void TEncParametersExtractor::init(UInt w, UInt h, UInt fr) {
	width = w;
	height = h;
	framesToBeCoded = fr;	
	
	skipMap = new bool** [framesToBeCoded];
	for (int f = 0; f < framesToBeCoded; f++) {	
		skipMap[f] = new bool* [width/4];
		for (int x = 0; x < width/4; x++) {
			skipMap[f][x] = new bool[height/4];
		}
	}
	fpSkip.open("skip_map.mat", fstream::out);
}

void TEncParametersExtractor::updateCTU(TComDataCU* pcCU) {
	//Char* preds = pcCU->getPredictionMode();
	//Char* parts = pcCU->getPartitionSize();
	bool* skips = pcCU->getSkipFlag();
	
	UInt x = pcCU->getCUPelX();
	UInt y = pcCU->getCUPelY();
	
	UInt f = pcCU->getSlice()->getPOC();
	
	if(pcCU->getSlice()->getSliceType() != I_SLICE) {
		for (int rasterIdx = 0; rasterIdx < pcCU->getTotalNumPart(); rasterIdx++) {
			UInt xPos = x + g_auiRasterToPelX[rasterIdx];
			UInt yPos = y + g_auiRasterToPelY[rasterIdx];
			UInt zScanIdx = g_auiRasterToZscan[rasterIdx];
			
			if(xPos < width and yPos < height) {
				if(skips[zScanIdx]) {
					//printf("(%d,%d) SKIP!\n", xPos, yPos);
					skipMap[f][xPos/4][yPos/4] = true;
				}
				else {
					//printf("(%d,%d) %d %d\n", xPos, yPos, preds[zScanIdx], parts[zScanIdx]);
					skipMap[f][xPos/4][yPos/4] = false;
				}
			}
		}
	}
	//xUpdateCTU(64, x, y, 0, preds, parts, skips);
}

void TEncParametersExtractor::report() {
	for (int f = 0; f < framesToBeCoded; f++) {
		for (int y = 0; y < height/4; y++) {
			for (int x = 0; x < width/4; x++) {
				fpSkip << (skipMap[f][x][y] ? "1" : "0") << " ";
			}
			fpSkip << std::endl;
		}
	}
}

void TEncParametersExtractor::close() {
	fpSkip.close();
}

/*TEncParametersExtractor::xUpdateCTU(UInt size, UInt x, UInt y, UInt idx, Char* preds, Char* parts, bool* skips) {
	if(size = 4) {
		
	}
	
	UInt pelStep = size / (4 * 2);
	UInt idxStep = size / 2;
	
	xUpdateCTU(size/2, x        , y        , idx, preds, parts, skips);
	xUpdateCTU(size/2, x+pelStep, y        , idx + size*1, preds, parts, skips);
	xUpdateCTU(size/2, x        , y+pelStep, idx + size*2, preds, parts, skips);
	xUpdateCTU(size/2, x+pelStep, y+pelStep, idx + size*3, preds, parts, skips);
}

*/