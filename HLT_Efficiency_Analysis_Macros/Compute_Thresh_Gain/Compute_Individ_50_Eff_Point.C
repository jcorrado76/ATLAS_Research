#define tree_cxx
#include "tree.h"
#include <TH2.h>
#include <TStyle.h>

void tree::Begin(TTree * /*tree*/)
{
  userInfo* parameters =
     dynamic_cast<userInfo*>(fInput->FindObject("parameters"));

   TString option = GetOption();
}

void tree::SlaveBegin(TTree * /*tree*/)
{

   TString option = GetOption();

}

Bool_t tree::Process(Long64_t entry)
{
   fReader.SetEntry(entry);

   return kTRUE;
}

void tree::SlaveTerminate()
{

}

void tree::Terminate()
{

}
