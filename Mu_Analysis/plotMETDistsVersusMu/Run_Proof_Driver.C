#include "TChain.h"

void Run_Proof_Driver(){
    TProof::Open("");
    TChain* mychain = new TChain( "METTree" , "Jburr_CELL_MET_Dists_versus_Mu" );
    //mychain->Add("~/DATA/user*.root");
    mychain->Add("~/Downloads/user.jburr.2017_11_17.ZB/*");
    mychain->SetProof();
    mychain->Process("PlotMETDistsVersMu.C+");
}
