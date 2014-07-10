#include "TEncDataApproximationEval.h"

Pel* TEncDataApproximationEval::backup;
Int TEncDataApproximationEval::stride;
Int TEncDataApproximationEval::width, TEncDataApproximationEval::height;
	
std::fstream TEncDataApproximationEval::fout;

bool TEncDataApproximationEval::firstFrameFlag;

const UInt TEncDataApproximationEval::faultOcc;

TEncDataApproximationEval::TEncDataApproximationEval() {
}

void TEncDataApproximationEval::init(Int w, Int h) {
	fout.open("approx_debug.txt", std::fstream::out);
	width = w;
	height = h;
	
	firstFrameFlag = true;
	
	backup = new Pel[width * height];
	
	srand(time(NULL));
}

void TEncDataApproximationEval::close() {
	fout.close();
}

void TEncDataApproximationEval::printLSamples(Pel* p, Int stride) {
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

void TEncDataApproximationEval::printBackupLSamples() {
	if(firstFrameFlag) {
		
		insertFaults(); //INSERTING FAULTS TO THE REFERENCE FRAME SAMPLES
		
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				fout << backup[x + y*width] << " ";
			}
			fout << std::endl;
		}
		firstFrameFlag = false;
	}	
}

void TEncDataApproximationEval::copyLumaSamples(Pel* p, Int stride) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			backup[x + y*width] = p[x + y*stride];
		}
	}
	
}

void TEncDataApproximationEval::insertFaults() {
	
	
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			
			Pel sample = backup[x + y*width];
			Pel masc = 0x0001; //16-bit data
			
			while(masc != 0x0100) { 
				Int bit = (masc & sample) ? 1 : 0;
				UInt maxRand = rand() % faultOcc;
				
				if(maxRand == 1) {
					if(bit == 0) { //flip the bit from 0 to 1
						sample = sample | masc;
					}
					else { //flip the bit from 1 to 0
						Pel negMasc = ~masc;
						sample = sample & negMasc;
					}
				}				
				masc = masc << 1;
			}
			
			backup[x + y*width] = sample;
		}
	}
}