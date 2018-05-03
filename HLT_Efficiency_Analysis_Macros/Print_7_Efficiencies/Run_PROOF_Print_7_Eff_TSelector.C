

//usage of the selector without PROOF: 
//TFile* myfile = TFile::Open("../../../MyData/PhysicsMain....");
//tree->Process("Print_7_Efficiencies_Selector.C+");

//usage of this PROOF macro:
//.x Run_PROOF_Print_7_Eff_TSelector.C

{
    TProof::Open("");
    TChain* mychain = new TChain( "tree" , "Print_7_Eff_Chain" );
    mychain->Add("../../../ATLAS_DATA/PhysicsMain.L1KFmuontriggers.2016.f731f758_m1659m1710.Run309759.48Runs.root");
    mychain->SetProof();
    mychain->Process("Print_7_Efficiencies_Selector.C+");
}

