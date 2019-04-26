//usage of the selector without PROOF: 
//TFile* myfile = TFile::Open("../../../MyData/ZeroBiasKF....");
//tree->Process("Compute_Trigger_Rate_TSelector.C+");

//usage of this PROOF macro:
//.x Run_PROOF_Compute_Trigger_Rate_TSelector.C 
{
    TProof::Open("");
    TChain* mychain = new TChain( "tree" , "Compute_Trigger_Rate_Chain" );
    mychain->Add("../../../MyData/ZeroBiasL1KF2016R307195R311481.51Runs.root");
    mychain->SetProof();
    mychain->Process("Compute_Trigger_Rate_TSelector.C+");
}
