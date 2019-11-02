// TODO: generalize this and make it be: "addEmptyBranches" or "addConstantBranches"
// and take a constant as parameter
void Create_HLT_NOALG_L1xx_Branches( const char* filename ){
    // UPDATE opens an existing file for writing. if no file exists, is created
    TFile* file = TFile::Open( filename , "UPDATE" );
    TTree* tree = (TTree*)file->Get("METTree");

    Bool_t HLT_noalg_zb_L1xx_passed;
    Float_t HLT_noalg_zb_L1xx_prescale;

    // TODO: think about refactoring these strings into an argument
    TBranch *HLT_noalg_zb_L1xx_passed_branch = tree->Branch("HLT_noalg_zb_L1XE50.passed", 
            &HLT_noalg_zb_L1xx_passed , "HLT_noalg_zb_L1XE50.passed/O");
    TBranch *HLT_noalg_zb_L1xx_prescale_branch = tree->Branch("HLT_noalg_zb_L1XE50.prescale", 
            &HLT_noalg_zb_L1xx_prescale , "HLT_noalg_zb_L1XE50.prescale/F");

    const Long64_t nentries = tree->GetEntries();
    HLT_noalg_zb_L1xx_passed = 0;
    HLT_noalg_zb_L1xx_prescale = 0.0;
    for ( Long64_t i = 0 ; i < nentries ; i++ ){
        tree->GetEntry( i );
        HLT_noalg_zb_L1xx_passed_branch->Fill();
        HLT_noalg_zb_L1xx_prescale_branch->Fill();
    }
    file->cd();
    tree->Print();
    tree->Write("",TObject::kOverwrite);
    delete file;
}
