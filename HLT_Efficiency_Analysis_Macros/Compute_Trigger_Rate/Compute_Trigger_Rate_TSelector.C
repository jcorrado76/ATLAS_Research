/*
 * This macro computes what the target trigger rate should be using a cut of L1XE50 and CELL XE 100 on the
 * zerobias data to simulate triggers currently being used at ATLAS
 */
#include "Compute_Trigger_Rate_TSelector.h"
void Compute_Trigger_Rate_TSelector::Begin(TTree*){TString option = GetOption();}
void Compute_Trigger_Rate_TSelector::SlaveBegin(TTree*)
{
    Float_t metLo = 0.0;
    Float_t metHi = 300.0;
    Int_t nbins = 1200;
    MetL1Hist = new TH1F("l1hist","L1XE50 Trigger Rate Histogram", nbins , metLo , metHi );
    RandomHist = new TH1F("zerobiashist","Zerobias Histogram", nbins , metLo , metHi );
    fOutput->Add( MetL1Hist );
    fOutput->Add( RandomHist );
    TString option = GetOption();
}
Bool_t Compute_Trigger_Rate_TSelector::Process(Long64_t entry)
{
   fReader.SetEntry(entry);
    if ( *passrndm > 0.5 )
    {
        numRndm++;
        if ( *metl1 > 50.0 )
        {
            numPassL1++;
        }
    }
   return kTRUE;
}
void Compute_Trigger_Rate_TSelector::SlaveTerminate(){}
void Compute_Trigger_Rate_TSelector::Terminate()
{
    std::cout << "Number of ZeroBias events: " << numRndm << std::endl;
    std::cout << "Number of events that pass metl1 > 50.0: " << numPassL1 << std::endl;
    std::cout << "Trigger rate = Number of events that pass L1>50 / Number Zerobias events: " 
        << numPassL1 / numRndm << std::endl;
}
