void ChangeInTimePileupToActualInteractionsPerCrossing( const char* filename ){
    // UPDATE opens an existing file for writing. if no file exists, is created
    TFile* file = TFile::Open( filename , "UPDATE" );
    TTree* tree = (TTree*)file->Get("METTree");

    float old_actint , new_actint;

    TBranch *new_actint_branch = tree->Branch( "ActualInteractionsPerCrossing", &new_actint , "ActualInteractionsPerCrossing/F");
    tree->SetBranchAddress( "InTimePileup", &old_actint);

    const Long64_t nentries = tree->GetEntries();
    for ( Long64_t i = 0 ; i < nentries ; i++ ){
        tree->GetEntry( i );
        new_actint = old_actint;
        new_actint_branch->Fill();
    }
    file->cd();
    tree->Print();
    tree->Write("",TObject::kOverwrite);
    file->Close();
}
