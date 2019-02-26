

//usage of the selector without PROOF: 
//TFile* myfile = TFile::Open("../../../MyData/PhysicsMain....");
//tree->Process("Print_7_Efficiencies_Selector.C+");

//usage of this PROOF macro:
//.x Run_PROOF_Print_7_Eff_TSelector.C

#include "Draw_Puc_Cell_Met_Sig_Efficiencies.h"
void Run_PROOF_Draw_Puc_Cell_ETmiss_Efficiencies(){
    gROOT->ProcessLine(".L Missing_ET_Significance/Draw_Puc_Cell_Met_Sig_Efficiencies.C+");
    TChain* mychain = new TChain( "tree" , "Draw_Puc_Cell_ETMiss_Efficiency" );
    mychain->Add("../DATA/mincer_data/PhysicsMain.L1KFXEunprescaledtriggers.2016.f731f758_m1659m1710.Run309759.48Runs.root");
    TProof* proof = TProof::Open("workers=8");
    proof->Load("/home/joseph/ATLAS_Research/HLT_Efficiency_Analysis_Macros/Missing_ET_Significance/Draw_Puc_Cell_Met_Sig_Efficiencies.C+");
    Draw_Puc_Cell_Met_Sig_Efficiencies* analysis = new Draw_Puc_Cell_Met_Sig_Efficiencies();
    mychain->SetProof();
    mychain->Process((TSelector *) analysis);
}

