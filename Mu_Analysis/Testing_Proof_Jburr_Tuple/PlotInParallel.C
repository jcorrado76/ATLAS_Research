#define PlotInParallel_cxx
#include "PlotInParallel.h"
#include <TStyle.h>

void PlotInParallel::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
}

void PlotInParallel::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();
}

Bool_t PlotInParallel::Process(Long64_t entry)
{

   fReader.SetEntry(entry);

   return kTRUE;
}

void PlotInParallel::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void PlotInParallel::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

}
