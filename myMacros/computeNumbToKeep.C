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
    /* given a new zerobias file, this macro computes what fraction the triggers currently in use at CERN would keep
    must pass metl1 > 50.0, cell > 100.0, and all  passnoalg_i > 0.5
    PhysicsMain.All.noalgXEtriggers.2016.f731f758._m1659m1710.48Runs.root should yield 5762
    */


    TString zerobiasFilePath = "../myData/"+ zeroBiasFileName;
    TFile * zeroBiasFile = TFile::Open(zerobiasFilePath, "READ");
    TTree* zeroBiasTree = (TTree*)zeroBiasFile->Get("tree");
    Int_t zerobiasNentries = zeroBiasTree->GetEntries();

    Float_t metl1, metcell;
    Int_t passnoalgL1XE10 , passnoalgL1XE30, passnoalgL1XE40, passnoalgL1XE45;
    Float_t actint;
    Int_t actintCut = 35.0;

    zeroBiasTree->SetBranchAddress("metl1",&metl1);
    zeroBiasTree->SetBranchAddress("metcell", &metcell);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE10",&passnoalgL1XE10);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE30",&passnoalgL1XE30);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE40",&passnoalgL1XE40);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE45",&passnoalgL1XE45);
    zeroBiasTree->SetBranchAddress("actint",&actint);

    /*
    To compute number of events that we know we can trigger on
    this is what CERN currently uses. The fraction needs to stay the same; need to still
    use 1/200, but the number of events to keep changes based on the new actint cut, because you need to
    multiply fraction to keep (0.0059) by some new numbToKeep
    */

    Int_t numEventsToKeep = 0 ;
    Int_t counter2 = 0;
    for (Int_t i = 0 ; i < zerobiasNentries ; i++)
    {
        zeroBiasTree->GetEntry(i);
        if ( metl1 > 50.0 && metcell > 100.0  &&
           ( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 ||
            passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5  ) )
        {
            numEventsToKeep++;
        }
        if ( (metl1 > 50.0) && (actint > actintCut)  &&
           ( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 ||
            passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5  ) )
        {
            counter2++;
        }
    }



    //we want to be able to look at how the threshold on cell needed to keep same fraction
    //varies as we change actint cut
    //this is not the numb to keep. this is the numb to keep, divided by the fraction to keep

    Float_t counter1Frac = (Float_t) numEventsToKeep / (Float_t) zerobiasNentries;
    Float_t counter2Frac = (Float_t) counter2 / (Float_t) zerobiasNentries;

    std::cout << "zb_Nentries: " << zerobiasNentries << std::endl;

    std::cout << "Number of events kept with passnoalg, l1, and cell > 100: " << numEventsToKeep << std::endl;
    std::cout << "Fraction of zb nentries: " << counter1Frac << std::endl;

    std::cout << "Number of events kept with passsnoalg, l1, and actint > 35: " << counter2 << std::endl;
    std::cout << "Fraction of zb nentries: " << counter2Frac << std::endl;


    return(1);
}
