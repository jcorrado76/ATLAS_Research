#define L1XEefficiencySelector_cxx
#include "L1XEefficiencySelector.h"

void L1XEefficiencySelector::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
}

void L1XEefficiencySelector::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();

}

Bool_t L1XEefficiencySelector::Process(Long64_t entry)
{
   fReader.SetEntry(entry);
   return kTRUE;
}

void L1XEefficiencySelector::SlaveTerminate()
{
}

void L1XEefficiencySelector::Terminate()
{
}
