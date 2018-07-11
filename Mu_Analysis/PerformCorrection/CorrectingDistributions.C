#define CorrectingDistributions_cxx


#include "CorrectingDistributions.h"
#include <TH2.h>
#include <TStyle.h>

void CorrectingDistributions::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
}

void CorrectingDistributions::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();

}

Bool_t CorrectingDistributions::Process(Long64_t entry)
{
   fReader.SetEntry(entry);

   return kTRUE;
}

void CorrectingDistributions::SlaveTerminate()
{
}

void CorrectingDistributions::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

}
