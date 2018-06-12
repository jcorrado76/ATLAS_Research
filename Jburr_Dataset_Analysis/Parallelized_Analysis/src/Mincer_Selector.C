#define Mincer_Selector_cxx

#include "Mincer_Selector.h"
#include <TH2.h>
#include <TStyle.h>

void Mincer_Selector::Begin(TTree * /*tree*/)
{

   TString option = GetOption();
   histo1 = new TH1F("mincerHist","Mincer Histogram",200,0.0,200.0);
   fOutput->Add(histo1);
}

void Mincer_Selector::SlaveBegin(TTree * /*tree*/)
{

   TString option = GetOption();

}

Bool_t Mincer_Selector::Process(Long64_t entry)
{

   fReader.SetEntry(entry);

   histo1->Fill(*metcell);

   return kTRUE;
}

void Mincer_Selector::SlaveTerminate()
{
}

void Mincer_Selector::Terminate()
{

}
