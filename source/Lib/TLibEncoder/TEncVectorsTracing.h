#ifndef VECTORSHANDLING_H
#define	VECTORSHANDLING_H

#include <iosfwd>
#include <string>
#include <unistd.h>
#include <map>
#include <fstream>
#include <iostream>

#include "../TLibCommon/TypeDef.h"

class TEncVectorsTracing {    
private:
    
    static UInt wFrameInCU, hFrameInCU;
    static std::map<std::pair<UInt, UInt>, Short*** > mvFrame;
    static std::fstream fp;
    
    static UInt idRefFrame;
    static bool bBi;
    
    static void xAllocNewVectorsFrame(std::pair<UInt, UInt> p);
   
    
public:
    TEncVectorsTracing();
    
    static void init(std::string fileName, UInt wFrame, UInt hFrame);
    static void finalize();
    static void insertMV(UInt idCurrFrame, UInt xCU, UInt yCU, Short xMv, Short yMv);

    static void reportMv();
    
    static void setIdRefFrame(UInt id);
    static void setBiPrediction(bool b);
};

#endif	/* VECTORSHANDLING_H */

