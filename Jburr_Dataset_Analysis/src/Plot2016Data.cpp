#include "Plot2016Data.h"
void Plot2016Data(){
    TFile* mincerfile = TFile::Open("$DATA/ZeroBiasL1KF2016R307195R311481.51Runs.root","READ");  
    TFile* jburrfile = TFile::Open("data/totalntuple16.root","READ");

    TTree* mincertree = (TTree*) mincerfile->Get("tree");
    TTree* burrtree = (TTree*) jburrfile->Get("METTree");

    Float_t mincermetcell, jburrmetcell;
    Int_t mincerpassrndm;
    Bool_t jburrpassrndm;
    UInt_t RunNumber;
    Int_t mincerRunNumber;

    Int_t mincerRunHigh = 310000;
    Int_t jburrRunLow = 307195;
    Int_t jburrRunHigh = 311481;

    Float_t metlow = 0.0;
    Float_t methigh = 200.0;

    TH1F* mincerhist = new TH1F("histo1" , "Mincer Hist" , 200 , metlow , methigh );
    TH1F* burrhist = new TH1F("histo2" , "Jburr Hist" , 200 , metlow , methigh);


    mincertree->SetBranchAddress("metcell",&mincermetcell);
    mincertree->SetBranchAddress("passrndm",&mincerpassrndm);
    mincertree->SetBranchAddress("runnum",&mincerRunNumber);
    burrtree->SetBranchAddress("cell.met",&jburrmetcell);
    burrtree->SetBranchAddress("HLT_noalg_zb_L1ZB.passed",&jburrpassrndm);
    burrtree->SetBranchAddress("RunNumber",&RunNumber);


    Int_t mincerentries = mincertree->GetEntries();
    Int_t burrentries = burrtree->GetEntries();


    for ( Int_t i = 0 ; i < mincerentries ; i++){
        mincertree->GetEntry(i);
        if (mincerpassrndm > 0.5 && mincerRunNumber < mincerRunHigh ){
        mincerhist->Fill(mincermetcell);
        }
    }

    for ( Int_t i = 0 ; i < burrentries; i++){
        burrtree->GetEntry(i);
        if (jburrpassrndm && RunNumber < jburrRunHigh && RunNumber > jburrRunLow ){
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
    img->WriteImage("pictures/2016ZBDataComparisonWpassrndmWRunNumberCutWMincerRunNumbCut.png");


}

