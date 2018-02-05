{
    gSystem->Setenv("DATA", "~/ATLAS_DATA");

    TString zb_pathname = "$DATA/ZeroBiasL1KF2016R307195R311481.51Runs.root";

    gSystem->ExpandPathName( zb_pathname );

    if ( gSystem->AccessPathName( zb_pathname ) ){
         
        TFile* zb_file = TFile::Open( zb_pathname );

        TChain* mychain = new TChain( "tree" , "Curve_reconst_Chain" );
        mychain->Add( zb_pathname );
        TProof* proof = TProof::Open("");
        mychain->SetProof();
        proof->SetParameter("PROOF_UseTreeCache" , (Int_t)0);
        mychain->Process("ZB_Eff_Selector.C+");

    }
    else{
        std::cout << "Could not access filename " << std::endl;
        std::cout << "Filename:\n" << zb_pathname << std::endl;
    }

}
