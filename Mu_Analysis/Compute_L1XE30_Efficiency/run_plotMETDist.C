#include "./PlotMETDistsVersMu.h"
void run_plotMETDist(){
    PlotMETDistsVersMu* myAnalysis = (PlotMETDistsVersMu*)TSelector::GetSelector("PlotMETDistsVersMu.C+g");
    TChain* mychain = new TChain( "METTree" , "mychain" );
    mychain->Add("~/DATA/ZB/user.jburr.2017_11_17.ZB/*");
    mychain->Process(myAnalysis);
}

