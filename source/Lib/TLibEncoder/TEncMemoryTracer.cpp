#include "TEncMemoryTracer.h"
#include "TEncAnalyze.h"

std::fstream TEncMemoryTracer::fp;
bool TEncMemoryTracer::firstOrRasterSearchFlag;

TEncMemoryTracer::TEncMemoryTracer() {
}

void TEncMemoryTracer::init(std::string fileName, UInt wFrame, UInt hFrame, UInt tileCols, UInt tileRows, UInt searchRange) {
	fp.open(fileName.c_str(), std::fstream::out);
	firstOrRasterSearchFlag = false;
	
	std::string outStr = "";
	
	std::stringstream ss;
	ss << wFrame << " ";
	ss << hFrame << " ";
	ss << tileCols << " ";
	ss << tileRows << " ";
	ss << searchRange << std::endl;
	
	outStr += ss.str();
	fp << outStr;
}

void TEncMemoryTracer::finalize() {
	fp.close();
}

void TEncMemoryTracer::initFrame(Int idCurrFrame) {
	std::string outStr = "I ";
	
	std::stringstream ss;
	ss << idCurrFrame << std::endl;
	outStr += ss.str();
	fp << outStr;
}

void TEncMemoryTracer::initLCU(Int xLCU, Int yLCU, Int idTile) {
	std::string outStr = "L ";
	
	std::stringstream ss;
	ss << xLCU << " ";
	ss << yLCU << " ";
	ss << idTile << std::endl;
	
	outStr += ss.str();
	fp << outStr;
}

void TEncMemoryTracer::initCU(Int xCU, Int yCU, Int depthCU) {
	std::string outStr = "U ";
	
	std::stringstream ss;
	ss << xCU << " ";
	ss << yCU << " ";
	ss << depthCU << std::endl;
	
	outStr += ss.str();
	fp << outStr;
}

void TEncMemoryTracer::initPU(Int idPart, Int sizePU, Int idRefFrame) {
	std::string outStr = "P ";
	
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

void TEncMemoryTracer::finalizeLCU() {
	fp << "E" << std::endl;
}

void TEncMemoryTracer::finalizePU() {
	fp << "p" << std::endl;
}

void TEncMemoryTracer::finalizeCU() {
	fp << "u" << std::endl;
}

void TEncMemoryTracer::finalizeFrame() {
	fp << "i" << std::endl;
}