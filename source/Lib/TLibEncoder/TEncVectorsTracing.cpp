#include "TEncVectorsTracing.h"

std::fstream TEncVectorsTracing::fp;
std::map<std::pair<UInt, UInt>, Short*** > TEncVectorsTracing::mvFrame;
UInt TEncVectorsTracing::wFrameInCU, TEncVectorsTracing::hFrameInCU, TEncVectorsTracing::idRefFrame;
bool TEncVectorsTracing::bBi;

TEncVectorsTracing::TEncVectorsTracing() {
	
}

void TEncVectorsTracing::init(std::string fileName, UInt w, UInt h) {	
	fp.open(fileName.c_str(), std::fstream::out);
	wFrameInCU = w/MV_TARGET_CU_SIZE;
	hFrameInCU = h/MV_TARGET_CU_SIZE;
	
}

void TEncVectorsTracing::finalize() {
	fp.close();
}

void TEncVectorsTracing::xAllocNewVectorsFrame(std::pair<UInt, UInt> p) {
	Short ***mv = NULL;
	
	if(mvFrame.find(p) == mvFrame.end()) {
		mv = new Short**[wFrameInCU];
		for (int i = 0; i < wFrameInCU; i++) {
			mv[i] = new Short*[hFrameInCU];
			for (int j = 0; j < hFrameInCU; j++) {
				mv[i][j] = new Short[2];
			}
		}
	}
	
	if(mv != NULL) {
		mvFrame[p] = mv;
	}
}

void TEncVectorsTracing::insertMV(UInt idCurrFrame, UInt xCU, UInt yCU, Short xMv, Short yMv) {
	if( !bBi ) {
		std::pair<UInt, UInt> framesME(idCurrFrame, idRefFrame);
		xAllocNewVectorsFrame(framesME);


		mvFrame[framesME][xCU][yCU][0] = xMv;
		mvFrame[framesME][xCU][yCU][1] = yMv;
	}	
}

void TEncVectorsTracing::reportMv() {
	std::cout << "IM HERE!!!"  << mvFrame.size() << "\n\n";
	//UInt ME_ORDER [15][2] = {{8,0}, {4,0}, {2,0}, {2,4}, {6,4}, {6,8}, {1,0}, {1,2}, {3,2}, {3,4}, {5,4}, {5,6}, {7,6}, {7,8}};	
	//UInt NUM_OF_ME = 14;
	
	std::cout << mvFrame.size() << "\n";
	
	/*for debugging */
	
	for (std::map<std::pair<UInt, UInt>, Short*** >::iterator it = mvFrame.begin(); it != mvFrame.end(); it++) {
		std::cout << "ME Entry " << (*it).first.first << " " << (*it).first.second << "\n";
		Short ***mv = (*it).second;
		
		for (int h = 0; h < hFrameInCU; h++) {
			for (int x = 0; x < wFrameInCU; x++) {
				fp << mv[x][h][0] << " " << mv[x][h][1] << std::endl;
			}
		}
		
	}
}

void TEncVectorsTracing::setIdRefFrame(UInt id) {
	idRefFrame = id;
}

void TEncVectorsTracing::setBiPrediction(bool b) {
	bBi = b;
}