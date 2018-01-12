#define Bisection_Selector_cxx

#include "Bisection_Selector.h"
#include <TH2.h>
#include <TStyle.h>

void Bisection_Selector::Begin(TTree * /*tree*/)
{

   TString option = GetOption();
}

void Bisection_Selector::SlaveBegin(TTree * /*tree*/)
{

}

Bool_t Bisection_Selector::Process(Long64_t entry)
{

   fReader.SetEntry(entry);

   return kTRUE;
}

void Bisection_Selector::SlaveTerminate()
{

}

void Bisection_Selector::Terminate()
{

}
