#ifndef TENCMEMORYTRACER_H
#define	TENCMEMORYTRACER_H

#include "../TLibCommon/TypeDef.h"

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

class TEncMemoryTracer {
private:
    
    static std::fstream fp;
    

public:
    
    static bool firstOrRasterSearchFlag;
    
    TEncMemoryTracer();
    
    static void init(std::string fileName);
    static void finalize();
    
    static void initLCU(Int xLCU, Int yLCU, Int idTile, Int idFrame);
    static void initCU(Int xCU, Int yCU, Int depthCU);
    static void initPU(Int idPart, Int sizePU, Int idRefFrame);
    static void insertFirstSearch(Int xStart, Int yStart);
    static void insertCandidate(Int xCand, Int yCand);
    static void insertRasterSearch(Int xLeft, Int xRight, Int yTop, Int yBottom);
    
};

#endif	/* TENCMEMORYTRACER_H */
