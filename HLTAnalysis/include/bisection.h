#ifndef BISECTION_H
#define BISECTION_H

#include "mincerMacros.h"
#include "userInfo.h"

class Bisection{
private:
Float_t binwidth;
Float_t individAThreshFinal;
Float_t individBThreshFinal;
Int_t numPassedProcess1WithActintCut; 
Float_t target;
Float_t lwrbnd, uprbnd;
Float_t x1,x3;
Float_t Process2FracX1WithActintCut, Process2FracX2WithActintCut,Process2FracX3WithActintCut;
Float_t numKeepx1,numKeepx2,numKeepx3;
Float_t epsilon;
Float_t initialGuess;
Float_t firstguess;
TH1F* algAHist;
TH1F* algBHist;
TH1F *algAMETtarget;
TH1F *algBMETtarget;

Float_t algAMETx1thresh,
        algAMETx2thresh,
        algAMETx3thresh,
        algBMETx1thresh,
        algBMETx2thresh, 
        algBMETx3thresh;


Float_t algAMET,algBMET, metl1,passnoalg_actint ;
Int_t passnoalgL1XE10,passnoalgL1XE30,passnoalgL1XE40,passnoalgL1XE45;






public:
//constructor
void Bisection( userInfo* parameters );
void ComputeInitialExtremaThresh();
void PrintParameters();


};

#endif //BISECTION_H
