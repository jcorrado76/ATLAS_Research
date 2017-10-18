#include "TString.h"
#include "TROOT.h"
#include "userInfo.h"



void actintAnalysis(){
    TFile* threeEfficiencies( const TString& , const TString& , const Float_t , const TString);
    TString algA = "metmht";
    TString algB = "mettopoclpuc";

    //TODO: need to find a way to change the name of the root file each time you save
    //with a different actint cut

    threeEfficiencies(algA,algB, 0.0059, "ActintAnalysis");
    logFileParams->setActintCut(0.0);
    threeEfficiencies(algA,algB, 0.0059, "ActintAnalysis");
}
