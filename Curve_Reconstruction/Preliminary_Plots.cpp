{
    TString zb_path  = "$(DATA)/ZeroBiasL1KF2016R307195R311481.51Runs.root";
    TString sig_path = "$(DATA)/PhysicsMain.L1KFmuontriggers.2016.f731f758_m1659m1710.Run309759.48Runs.root";


    if (!gSystem->AccessPathName( zb_path ) ){
        std::cout << "could not open root file" << std::endl;
    }
    if (!gSystem->AccessPathName( sig_path ) ){
        std::cout << "could not open root file" << std::endl;
    }

    std::cout << "Signal and zb files accessed successfully" << std::endl;

    TFile* zb_file      = TFile::Open( zb_path , "READ");
    TTree* zb_tree      = (TTree*)zb_file->Get("tree");
    Int_t zb_nentries   = zb_tree->GetEntries();

    TFile* sig_file = TFile::Open( sig_path , "READ");
    TTree* sig_tree = (TTree*)sig_file->Get("tree");
    Int_t sig_nentries   = sig_tree->GetEntries();
    

    Float_t metcell = 0;
    Int_t passrndm = 0;
    Int_t passnoalgL1XE10 = 0;
    Int_t passnoalgL1XE30 = 0;
    Int_t passnoalgL1XE40 = 0;
    Int_t passnoalgL1XE45 = 0;

    zb_tree->SetBranchAddress( "metcell" , &metcell );
    zb_tree->SetBranchAddress( "passrndm" , &passrndm );
    sig_tree->SetBranchAddress( "passnoalgL1XE10" , &passnoalgL1XE10);
    sig_tree->SetBranchAddress( "passnoalgL1XE30" , &passnoalgL1XE30);
    sig_tree->SetBranchAddress( "passnoalgL1XE40" , &passnoalgL1XE40);
    sig_tree->SetBranchAddress( "passnoalgL1XE45" , &passnoalgL1XE45);


    TH1F *MetCellHist = new TH1F( "histo0" , "Metcell Hist" , 300 , 0.0 , 80.0 );
    TH1F *MetCellHistPNA10 = new TH1F( "histo1" , "Metcell PNA 10" , 300 , 0.0 , 80.0 );
    TH1F *MetCellHistPNA30 = new TH1F( "histo2" , "Metcell PNA 30" , 300 , 0.0 , 80.0 );
    TH1F *MetCellHistPNA40 = new TH1F( "histo3" , "Metcell PNA 40" , 300 , 0.0 , 80.0 );
    TH1F *MetCellHistPNA45 = new TH1F( "histo4" , "Metcell PNA 45" , 300 , 0.0 , 80.0 );


    for ( Int_t i = 0 ; i < zb_nentries ; i++ ) {
        zb_tree->GetEntry(i);
        sig_tree->GetEntry(i);
        if (passrndm){
            MetCellHist->Fill( metcell );
        }
        if ( passnoalgL1XE10 > 0.5 ){
            MetCellHistPNA10->Fill( metcell );
        }
        if ( passnoalgL1XE30 > 0.5 ){
            MetCellHistPNA30->Fill( metcell );
        }
        if ( passnoalgL1XE40 > 0.5 ){
            MetCellHistPNA40->Fill( metcell );
        }
        if ( passnoalgL1XE45 > 0.5 ){
            MetCellHistPNA45->Fill( metcell );
        }
    }



    TCanvas *mycanv = new TCanvas( "mycanv" , "Preliminary Plots Canvas");
    TLegend *legend = new TLegend();
    legend->AddEntry( MetCellHist );
    legend->AddEntry( MetCellHistPNA10 );
    legend->AddEntry( MetCellHistPNA30 );
    legend->AddEntry( MetCellHistPNA40 );
    legend->AddEntry( MetCellHistPNA45 );

    MetCellHist->SetLineColor(kBlue);
    MetCellHistPNA10->SetLineColor(kGreen);
    MetCellHistPNA30->SetLineColor(kRed);
    MetCellHistPNA40->SetLineColor(kTeal);
    MetCellHistPNA45->SetLineColor(kBlack);

    MetCellHist->Draw();
    MetCellHistPNA10->Draw("SAME");
    MetCellHistPNA30->Draw("SAME");
    MetCellHistPNA40->Draw("SAME");
    MetCellHistPNA45->Draw("SAME");
    legend->Draw();
    mycanv->Draw();

}

