#include <TH1F.h>
#include <TFile.h>
#include <TNtuple.h>
#include <TList.h>
#include <TString.h>

void PlotEventNumbOverlap(){

    TFile* mincerfile = TFile::Open("$DATA/ZeroBiasL1KF2016R307195R311481.51Runs.root","READ");  
    TFile* jburrfile = TFile::Open("data/totalntuple16.root","READ");

    TTree* mincertree = (TTree*) mincerfile->Get("tree");
    TTree* burrtree = (TTree*) jburrfile->Get("METTree");


    Int_t mincerRunNumber, jburrRunNumber, mincereventnumber;
    ULong64_t jburreventnumber; 
    Int_t mincerpassrndm;
    Bool_t jburrpassrndm;
    
    UInt_t RunNumber;
    Int_t runLow = 307195;
    Int_t runHigh = 311481;
    Int_t nbins = 10000;
    Int_t mincereventnumberlow = -2.1474832e9;
    Int_t mincereventnumberhigh = 2.1474832e9;
    Int_t jburreventnumberlow = 32452;
    Int_t jburreventnumberhigh = 7.04e9;


    TH1F* mincerhist = new TH1F("histo1" , "Mincer Hist" , nbins , runLow , runHigh );
    TH1F* burrhist = new TH1F("histo2" , "Jburr Hist" , nbins , runLow , runHigh);
    TH1F* diffhist = 0;


    mincertree->SetBranchAddress("runnum",&mincerRunNumber);
    mincertree->SetBranchAddress("passrndm",&mincerpassrndm);
    mincertree->SetBranchAddress("eventnum",&mincereventnumber);
    burrtree->SetBranchAddress("HLT_noalg_zb_L1ZB.passed",&jburrpassrndm);
    burrtree->SetBranchAddress("RunNumber",&RunNumber);
    burrtree->SetBranchAddress("EventNumber",&jburreventnumber);


    Int_t mincerentries = mincertree->GetEntries();
    Int_t burrentries = burrtree->GetEntries();

    //well, what you should do it figure out what the distribution of event numbers looks like after you cut on the run
    //number because that might cut it down a lot and make the event numbers match up 

    //plot the intersection of event numbers, so constrain mincer's data by jburrs event numbers and jburrs data by
    //mincers event numbers 
    for ( Int_t i = 0 ; i < mincerentries ; i++){
        mincertree->GetEntry(i);
        if (mincerpassrndm > 0.5 && mincerRunNumber < 310000 && mincereventnumber > jburreventnumberlow && mincereventnumber < jburreventnumberhigh ){
        mincerhist->Fill(mincerRunNumber + 10.);
        }
    }

    for ( Int_t i = 0 ; i < burrentries; i++){
        burrtree->GetEntry(i);
        if (jburrpassrndm && RunNumber < runHigh && RunNumber > runLow && jburreventnumber > mincereventnumberlow && jburreventnumber < mincereventnumberhigh ){
        burrhist->Fill(RunNumber);
        }
    }

    diffhist->Add(mincerhist,burrhist,1.,-1.);

    diffhist->SetLineColor(kTeal);
    mincerhist->SetLineColor(kRed);
    burrhist->SetLineColor(kBlue);

    mincerhist->Draw();
    burrhist->Draw("SAME");
    diffhist->Draw("SAME");


    TFile* outfile = TFile::Open("EventNumOverlap.root","RECREATE");
    mincerhist->Write();
    burrhist->Write();
    diffhist->Write();


}

