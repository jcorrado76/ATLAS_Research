#include "zbToL1XE30/plotMETDistsVersusMu/PlotMETDistsVersMu.h"
#include <TChain.h>
#include <TSelector.h>
#include <TEfficiency.h>

int totalCorrection(){
    PlotMETDistsVersMu* myAnalysis = (PlotMETDistsVersMu*)TSelector::GetSelector("zbToL1XE30/plotMETDistsVersusMu/PlotMETDistsVersMu.C+");
    TChain* mychain = new TChain( "METTree" , "mychain" );
    mychain->Add("~/DATA/ZB/user.jburr.2017_11_17.ZB/*");
    mychain->Process(myAnalysis);

    return(1);

}


