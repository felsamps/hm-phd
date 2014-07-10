#include "TEncDataApproximationEval.h"

Pel* TEncDataApproximationEval::backup;
Int TEncDataApproximationEval::stride;
Int TEncDataApproximationEval::width, TEncDataApproximationEval::height;
	
std::fstream TEncDataApproximationEval::fout;

bool TEncDataApproximationEval::firstFrameFlag;

TEncDataApproximationEval::TEncDataApproximationEval() {
}

void TEncDataApproximationEval::init(Int w, Int h) {
	fout.open("approx_debug.txt", std::fstream::out);
	width = w;
	height = h;
	
	firstFrameFlag = true;
}

void TEncDataApproximationEval::close() {
	fout.close();
}

void TEncDataApproximationEval::printLumaSamplesData(Pel* p, Int stride) {
	if(firstFrameFlag) {
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				fout << p[x + y*stride] << " ";
			}
			fout << std::endl;
		}
		firstFrameFlag = false;
	}	
}