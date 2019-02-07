{
    TChain* muonChain = new TChain("METTree","JETM10Chain");
    muonChain->Add("PhysicsMain/JburrJETM10*");
    TFile* newFile = new TFile("JETM10_missing_et_significance.root","RECREATE","JETM10_missing_significance_file");

    TChain* newChain = (TChain*)muonChain->CloneTree(0); // create a clone to make a copy
    TTree* tree = newChain->GetTree(); // cannot fill a chain. must get the tree version

    if (newChain == 0) return;

    float missing_et_significance = 0.0;
    TBranch *missing_et_significance_branch = tree->Branch("missing_et_significance", &missing_et_significance , "missing_et_significance/F");

    Float_t metcell = 0;
    Float_t sumetcell = 0;

    muonChain->SetBranchAddress("cell.met", &metcell);
    muonChain->SetBranchAddress("cell.sumet", &sumetcell);

    const Float_t a = 3.0;
    const Float_t b = 0.465;

    Float_t sigma = 0;

    const Int_t nentries = muonChain->GetEntries();
    for (size_t i = 0 ; i < nentries ; i++ ){
        Int_t nb = muonChain->GetEntry( i );
        sigma = a + b * TMath::Sqrt( sumetcell );
        missing_et_significance = metcell / sigma;
        tree->Fill();
    }
    newFile->cd();
    tree->Write();
}
