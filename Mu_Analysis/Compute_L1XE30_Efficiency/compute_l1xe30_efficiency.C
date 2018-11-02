#include "ComputeL1XE30toZBEfficiency.h"
void compute_l1xe30_efficiency(){
    ComputeL1XE30toZBEfficiency* myAnalysis = (ComputeL1XE30toZBEfficiency*)TSelector::GetSelector("ComputeL1XE30toZBEfficiency.C++g");
    TChain* mychain = new TChain( "METTree" , "mychain" );
    mychain->Add("~/DATA/ZB/user.jburr.2017_11_17.ZB/*");
    mychain->Process(myAnalysis);
}

