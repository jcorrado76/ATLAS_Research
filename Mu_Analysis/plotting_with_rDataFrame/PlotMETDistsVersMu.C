#include "RDataFrame.h"

// c++11 lambda function
auto metCut = [](double x) {
    return x > 4.;
}«»


PlotMETDistsVersMu(){
    ROOT::EnableImplicitMT(); // tell root you want parallel
    ROOT::RDataFrame d("METTree", "$DATA/totalJburrTuple.root"); // interface to TTree and TChain
    auto metcellHist = d.Filter("cell.met < 300.").Histo1D("cell.met"); // this should happen in parallel
    metcellHist->Draw();
}
