#define PlotMETDistsVersMu_cxx


#include "PlotMETDistsVersMu.h"
#include <TH2.h>
#include <TStyle.h>

void PlotMETDistsVersMu::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
    Int_t nbins = 1000;
    metcellmu0thru10 = new TH1F("cellmu0thru10","MET Cell Histogram for actint between 0 and 10", nbins , 0.0, 10.0 )
    metcellmu10thru20 = new TH1F("cellmu10thru20","MET Cell Histogram for actint between 10 and 20", nbins , 10.0, 20.0 )
    metcellmu20thru30 = new TH1F("cellmu20thru30","MET Cell Histogram for actint between 20 and 30", nbins , 20.0, 30.0 )
    metcellmu30thru40 = new TH1F("cellmu30thru40","MET Cell Histogram for actint between 30 and 40", nbins , 30.0, 40.0 )
    metcellmu40thru50 = new TH1F("cellmu40thru50","MET Cell Histogram for actint between 40 and 50", nbins , 40.0, 50.0 )
    metcellmu50thru60 = new TH1F("cellmu50thru60","MET Cell Histogram for actint between 50 and 60", nbins , 50.0, 60.0 )
    metcellmu60thru70 = new TH1F("cellmu60thru70","MET Cell Histogram for actint between 60 and 70", nbins , 60.0, 70.0 )
}

void PlotMETDistsVersMu::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();
}

Bool_t PlotMETDistsVersMu::Process(Long64_t entry)
{
   fReader.SetEntry(entry);
   return kTRUE;
}

void PlotMETDistsVersMu::SlaveTerminate()
{
}

void PlotMETDistsVersMu::Terminate()
{
}
