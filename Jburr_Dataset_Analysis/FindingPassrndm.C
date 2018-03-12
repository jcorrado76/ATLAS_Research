#define FindingPassrndm_cxx

#include "FindingPassrndm.h"
#include <TH2.h>
#include <TStyle.h>
#include <TH1F.h>

void FindingPassrndm::Begin(TTree * /*tree*/)
{

   TString option = GetOption();
   fHistogram  = new TH1F("burr_hist" , "Jburr Hist" , 200 , 0.0 , 200.0);
   fOutput->Add(fHistogram);
}

void FindingPassrndm::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();

}

Bool_t FindingPassrndm::Process(Long64_t entry)
{
   fReader.SetEntry(entry);
       
    if ( *RunNumber < 311481 && *RunNumber > 307195){
    fHistogram->Fill(*HLT_noalg_zb_L1ZB_passed);
    }

   return kTRUE;
}

void FindingPassrndm::SlaveTerminate()
{

}

void FindingPassrndm::Terminate()
{

}
