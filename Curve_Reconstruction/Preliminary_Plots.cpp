{
    gROOT->Reset();
    TString zb_path = "$(DATA)/ZeroBiasL1KF2016R307195R311481.51Runs.root";    

    if (!gSystem->AccessPathName( zb_path ) ){
        std::cout << "could not open root file" << std::endl;
    }

    std::cout << "File accessed successfully" << std::endl;

    TFile* zb_file      = TFile::Open( zb_path , "READ");
    TTree* zb_tree      = (TTree*)zb_file->Get("tree");
    Int_t zb_nentries   = zb_tree->GetEntries();

    

    Float_t metcell = 0;
    zb_tree->SetBranchAddress( "metcell" , &metcell );


    TH1F *MetCellHist = new TH1F( "histo" , "Metcell Hist" , 300 , 0.0 , 300.0 );


    for ( Int_t i = 0 ; i < zb_nentries ; i++ ) {
        zb_tree->GetEntry(i);
        MetCellHist->Fill( metcell );
    }



    TCanvas *mycanv = new TCanvas( "mycanv" , "Preliminary Plots Canvas");
    TLegend *legend = new TLegend();
    legend->AddEntry( MetCellHist );
    MetCellHist->Draw();
    legend->Draw();
    mycanv->Draw();

}

