#include "TString.h"
#include "TH1.h"
#include "TFile.h"
#include "TTree.h"


void createHisto( const TString& algName = "" , const Float_t cut = 0 )
{
    /* will produce a histogram of an alg given a cut */
    const TString fileName = "ZeroBias2016R307195R311481Runs56.root";
    TString filePath = "../myData/" + fileName;
    TFile * file = TFile::Open(filePath, "READ");
    TTree* tree = (TTree*)file->Get("tree");

    Float_t algMEt;
    Int_t passrndmFlag;
    Int_t nentries = tree->GetEntries();
    tree->SetBranchAddress("passrndm",&passrndmFlag);
    tree->SetBranchAddress( algName , &algMEt);
    TH1F* myHist = new TH1F(algName , algName , 400 , 0 , 300);
    for (Int_t i = 0 ; i < nentries ; i++)
    {
        tree->GetEntry(i);
        if ( passrndmFlag > 0.5 && algMEt > cut )
        {
            myHist->Fill(algMEt);
        }
    }
    TCanvas* mycanv = new TCanvas();
    myHist->Draw();
    mycanv->SetLogy();
    myHist->GetXaxis()->SetTitle("MEt [GeV]");
    myHist->GetYaxis()->SetTitle("No. Events");
}
