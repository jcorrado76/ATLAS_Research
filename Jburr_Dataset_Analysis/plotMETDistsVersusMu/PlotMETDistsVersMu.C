#define PlotMETDistsVersMu_cxx


#include "PlotMETDistsVersMu.h"

void PlotMETDistsVersMu::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
    Int_t nbins = 1000;
    Float_t gevLow = 0.0;
    Float_t gevHigh = 100.0;
    metcellmu0thru10 = new TH1F("cellmu0thru10","MET Cell Histogram for actint between 0 and 10", nbins , gevLow , gevHigh );
    metcellmu10thru20 = new TH1F("cellmu10thru20","MET Cell Histogram for actint between 10 and 20", nbins , gevLow , gevHigh );
    metcellmu20thru30 = new TH1F("cellmu20thru30","MET Cell Histogram for actint between 20 and 30", nbins , gevLow , gevHigh );
    metcellmu30thru40 = new TH1F("cellmu30thru40","MET Cell Histogram for actint between 30 and 40", nbins , gevLow , gevHigh );
    metcellmu40thru50 = new TH1F("cellmu40thru50","MET Cell Histogram for actint between 40 and 50", nbins , gevLow , gevHigh );
    metcellmu50thru60 = new TH1F("cellmu50thru60","MET Cell Histogram for actint between 50 and 60", nbins , gevLow , gevHigh );
    metcellmu60thru70 = new TH1F("cellmu60thru70","MET Cell Histogram for actint between 60 and 70", nbins , gevLow , gevHigh );
}

void PlotMETDistsVersMu::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();
}

Bool_t PlotMETDistsVersMu::Process(Long64_t entry)
{
   fReader.SetEntry(entry);

   if ( *InTimePileup > 0.0 && *InTimePileup < 10.0  ){
       metcellmu0thru10->Fill(*cell_met);
   }
   if ( *InTimePileup > 10.0 && *InTimePileup < 20.0  ){
       metcellmu10thru20->Fill(*cell_met);
   }
   if ( *InTimePileup > 20.0 && *InTimePileup < 30.0  ){
       metcellmu20thru30->Fill(*cell_met);
   }
   if ( *InTimePileup > 30.0 && *InTimePileup < 40.0  ){
       metcellmu30thru40->Fill(*cell_met);
   }
   if ( *InTimePileup > 40.0 && *InTimePileup < 50.0  ){
       metcellmu40thru50->Fill(*cell_met);
   }
   if ( *InTimePileup > 50.0 && *InTimePileup < 60.0  ){
       metcellmu50thru60->Fill(*cell_met);
   }
   if ( *InTimePileup > 60.0 && *InTimePileup < 70.0  ){
       metcellmu60thru70->Fill(*cell_met);
   }
   return kTRUE;
}

void PlotMETDistsVersMu::SlaveTerminate()
{
}

void PlotMETDistsVersMu::Terminate()
{
    TCanvas* mycanv = new TCanvas("cellMuSlices", "MET Cell Slices in Mu");
    THStack* muSlicesStack = new THStack("muStack","CELL MET Hists in Mu Slices");

    metcellmu0thru10->SetLineColor(1);
    metcellmu10thru20->SetLineColor(2);
    metcellmu20thru30->SetLineColor(3);
    metcellmu30thru40->SetLineColor(4);
    metcellmu40thru50->SetLineColor(12);
    metcellmu50thru60->SetLineColor(6);
    metcellmu60thru70->SetLineColor(9);

    // draw stacked hists, because i want y axis to adjust
    // better than Drawing "SAME" for stacking hists 
    muSlicesStack->Add(metcellmu0thru10);
    muSlicesStack->Add(metcellmu10thru20);
    muSlicesStack->Add(metcellmu20thru30);
    muSlicesStack->Add(metcellmu30thru40);
    muSlicesStack->Add(metcellmu40thru50);
    muSlicesStack->Add(metcellmu50thru60);
    muSlicesStack->Add(metcellmu60thru70);

    muSlicesStack->Draw();
    
    mycanv->SetTitle("Cell Slices in Mu");
    gPad->SetLogy();
    TLegend* legend = new TLegend();
    legend->AddEntry(metcellmu0thru10);
    legend->AddEntry(metcellmu10thru20);
    legend->AddEntry(metcellmu20thru30);
    legend->AddEntry(metcellmu30thru40);
    legend->AddEntry(metcellmu40thru50);
    legend->AddEntry(metcellmu50thru60);
    legend->AddEntry(metcellmu60thru70);
    legend->Draw("SAME");
    gStyle->SetOptStat(0);
}

