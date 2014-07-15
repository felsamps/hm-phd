#include "TEncDataApproximationEval.h"

Pel* TEncDataApproximationEval::backup;
Pel* TEncDataApproximationEval::faulty;

Int TEncDataApproximationEval::stride;
Int TEncDataApproximationEval::width, TEncDataApproximationEval::height;
	
std::fstream TEncDataApproximationEval::fout;

bool TEncDataApproximationEval::firstFrameFlag;

UInt TEncDataApproximationEval::faultOcc;

Int TEncDataApproximationEval::iSrchRngHorLeft;
Int TEncDataApproximationEval::iSrchRngHorRight;
Int TEncDataApproximationEval::iSrchRngVerTop;
Int TEncDataApproximationEval::iSrchRngVerBottom;

TEncDataApproximationEval::TEncDataApproximationEval() {
}

void TEncDataApproximationEval::init(Int w, Int h) {
	fout.open("approx_debug.txt", std::fstream::out);
	width = w;
	height = h;
	
	firstFrameFlag = true;
	
	backup = new Pel[width * height];
	faulty = new Pel[width * height];
	
	srand(time(NULL));
	
	firstFrameFlag = true;
}

void TEncDataApproximationEval::close() {
	fout.close();
}

void TEncDataApproximationEval::initSearchWindow(TComMv& mvLT, TComMv& mvRB, Int xCU, Int yCU) {
	iSrchRngHorLeft   = mvLT.getHor();
	iSrchRngHorRight  = mvRB.getHor();
	iSrchRngVerTop    = mvLT.getVer();
	iSrchRngVerBottom = mvRB.getVer();
	
}


void TEncDataApproximationEval::saveSearchWindow(Pel* p, Int stride) {
	Pel* pOrig, *pAuxOrig, *pBackup;
	pOrig = p;
	pOrig += (iSrchRngVerTop * stride);	//point the pointer to the first line of the search window
	
	pBackup = backup;
	
	for (int y = iSrchRngVerTop; y < iSrchRngVerBottom; y++) {
		for (int x = iSrchRngHorLeft; x < iSrchRngHorRight; x++) {
			pAuxOrig = pOrig + x; //point the auxiliar pointer to the right sample inside the search window limits
			*pBackup = *pAuxOrig;
			
			pBackup++;
		}
		pOrig += stride;
		
		fout << std::endl;
		
	}
}

void TEncDataApproximationEval::recoverySearchWindow(Pel* p, Int stride) {
	Pel* pOrig, *pAuxOrig, *pBackup;
	pOrig = p;
	pOrig += (iSrchRngVerTop * stride);	//point the pointer to the first line of the search window
	
	pBackup = backup;
	
	for (int y = iSrchRngVerTop; y < iSrchRngVerBottom; y++) {
		for (int x = iSrchRngHorLeft; x < iSrchRngHorRight; x++) {
			pAuxOrig = pOrig + x; //point the auxiliar pointer to the right sample inside the search window limits
			*pAuxOrig = *pBackup;
			
			pBackup++;
		}
		pOrig += stride;
		
		fout << std::endl;
		
	}
}

void TEncDataApproximationEval::recoveryFaultySearchWindow(Pel* p, Int stride) {
	Pel* pOrig, *pAuxOrig, *pFaulty;
	pOrig = p;
	pOrig += (iSrchRngVerTop * stride);	//point the pointer to the first line of the search window
	
	pFaulty = faulty;
	
	for (int y = iSrchRngVerTop; y < iSrchRngVerBottom; y++) {
		for (int x = iSrchRngHorLeft; x < iSrchRngHorRight; x++) {
			pAuxOrig = pOrig + x; //point the auxiliar pointer to the right sample inside the search window limits
			*pAuxOrig = *pFaulty;
			
			pFaulty++;
		}
		pOrig += stride;
		
		fout << std::endl;
		
	}
}

void TEncDataApproximationEval::printBackupLSamples() {
	Pel *pBackup = backup;	
	
	for (int y = iSrchRngVerTop; y < iSrchRngVerBottom; y++) {
		for (int x = iSrchRngHorLeft; x < iSrchRngHorRight; x++) {
			fout << *pBackup << " ";
			pBackup ++;
		}
		fout << std::endl;
	}
}

void TEncDataApproximationEval::printSearchWindow(Pel* p, Int stride) {
	
	Pel* pAux;
	p += (iSrchRngVerTop * stride);	//point the pointer to the first line of the search window
		
	for (int y = iSrchRngVerTop; y < iSrchRngVerBottom; y++) {
		for (int x = iSrchRngHorLeft; x < iSrchRngHorRight; x++) {
			pAux = p + x; //point the auxiliar pointer to the right sample inside the search window limits
			fout << *pAux << " ";
		}
		p += stride;
		fout << std::endl;
	}
	firstFrameFlag = false;
	
}

void TEncDataApproximationEval::insertFaults() {
	
	Pel *pBackup = backup;
	Pel *pFaulty = faulty;
	
	for (int y = iSrchRngVerTop; y < iSrchRngVerBottom; y++) {
		for (int x = iSrchRngHorLeft; x < iSrchRngHorRight; x++) {
			
			Pel sample = *pBackup;
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
			
			*faulty = sample;
			pFaulty ++;
			pBackup ++;
		}
	}
}