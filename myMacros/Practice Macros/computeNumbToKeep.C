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

Int_t computeNumbToKeep(const TString& thresholdFileName = "PhysicsMain.All.noalgXEtriggers.2016.f731f758._m1659m1710.48Runs.root")
{
    /* given a new zerobias file, this macro computes what fraction the triggers currently in use at CERN would keep
    must pass metl1 > 50.0, cell > 100.0, and all  passnoalg_i > 0.5
    PhysicsMain.All.noalgXEtriggers.2016.f731f758._m1659m1710.48Runs.root should yield 5762
    */


    TString threshFilePath = "../myData/"+ thresholdFileName;
    TFile * threshFileHandle = TFile::Open(threshFilePath, "READ");
    TTree* thresholdTree = (TTree*)threshFileHandle->Get("tree");
    Int_t NentriesNoCuts = thresholdTree->GetEntries();

    Float_t metl1, metcell;
    Int_t passnoalgL1XE10 , passnoalgL1XE30, passnoalgL1XE40, passnoalgL1XE45;
    Float_t actint;
    Int_t actintCut = 35.0;

    thresholdTree->SetBranchAddress("metl1",&metl1);
    thresholdTree->SetBranchAddress("metcell", &metcell);
    thresholdTree->SetBranchAddress("passnoalgL1XE10",&passnoalgL1XE10);
    thresholdTree->SetBranchAddress("passnoalgL1XE30",&passnoalgL1XE30);
    thresholdTree->SetBranchAddress("passnoalgL1XE40",&passnoalgL1XE40);
    thresholdTree->SetBranchAddress("passnoalgL1XE45",&passnoalgL1XE45);
    thresholdTree->SetBranchAddress("actint",&actint);

    /*
    To compute number of events that we know we can trigger on
    this is what CERN currently uses. The fraction needs to stay the same; need to still
    use 1/200, but the number of events to keep changes based on the new actint cut, because you need to
    multiply fraction to keep (0.0059) by some new numbToKeep
    */

    Int_t Process1NoActintEventsKept = 0 ;
    Int_t Process2NoActintEventsKept = 0 ;
    Int_t Process1WithActintCutEventsKept = 0;
    for (Int_t i = 0 ; i < NentriesNoCuts ; i++)
    {
        thresholdTree->GetEntry(i);
        if ( metl1 > 50.0 &&
           ( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 ||
            passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5  ) )
        {
            Process1NoActintEventsKept++;
        }
        if ( metl1 > 50.0 && metcell > 100.0  &&
           ( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 ||
            passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5  ) )
        {
            Process2NoActintEventsKept++;
        }
        if ( (metl1 > 50.0) && (actint > actintCut)  &&
           ( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 ||
            passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5  ) )
        {
            Process1WithActintCutEventsKept++;
        }
    }



    //we want to be able to look at how the threshold on cell needed to keep same fraction
    //varies as we change actint cut
    //this is not the numb to keep. this is the numb to keep, divided by the fraction to keep

    Float_t noActintProcess1Frac = (Float_t) Process1NoActintEventsKept / (Float_t) NentriesNoCuts;
    Float_t noActintProcess2Frac = (Float_t) Process2NoActintEventsKept / (Float_t) Process1NoActintEventsKept;
    Float_t ActintCutProcess1Frac = (Float_t) Process1WithActintCutEventsKept / (Float_t) NentriesNoCuts;

    Int_t passnoalgEventsToKeep = Process1WithActintCutEventsKept * noActintProcess2Frac;

    std::cout << "Passnoalg Nentries: " << NentriesNoCuts << std::endl;
    std::cout << "\n" << std::endl;

    std::cout << "Number of events kept with l1>50.0: " << Process1NoActintEventsKept << std::endl;
    std::cout << "Process 1 Fraction NoActint: " << noActintProcess1Frac << std::endl;
    std::cout << "\n" << std::endl;

    std::cout << "Number of events kept with l1>50.0 and cell>100.0: " << Process2NoActintEventsKept << std::endl;
    std::cout << "Process 2 Fraction NoActint: " << noActintProcess2Frac << std::endl;
    std::cout << "\n" << std::endl;

    std::cout << "Number of events kept with l1>50.0 and actint>35.0: " << Process1WithActintCutEventsKept << std::endl;
    std::cout << "Process 1 Fraction WithActint: " << ActintCutProcess1Frac << std::endl;
    std::cout << "\n" << std::endl;

    std::cout << "Number of events to keep using process2 frac with no actint cut on the number of process 1 events kept after using actint cut "
    << passnoalgEventsToKeep << std::endl;

    return(1);
}
