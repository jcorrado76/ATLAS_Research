{
    TChain* mychain = new TChain( "tree" , "Mincer Event Num Duplicate Chain");
    mychain->Add("$DATA/ZeroBiasL1KF2016R307195R311481.51Runs.root");

    TProof *proof = TProof::Open("");
    //proof->Load("CheckDuplicateEventNumbs.C+");
    mychain->SetProof();
    mychain->Process("CheckDuplicateEventNumbs.C+");
}

