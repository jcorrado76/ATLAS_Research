#include "TMath.h"
#include "TH1.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TEfficiency.h"
#include "TLegend.h"
#include <iostream>
#include <fstream>
#include "TROOT.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TF1.h"

Int_t WAnalysis()
{
    //Plots the efficiency curves for (metcell, metmht) , (metcell, mettopocl) , (metcell , mettopoclps) , (metmht, mettopoclpuc)
    //using the W cut, versus not using the W cut

    TString zeroBiasFileName = "PhysicsMain.All.noalgXEtriggers.2016.f731f758._m1659m1710.48Runs.root";
    TString signalFileName = "PhysicsMain2016.Muons.noalgL1XE45R3073065R311481Runs9B.root";

    TFile* zeroBiasFileHandle = TFile::Open( "../myData/" + zeroBiasFileName );
    TTree* zeroBiasTree = (TTree*) zeroBiasFileHandle->Get("tree");

    Int_t zbNentries = zeroBiasTree->GetEntries();
    Int_t passnoalgL1XE10,passnoalgL1XE30,passnoalgL1XE40,passnoalgL1XE45;

    Float_t metl1;
    Float_t metcell;
    Float_t metmht;
    Float_t mettopocl,mettopoclps,mettopoclpuc;

    zeroBiasTree->SetBranchAddress("metl1",&metl1);
    zeroBiasTree->SetBranchAddress("metcell",&metcell);
    zeroBiasTree->SetBranchAddress("metmht",&metmht);
    zeroBiasTree->SetBranchAddress("mettopocl",&mettopocl);
    zeroBiasTree->SetBranchAddress("mettopoclps",&mettopoclps);
    zeroBiasTree->SetBranchAddress("mettopoclpuc",&mettopoclpuc);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE10",&passnoalgL1XE10);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE30",&passnoalgL1XE30);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE40",&passnoalgL1XE40);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE45",&passnoalgL1XE45);

    TH1F *zbCellHist = new TH1F("metcell", "metcell", nbins, metMin, metMax);
    TH1F *zbMhtHist = new TH1F("metmht", "metmht", nbins, metMin, metMax);
    TH1F *zbTopoclHist = new TH1F("mettopocl", "mettopocl", nbins, metMin, metMax);
    TH1F *zbTopoclpsHist = new TH1F("mettopoclps", "mettopoclps", nbins, metMin, metMax);
    TH1F *zbTopoclpucHist = new TH1F("mettopoclpuc", "mettopoclpuc", nbins, metMin, metMax);
}
