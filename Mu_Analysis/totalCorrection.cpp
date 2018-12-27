#include <TChain.h>
#include <TSelector.h>
#include <TEfficiency.h>

#include "Compute_L1XE30_Efficiency/ComputeL1XE30toZBEfficiency.h"
#include "Compute_L1XE50_L1XE30_Efficiency/ComputeL1XE50toL1XE30Efficiency.h"

#include "CorrectL1XE30toZB/CorrectL1XE30toZB.h"
#include "CorrectL1XE50toZB/CorrectL1XE50toZB.h"

int totalCorrection(){

    std::cout << "Computing L1XE30 Efficiency from ZB MET Data" << std::endl;
    // Compute l1xe30 efficiencies from ZB data
    ComputeL1XE30toZBEfficiency* buildl1xe30Efficiencies =
        (ComputeL1XE30toZBEfficiency*)TSelector::GetSelector("Compute_L1XE30_Efficiency/ComputeL1XE30toZBEfficiency.C+");
    TChain* zb_chain = new TChain( "METTree" , "zb_chain" );
    zb_chain->Add("~/DATA/ZB/user.jburr.2017_11_17.ZB/*");
    zb_chain->Process(buildl1xe30Efficiencies);

    TChain* jetm10_chain = new TChain( "METTree", "jetm10chain");
    jetm10_chain->Add("~/DATA/PhysicsMain/JburrJETM10*");

    std::cout << "Correcting L1XE30 Data back to ZB MET Data" << std::endl;
    // correct the l1xe30 data back to match ZB data
    CorrectL1XE30toZB* correctToZB = (CorrectL1XE30toZB*) TSelector::GetSelector("CorrectL1XE30toZB/CorrectL1XE30toZB.C+");
    jetm10_chain->Process(correctToZB);

    std::cout << "Computing L1XE50 Efficiency from L1XE30 JETM10 Data" << std::endl;
    // Compute l1xe50 efficiencies from the jetm10 l1xe30 data
    ComputeL1XE50toL1XE30Efficiency* createL1XE50Efficiencies =
        (ComputeL1XE50toL1XE30Efficiency*) TSelector::GetSelector("Compute_L1XE50_L1XE30_Efficiency/ComputeL1XE50toL1XE30Efficiency.C+");
    jetm10_chain->Process( createL1XE50Efficiencies );

    std::cout << "Correcting L1XE50 all the way back to ZB MET Data" << std::endl;
    // Correct L1XE50 data back to zerobias data
    CorrectL1XE50toZB* CorrectL1XE50DataAllWay = (CorrectL1XE50toZB*) TSelector::GetSelector("CorrectL1XE50toZB/CorrectL1XE50toZB.C+");
    jetm10_chain->Process( CorrectL1XE50DataAllWay );

    std::cout << "Successfully performed all of the corrections all the way back to zerobias" << std::endl;
    return(1);

}
