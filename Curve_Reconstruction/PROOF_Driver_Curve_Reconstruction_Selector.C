


{
    gSystem->Setenv("DATA", "~/ATLAS_DATA");

    TString zb_pathname = "$DATA/ZeroBiasL1KF2016R307195R311481.51Runs.root";

    gSystem->ExpandPathName( zb_pathname );
    
    if (gSystem->AccessPathName( zb_pathname ) ){

        std::cout << "Successfully accessed data file" << std::endl;

        TFile* zb_file = TFile::Open(  zb_pathname );

        std::cout << "Successfully opened data file" << std::endl;


        tree->Process("Curve_Reconstruction_Selector.C");






/*
        TProof* proof = TProof::Open("");
        TChain* mychain = new TChain( "tree" , "Curve_Reconst_Chain" );
        mychain->Add( zb_pathname );
        mychain->SetProof();
        proof->SetParameter("PROOF_UseTreeCache", (Int_t)0);
        mychain->Process( "Curve_Reconstruction_Selector.C+");
        */

    }
    else{
        std::cout << "Could not access filename" << std::endl;
        std::cout << "Filename:\n" << zb_pathname << std::endl;
    }

}
