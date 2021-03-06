#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TImage.h>

void GenerateTableDifferences(){
    /* this macro needs to compute the histograms for the two data sets, and compute their difference and generate a new
     * histogram, and perhaps a table with the most interesting differences */


    TFile* mincerfile = TFile::Open("$DATA/ZeroBiasL1KF2016R307195R311481.51Runs.root","READ");  
    TFile* jburrfile = TFile::Open("data/totalntuple16.root","READ");

    TTree* mincertree = (TTree*) mincerfile->Get("tree");
    TTree* burrtree = (TTree*) jburrfile->Get("METTree");


    Int_t mincerRunNumber, jburrRunNumber;
    Int_t mincerpassrndm;
    Bool_t jburrpassrndm;
    
    UInt_t RunNumber;
    Int_t runLow = 307195;
    Int_t runHigh = 311481;
    Int_t nbins = 10000;

    TH1F* mincerhist = new TH1F("histo1" , "Mincer Hist" , nbins , runLow , runHigh );
    TH1F* mincerhist_staggered = new TH1F("histo1_staggered" , "Mincer Hist Staggered" , nbins , runLow , runHigh );
    TH1F* burrhist = new TH1F("histo2" , "Jburr Hist" , nbins , runLow , runHigh);
    TH1F* diffhist= new TH1F("histo3" , "Diff Hist" , nbins , runLow , runHigh);


    mincertree->SetBranchAddress("runnum",&mincerRunNumber);
    mincertree->SetBranchAddress("passrndm",&mincerpassrndm);
    burrtree->SetBranchAddress("HLT_noalg_zb_L1ZB.passed",&jburrpassrndm);
    burrtree->SetBranchAddress("RunNumber",&RunNumber);


    Int_t mincerentries = mincertree->GetEntries();
    Int_t burrentries = burrtree->GetEntries();


    for ( Int_t i = 0 ; i < mincerentries ; i++){
        mincertree->GetEntry(i);
        if (mincerpassrndm > 0.5 && mincerRunNumber < 310000 ){
        mincerhist->Fill(mincerRunNumber);
        mincerhist_staggered->Fill(mincerRunNumber + 10.0);
        }
    }

    for ( Int_t i = 0 ; i < burrentries; i++){
        burrtree->GetEntry(i);
        if (jburrpassrndm && RunNumber < runHigh && RunNumber > runLow){
        burrhist->Fill(RunNumber);
        }
    }


    mincerhist->SetLineColor(kRed);
    burrhist->SetLineColor(kBlue);

    diffhist->Add(mincerhist,burrhist,1.,-1.);

    diffhist->SetLineColor(kMagenta);

    TCanvas* mycanv = new TCanvas("c1" , "Differences between mincer data and jburr data");
    mincerhist->Draw();
    burrhist->Draw("SAME");

    TLegend *legend = new TLegend(0.57,0.15,0.9,0.4,"","NDC");
    legend->AddEntry(mincerhist);
    legend->AddEntry(burrhist);
    legend->Draw();

    mycanv->SetTitle("Difference of Mincer Data to Jburr Data");
    mycanv->Draw();

    TImage* img = TImage::Create();
    img->FromPad(mycanv);
    img->WriteImage("pictures/DifferencePlot.png");


    TFile* outputfile = new TFile("RunNumberHists.root","RECREATE");

    mincerhist->Write();
    mincerhist_staggered->Write();
    burrhist->Write();
    diffhist->Write();

}


