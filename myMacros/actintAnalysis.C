#include "TString.h"
#include "TROOT.h"
#include "userInfo.h"



void actintAnalysis(){
    TFile* threeEfficiencies( const TString& , const TString& , const Float_t , const TString);
    TString algA = "metmht";
    TString algB = "mettopoclpuc";

    userInfo* logFileParams = new userInfo();

    logFileParams->Print();
    logFileParams->setActintCut(40.0);
    logFileParams->Print();
    threefficiencies(algA,algB, 0.0059, "ActintAnalysis");
    logFileParams->setActintCut(35.0);
    threefficiencies(algA,algB, 0.0059, "ActintAnalysis");
    logFileParams->setActintCut(30.0);
    threefficiencies(algA,algB, 0.0059, "ActintAnalysis");
    logFileParams->setActintCut(25.0);
    threefficiencies(algA,algB, 0.0059, "ActintAnalysis");
    logFileParams->setActintCut(20.0);
    threefficiencies(algA,algB, 0.0059, "ActintAnalysis");


}
