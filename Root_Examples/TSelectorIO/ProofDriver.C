{

    TString zbpath("$DATA/ZeroBiasL1KF2016R307195R311481.51Runs.root");
    TFile* ZeroBiasFile = TFile::Open(zbpath);
    /* I tried to do error handling here, but ROOT does not have any error-handling capability. Most methods simply
     * contain a return in the case that it throws an error */

   TChain* mychain = new TChain("ZeroBiasTree","TSelectorIOChain");
   mychain->Add(zbpath);

   TProof* proof_sesh = TProof::Open("");

   mychain->SetProof();

   

   mychain->Process("TSelectorIO.C+");



}

