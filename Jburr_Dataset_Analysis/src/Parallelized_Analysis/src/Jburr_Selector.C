#define Jburr_Selector_cxx

#include "Jburr_Selector.h"
#include <TH2.h>
#include <TStyle.h>

void Jburr_Selector::Begin(TTree * /*tree*/)
{

   histo1 = new TH1F("histo1","Jburrhist", 200, 300000,310000 );
   fOutput->Add(histo1);
   TString option = GetOption();
}

void Jburr_Selector::SlaveBegin(TTree * /*tree*/)
{

   TString option = GetOption();

}

Bool_t Jburr_Selector::Process(Long64_t entry)
{

   fReader.SetEntry(entry);
   histo1->Fill(*RunNumber);

   return kTRUE;
}

void Jburr_Selector::SlaveTerminate()
{

}

void Jburr_Selector::Terminate()
{

}
