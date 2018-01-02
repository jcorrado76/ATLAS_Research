#define Compute_Trigger_Rate_TSelector_cxx

#include "Compute_Trigger_Rate_TSelector.h"

void Compute_Trigger_Rate_TSelector::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
}

void Compute_Trigger_Rate_TSelector::SlaveBegin(TTree * /*tree*/)
{

    MetL1Hist = new TH1F("h1","Process 2 Histogram", 1200, 0.,300.);
    RandomHist = new TH1F("h2","Process 1 Histogram", 1200, 0.,300.);
    fOutput->Add( MetL1Hist );
    fOutput->Add( RandomHist );
   TString option = GetOption();
}


Bool_t Compute_Trigger_Rate_TSelector::Process(Long64_t entry)
{
   fReader.SetEntry(entry);

    if ( *passrndm > 0.5 )
    {
        RandomHist->Fill( *metl1 );

        if ( *metl1 > 50.0 )
        {
            MetL1Hist->Fill( *metl1 );
        }
    }

   return kTRUE;
}

void Compute_Trigger_Rate_TSelector::SlaveTerminate()
{
}

void Compute_Trigger_Rate_TSelector::Terminate()
{
    std::cout << "Number of random (process 1) entries: " << RandomHist->GetEntries() << std::endl;
    std::cout << "Number of metl1 > 50.0 ( process 2 ) entries: " << MetL1Hist->GetEntries() << std::endl;
    std::cout << "Trigger rate = ( numb kept process 1 ) / ( numb kept process 2 ): " << ((MetL1Hist->GetEntries())/(RandomHist->GetEntries())) << std::endl;
}
