#include "TString.h"
#include "TROOT.h"
#include "userInfo.h"



void actintAnalysis(){
    TFile* threeEfficiencies( const TString& , const TString& , const Float_t , const TString);
    TString algA = "metmht";
    TString algB = "mettopoclpuc";

    userInfo* logFileParams = new userInfo();


    //TODO: need to find a way to change the name of the root file each time you save
    //with a different actint cut

    logFileParams->Print();
    logFileParams->setActintCut(40.0);
    logFileParams->Print();
    threeEfficiencies(algA,algB, 0.0059, "ActintAnalysis");
    logFileParams->setActintCut(35.0);
    threeEfficiencies(algA,algB, 0.0059, "ActintAnalysis");
    logFileParams->setActintCut(30.0);
    threeEfficiencies(algA,algB, 0.0059, "ActintAnalysis");
    logFileParams->setActintCut(25.0);
    threeEfficiencies(algA,algB, 0.0059, "ActintAnalysis");
    logFileParams->setActintCut(20.0);
    threeEfficiencies(algA,algB, 0.0059, "ActintAnalysis");


}
