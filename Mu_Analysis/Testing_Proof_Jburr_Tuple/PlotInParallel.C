#define PlotInParallel_cxx
#include "PlotInParallel.h"
#include <TStyle.h>

void PlotInParallel::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
   METHist = new TH1F("h1","MET Practice Hist");
}

void PlotInParallel::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();
}

Bool_t PlotInParallel::Process(Long64_t entry)
{
   fReader.SetEntry(entry);
   METHist->Fill(*cell.met);
   return kTRUE;
}

void PlotInParallel::SlaveTerminate()
{
}

void PlotInParallel::Terminate()
{
    METHist->Draw();
}
