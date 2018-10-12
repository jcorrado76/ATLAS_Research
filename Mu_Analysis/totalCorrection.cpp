#include "zbToL1XE30/plotMETDistsVersusMu/PlotMETDistsVersMu.h"
#include "zbToL1XE30/PerformCorrection/CorrectingDistributions.h"
#include "L1XE30toL1XE50/plotl130dists/BuildEfficiencyL150.h"
#include "L1XE30toL1XE50/performL130to50Correction/CorrectL1XE50ToZB.h"
#include <TChain.h>
#include <TSelector.h>
#include <TEfficiency.h>

int totalCorrection(){
    PlotMETDistsVersMu* buildl1xe30Efficiencies = (PlotMETDistsVersMu*)TSelector::GetSelector("zbToL1XE30/plotMETDistsVersusMu/PlotMETDistsVersMu.C+");
    TChain* zb_chain = new TChain( "METTree" , "zb_chain" );
    zb_chain->Add("~/DATA/ZB/user.jburr.2017_11_17.ZB/*");
    zb_chain->Process(buildl1xe30Efficiencies);

    CorrectingDistributions* correctToZB = (CorrectingDistributions*) TSelector::GetSelector("zbToL1XE30/PerformCorrection/CorrectingDistributions.C+");
    TChain* jetm10_chain = new TChain( "METTree", "jetm10chain");
    jetm10_chain->Add("~/DATA/PhysicsMain/JburrJETM10*");
    jetm10_chain->Process(correctToZB);

    BuildEfficiencyL150* createL1XE50Efficiencies = (BuildEfficiencyL150*) TSelector::GetSelector("L1XE30toL1XE50/plotl130dists/BuildEfficiencyL150.C+");
    jetm10_chain->Process( createL1XE50Efficiencies );

    CorrectL1XE50ToZB* CorrectL1XE50DataAllWay = (CorrectL1XE50ToZB*) TSelector::GetSelector("L1XE30toL1XE50/performL130to50Correction/CorrectL1XE50ToZB.C+");
    jetm10_chain->Process( CorrectL1XE50DataAllWay );


    return(1);

}


