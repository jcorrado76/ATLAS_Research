#include "Compute_L1XE30_Efficiency/ComputeL1XE30toZBEfficiency.h"
#include "CorrectL1XE30toZB/CorrectL1XE30toZB.h"
#include "L1XE30toL1XE50/plotl130dists/BuildEfficiencyL150.h"
#include "L1XE30toL1XE50/performL130to50Correction/CorrectL1XE50ToZB.h"
#include <TChain.h>
#include <TSelector.h>
#include <TEfficiency.h>

int totalCorrection(){
    ComputeL1XE30toZBEfficiency* buildl1xe30Efficiencies = (ComputeL1XE30toZBEfficiency*)TSelector::GetSelector("Compute_L1XE30_Efficiency/ComputeL1XE30toZBEfficiency.C+");
    TChain* zb_chain = new TChain( "METTree" , "zb_chain" );
    zb_chain->Add("~/DATA/ZB/user.jburr.2017_11_17.ZB/*");
    zb_chain->Process(buildl1xe30Efficiencies);

    CorrectL1XE30toZB* correctToZB = (CorrectL1XE30toZB*) TSelector::GetSelector("CorrectL1XE30toZB/CorrectL1XE30toZB.C+");
    TChain* jetm10_chain = new TChain( "METTree", "jetm10chain");
    jetm10_chain->Add("~/DATA/PhysicsMain/JburrJETM10*");
    jetm10_chain->Process(correctToZB);

    //BuildEfficiencyL150* createL1XE50Efficiencies = (BuildEfficiencyL150*) TSelector::GetSelector("L1XE30toL1XE50/plotl130dists/BuildEfficiencyL150.C+");
    //jetm10_chain->Process( createL1XE50Efficiencies );

    //CorrectL1XE50ToZB* CorrectL1XE50DataAllWay = (CorrectL1XE50ToZB*) TSelector::GetSelector("L1XE30toL1XE50/performL130to50Correction/CorrectL1XE50ToZB.C+");
    //jetm10_chain->Process( CorrectL1XE50DataAllWay );


    return(1);

}


