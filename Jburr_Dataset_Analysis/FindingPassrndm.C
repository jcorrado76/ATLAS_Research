#define FindingPassrndm_cxx

#include "FindingPassrndm.h"
#include <TH2.h>
#include <TStyle.h>

void FindingPassrndm::Begin(TTree * /*tree*/)
{

   TString option = GetOption();
}

void FindingPassrndm::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();

}

Bool_t FindingPassrndm::Process(Long64_t entry)
{

   fReader.SetEntry(entry);

   return kTRUE;
}

void FindingPassrndm::SlaveTerminate()
{

}

void FindingPassrndm::Terminate()
{

}
