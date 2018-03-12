{
    TFile* mincerfile = TFile::Open("$DATA/ZeroBiasL1KF2016R307195R311481.51Runs.root","READ");  
    TFile* jburrfile = TFile::Open("data/totalntuple16.root","READ");

    TTree* mincertree = (TTree*) mincerfile->Get("tree");
    TTree* burrtree = (TTree*) jburrfile->Get("METTree");


    Int_t mincerRunNumber, jburrRunNumber;
    Int_t mincerpassrndm;
    Bool_t jburrpassrndm;
    UInt_t RunNumber;


    Int_t nbins = 10000;

    TH1F* mincerhist = new TH1F("histo1" , "Mincer Hist" , nbins , 0.0 , 200.0);
    TH1F* burrhist = new TH1F("histo2" , "Jburr Hist" , nbins , 0.0 , 200.0);


    mincertree->SetBranchAddress("runnum",&mincerRunNumber);
    mincertree->SetBranchAddress("passrndm",&mincerpassrndm);
    burrtree->SetBranchAddress("HLT_noalg_zb_L1ZB.passed",&jburrpassrndm);
    burrtree->SetBranchAddress("RunNumber",&RunNumber);


    Int_t mincerentries = mincertree->GetEntries();
    Int_t burrentries = burrtree->GetEntries();


    for ( Int_t i = 0 ; i < mincerentries ; i++){
        mincertree->GetEntry(i);
        if (mincerpassrndm > 0.5 ){
        mincerhist->Fill(mincerRunNumber);
        }
    }

    for ( Int_t i = 0 ; i < burrentries; i++){
        burrtree->GetEntry(i);
        if (jburrpassrndm && RunNumber < 311481 && RunNumber > 307195 ){
        burrhist->Fill(RunNumber);
        }
    }

    mincerhist->SetLineColor(kRed);
    burrhist->SetLineColor(kBlue);


    TCanvas* mycanv = new TCanvas("c1" , "2016 Data Run Number Distribution Comparison");
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
    img->WriteImage("pictures/2016ZBRunNumberComparison.png");


}

