#define JburrDuplicateCheck_cxx


#include "JburrDuplicateCheck.h"
#include <TH2.h>
#include <TStyle.h>

void JburrDuplicateCheck::Begin(TTree * /*tree*/)
{

   TString option = GetOption();
}

void JburrDuplicateCheck::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();

}

Bool_t JburrDuplicateCheck::Process(Long64_t entry)
{

   fReader.SetEntry(entry);

   return kTRUE;
}

void JburrDuplicateCheck::SlaveTerminate()
{

}

void JburrDuplicateCheck::Terminate()
{

}
