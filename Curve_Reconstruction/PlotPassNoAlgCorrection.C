{
    gSystem->Setenv("DATA", "~/ATLAS_DATA");

    TString zb_pathname = "$DATA/ZeroBiasL1KF2016R307195R311481.51Runs.root";
    TString pna_pathname = "$DATA/PhysicsMain.L1KFnoalgXEtriggers.2016.f731f758_m1659m1710.Run309759.48Runs.root";


    gSystem->ExpandPathName( zb_pathname );
    gSystem->ExpandPathName( pna_pathname );

    TProof* proof = TProof::Open("");

    TCanvas* mycanv = new TCanvas();



    if ( gSystem->AccessPathName( zb_pathname ) ){
         
        TFile* zb_file = TFile::Open( zb_pathname );

        TChain* zb_chain = new TChain( "tree" , "Curve_reconst_Chain" );
        zb_chain->Add( zb_pathname );
        zb_chain->SetProof();
        proof->SetParameter("PROOF_UseTreeCache" , (Int_t)0);
        zb_chain->Process("ZB_Eff_Selector.C+");
    }
    else {
        std::cout << "Unable to open zerobias file" << std::endl;
        return;
    }


    //WRITE THE OBJECTS TO FILE IN ZB_EFF_SELECTOR, AND READ THEM HERE SO YOU CAN PLOT THEM

    histo1->Draw();


	//MOVE ON TO MAKING THIS WORK AFTER YOU HAVE SUCCESSFULLY READ AND PLOTTED THE TOTAL RANDOM ZB CURVE`

    //if ( gSystem->AccessPathName( pna_pathname ) ){
         
        //TFile* pna_file = TFile::Open( pna_pathname );

        //TChain* pna_chain = new TChain( "tree" , "Curve_reconst_Chain" );
        //pna_chain->Add( pna_pathname );
        //pna_chain->SetProof();
        //proof->SetParameter("PROOF_UseTreeCache" , (Int_t)0);
        //pna_chain->Process(".C+");
    //}
    //else {
        //std::cout << "Unable to open passnoalg file" << std::endl;
        //return;
    
//need to plot the curves with passsnoalg cuts
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//need to plot the zerobias curve 















}

