void Create_Missing_Et_Significance_Branch_from_Single_tree( const char* filename ){
    // UPDATE opens an existing file for writing. if no file exists, is created
    TFile* file = TFile::Open( filename , "UPDATE" );
    TTree* tree = (TTree*)file->Get("tree");
    TString METCELL_FLAG_NAME = "metcell";
    TString SUMETCELL_FLAG_NAME = "setcell";

    float metcell, sumetcell, missing_et_significance, sigma;

    // magic hard-coded constants determined by fits from mincer
    const Float_t a = 3.0;
    const Float_t b = 0.465;

    TBranch *missing_et_significance_branch = tree->Branch("missing_et_significance", &missing_et_significance , "missing_et_significance/F");
    tree->SetBranchAddress( METCELL_FLAG_NAME , &metcell );
    tree->SetBranchAddress( SUMETCELL_FLAG_NAME , &sumetcell );


    const Long64_t nentries = tree->GetEntries();
    for ( Long64_t i = 0 ; i < nentries ; i++ ){
        tree->GetEntry( i );
        sigma = a + b * TMath::Sqrt( sumetcell );
        missing_et_significance = metcell / sigma;
        missing_et_significance_branch->Fill();
    }
    file->cd();
    tree->Print();
    tree->Write("",TObject::kOverwrite);
    delete file;
}
