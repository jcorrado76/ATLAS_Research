#include "TH1.h"
#include "TCanvas.h"
#include "TROOT.h"

void computeRightHandIntegral( const TString& algName ,
    const TString& fileName = "ZeroBias2016R307195R311481Runs56.root")
{
    gROOT->ProcessLine("gROOT->Time();");
    const TString dataFilePath = "../myData/" + fileName;
    TFile *file= TFile::Open(dataFilePath, "READ");
	TTree *tree = (TTree*)(file->Get("tree"));
    Float_t algMET;
    Int_t zbnentries = tree->GetEntries(); Int_t passrndmFlag;
    tree->SetBranchAddress(algName,&algMET);
    tree->SetBranchAddress("passrndm",&passrndmFlag);
    const TString title = algName + " right hand cumulative sum";
    TH1* regAlg = new TH1D(title, title, 400, 0.0, 500.0);
    for (Int_t i = 0  ; i < zbnentries ; i++)
    {
        tree->GetEntry(i);
        if ( passrndmFlag > 0.5)
        {
            regAlg->Fill(algMET);
        }
    }
	TH1* cumuReverse = regAlg->GetCumulative(kFALSE);
    cumuReverse->SetName(algName);
    TCanvas* cumulativeCanvas = new TCanvas(title,title);
    cumuReverse->Draw();
    cumulativeCanvas->SetLogy();
    cumuReverse->GetXaxis()->SetTitle("MEt [GeV]");
    cumuReverse->GetYaxis()->SetTitle("No. Events");
    const TString pathName = "./TEfficienciesPics/"+algName +"cumusum.jpg";

    cumulativeCanvas->Print(pathName);

}
