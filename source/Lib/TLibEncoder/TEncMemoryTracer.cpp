#include "TEncMemoryTracer.h"
#include "TEncAnalyze.h"

std::fstream TEncMemoryTracer::fp;
bool TEncMemoryTracer::firstOrRasterSearchFlag;

TEncMemoryTracer::TEncMemoryTracer() {
}

void TEncMemoryTracer::init(std::string fileName) {
	fp.open(fileName.c_str(), std::fstream::out);
	firstOrRasterSearchFlag = false;
}

void TEncMemoryTracer::finalize() {
	fp.close();
}

void TEncMemoryTracer::initLCU(Int xLCU, Int yLCU, Int idTile, Int idFrame) {
	std::string outStr = "LCU ";
	
	std::stringstream ss;
	ss << xLCU << " ";
	ss << yLCU << " ";
	ss << idTile << " ";
	ss << idFrame << std::endl;
	
	outStr += ss.str();
	fp << outStr;
}

void TEncMemoryTracer::initCU(Int xCU, Int yCU, Int depthCU) {
	std::string outStr = "CU ";
	
	std::stringstream ss;
	ss << xCU << " ";
	ss << yCU << " ";
	ss << depthCU << std::endl;
	
	outStr += ss.str();
	fp << outStr;
}

void TEncMemoryTracer::initPU(Int idPart, Int sizePU, Int idRefFrame) {
	std::string outStr = "PU ";
	
	std::stringstream ss;
	ss << idPart << " ";
	ss << sizePU << " ";
	ss << idRefFrame << std::endl;
	
	outStr += ss.str();
	fp << outStr;
}

void TEncMemoryTracer::insertFirstSearch(Int xStart, Int yStart) {
	std::string outStr = "F ";
	
	std::stringstream ss;
	ss << xStart << " ";
	ss << yStart << std::endl;
	
	outStr += ss.str();
	fp << outStr;
}

void TEncMemoryTracer::insertCandidate(Int xCand, Int yCand) {
	std::string outStr = "C ";
	
	std::stringstream ss;
	ss << xCand << " ";
	ss << yCand << std::endl;
	
	outStr += ss.str();
	fp << outStr;
}

void TEncMemoryTracer::insertRasterSearch(Int xLeft, Int xRight, Int yTop, Int yBottom) {
	std::string outStr = "R ";
	
	std::stringstream ss;
	ss << xLeft << " ";
	ss << xRight << " ";
	ss << yTop << " ";
	ss << yBottom << std::endl;
	
	outStr += ss.str();
	fp << outStr;
}