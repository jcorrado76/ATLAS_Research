#include "ComputeL1XE50toL1XE30Efficiency.h"
void compute_l1xe50_l1xe30Efficiency(){
    ComputeL1XE50toL1XE30Efficiency* myAnalysis = (ComputeL1XE50toL1XE30Efficiency*)TSelector::GetSelector("ComputeL1XE50toL1XE30Efficiency.C+");
    TChain* mychain = new TChain( "METTree" , "mychain" );
    mychain->Add("~/DATA/PhysicsMain/user.jburr.2017_11_17.JETM10/*");
    mychain->Process(myAnalysis);
}

