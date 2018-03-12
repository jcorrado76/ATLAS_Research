{
    TFile* mincerfile = TFile::Open("$DATA/ZeroBiasL1KF2016R307195R311481.51Runs.root","READ");  
    TFile* jburrfile = TFile::Open("./user.jburr.2017_11_17.data16.ZB/totalntuple.root","READ");

    TTree* mincertree = (TTree*) mincerfile->Get("tree");
    TTree* burrtree = (TTree*) jburrfile->Get("METTree");


    Float_t mincerRunNumber, jburrRunNumber;
    Int_t mincerpassrndm;
    Bool_t jburrpassrndm;
    UInt_t RunNumber;



    TH1F* mincerhist = new TH1F("histo1" , "Mincer Hist" , 200 , 0.0 , 200.0);
    TH1F* burrhist = new TH1F("histo2" , "Jburr Hist" , 200 , 0.0 , 200.0);


    mincertree->SetBranchAddress("runnum",&mincerRunNumber);
    mincertree->SetBranchAddress("passrndm",&mincerpassrndm);
    burrtree->SetBranchAddress("HLT_noalg_zb_L1ZB.passed",&jburrpassrndm);
    burrtree->SetBranchAddress("RunNumber",&RunNumber);


    Int_t mincerentries = mincertree->GetEntries();
    Int_t burrentries = burrtree->GetEntries();


    for ( Int_t i = 0 ; i < mincerentries ; i++){
        mincertree->GetEntry(i);
        if (mincerpassrndm > 0.5 ){
        mincerhist->Fill(mincermetcell);
        }
    }

    for ( Int_t i = 0 ; i < burrentries; i++){
        burrtree->GetEntry(i);
        if (jburrpassrndm && RunNumber < 311481 && RunNumber > 307195 ){
        burrhist->Fill(jburrmetcell);
        }
    }



    mincerhist->SetLineColor(kRed);
    burrhist->SetLineColor(kBlue);


    TCanvas* mycanv = new TCanvas("c1" , "2016 Data Cell Distribution Comparison");
    mincerhist->Draw();
    burrhist->Draw("SAME");

    TLegend *legend = new TLegend(0.57,0.15,0.9,0.4,"","NDC");
    legend->AddEntry(mincerhist);
    legend->AddEntry(burrhist);
    legend->Draw();

    mycanv->SetTitle("Comparison of Mincer 2016 Data to Jburr 2016 Data with passrndm");
    mycanv->SetLogy();
    mycanv->Draw();

    TImage* img = TImage::Create();
    img->FromPad(mycanv);
    img->WriteImage("2016ZBDataComparisonWpassrndmWRunNumberCut.png");


}

