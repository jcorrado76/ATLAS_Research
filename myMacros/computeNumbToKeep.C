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

Int_t computeNumbToKeep(const TString& zeroBiasFileName = "PhysicsMain.All.noalgXEtriggers.2016.f731f758._m1659m1710.48Runs.root")
{
    /* given a new zerobias file, this macro computes what fraction the triggers currently in use at CERN would keep */
    TString zerobiasFilePath = "../myData/"+ zerobiasFileName;
    TFile * zeroBiasFile = TFile::Open(zerobiasFilePath, "READ");
    TTree* zeroBiasTree = (TTree*)zeroBiasFile->Get("tree");
    Int_t zerobiasNentries = zeroBiasTree->GetEntries();

    Float_t metl1, metcell;
    Int_t passnoalgL1XE10 , passnoalgL1XE30, passnoalgL1XE40, passnoalgL1XE45;

    zeroBiasTree->SetBranchAddress("metl1",&metl1);
    zeroBiasTree->SetBranchAddress("metcell", &metcell);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE10",&passnoalgL1XE10);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE30",&passnoalgL1XE30);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE40",&passnoalgL1XE40);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE45",&passnoalgL1XE45);


    Int_t numbToKeep = 0 ;
    for (Int_t i = 0 ; i < zerobiasNentries ; i++)
    {
        zeroBiasTree->GetEntry(i);
        if ( metl1 > 50.0 && metcell > 100.0  &&
           ( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 ||
            passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5  ) )
        {
            numbToKeep++;
        }
    }

    std::cout << "Number of events to keep: " << numbToKeep << std::endl;


    return(numbToKeep);
}
