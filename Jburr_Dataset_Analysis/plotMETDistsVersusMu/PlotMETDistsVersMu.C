#define PlotMETDistsVersMu_cxx


#include "PlotMETDistsVersMu.h"

void PlotMETDistsVersMu::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
    Int_t nbins = 1000;
    Float_t gevLow = 0.0;
    Float_t gevHigh = 300.0;
    MET_Datamu0thru10 = new TH1F("metmu0thru10","L1ZB Data for actint between 0 and 10", nbins , gevLow , gevHigh );
    MET_Datamu10thru20 = new TH1F("metmu10thru20","L1ZB Data for actint between 10 and 20", nbins , gevLow , gevHigh );
    MET_Datamu20thru30 = new TH1F("metmu20thru30","L1ZB Data for actint between 20 and 30", nbins , gevLow , gevHigh );
    MET_Datamu30thru40 = new TH1F("metmu30thru40","L1ZB Data for actint between 30 and 40", nbins , gevLow , gevHigh );
    MET_Datamu40thru50 = new TH1F("metmu40thru50","L1ZB Data for actint between 40 and 50", nbins , gevLow , gevHigh );
    MET_Datamu50thru60 = new TH1F("metmu50thru60","L1ZB Data for actint between 50 and 60", nbins , gevLow , gevHigh );
    MET_Datamu60thru70 = new TH1F("metmu60thru70","L1ZB Data for actint between 60 and 70", nbins , gevLow , gevHigh );
}

void PlotMETDistsVersMu::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();
}

Bool_t PlotMETDistsVersMu::Process(Long64_t entry)
{
   fReader.SetEntry(entry);


   if (*RunNumber != 33023 && *RunNumber != 331975 && *RunNumber != 334487 ){
       if ( *InTimePileup > 0.0 && *InTimePileup < 10.0  ){
           MET_Datamu0thru10->Fill(*MET_Data);
       }
       if ( *InTimePileup > 10.0 && *InTimePileup < 20.0  ){
           MET_Datamu10thru20->Fill(*MET_Data);
       }
       if ( *InTimePileup > 20.0 && *InTimePileup < 30.0  ){
           MET_Datamu20thru30->Fill(*MET_Data);
       }
       if ( *InTimePileup > 30.0 && *InTimePileup < 40.0  ){
           MET_Datamu30thru40->Fill(*MET_Data);
       }
       if ( *InTimePileup > 40.0 && *InTimePileup < 50.0  ){
           MET_Datamu40thru50->Fill(*MET_Data);
       }
       if ( *InTimePileup > 50.0 && *InTimePileup < 60.0  ){
           MET_Datamu50thru60->Fill(*MET_Data);
       }
       if ( *InTimePileup > 60.0 && *InTimePileup < 70.0  ){
           MET_Datamu60thru70->Fill(*MET_Data);
       }
   }
   return kTRUE;
}

void PlotMETDistsVersMu::SlaveTerminate()
{
}

void PlotMETDistsVersMu::Terminate()
{
    TCanvas* mycanv = new TCanvas("MET_AlgMuSlices", "MET Slices in Mu");
    THStack* muSlicesStack = new THStack("muStack","MET Hists in Mu Slices After Removing Runs 33023, 331975, and 334487");

    // color the histograms so we can see difference 
    MET_Datamu0thru10->SetLineColor(1);
    MET_Datamu10thru20->SetLineColor(2);
    MET_Datamu20thru30->SetLineColor(3);
    MET_Datamu30thru40->SetLineColor(4);
    MET_Datamu40thru50->SetLineColor(12);
    MET_Datamu50thru60->SetLineColor(6);
    MET_Datamu60thru70->SetLineColor(9);

    // normalize histograms to 1 so we can compare shapes 
    Int_t MET_Datamu0thru10Nentries = MET_Datamu0thru10->GetEntries();
    Int_t MET_Datamu10thru20Nentries = MET_Datamu10thru20->GetEntries();
    Int_t MET_Datamu20thru30Nentries = MET_Datamu20thru30->GetEntries();
    Int_t MET_Datamu30thru40Nentries = MET_Datamu30thru40->GetEntries();
    Int_t MET_Datamu40thru50Nentries = MET_Datamu40thru50->GetEntries();
    Int_t MET_Datamu50thru60Nentries = MET_Datamu50thru60->GetEntries();
    Int_t MET_Datamu60thru70Nentries = MET_Datamu60thru70->GetEntries();

    MET_Datamu0thru10->Scale( 1. / MET_Datamu0thru10Nentries );
    MET_Datamu10thru20->Scale( 1. / MET_Datamu10thru20Nentries );
    MET_Datamu20thru30->Scale( 1. / MET_Datamu20thru30Nentries );
    MET_Datamu30thru40->Scale( 1. / MET_Datamu30thru40Nentries );
    MET_Datamu40thru50->Scale( 1. / MET_Datamu40thru50Nentries );
    MET_Datamu50thru60->Scale( 1. / MET_Datamu50thru60Nentries );
    MET_Datamu60thru70->Scale( 1. / MET_Datamu60thru70Nentries );

    // draw stacked hists, because i want y axis to adjust
    // better than Drawing "SAME" for stacking hists 
    muSlicesStack->Add(MET_Datamu0thru10);
    muSlicesStack->Add(MET_Datamu10thru20);
    muSlicesStack->Add(MET_Datamu20thru30);
    muSlicesStack->Add(MET_Datamu30thru40);
    muSlicesStack->Add(MET_Datamu40thru50);
    muSlicesStack->Add(MET_Datamu50thru60);
    muSlicesStack->Add(MET_Datamu60thru70);

    muSlicesStack->Draw();
    
    mycanv->SetTitle("L1ZB Slices in Mu");
    gPad->SetLogy();
    TLegend* legend = new TLegend();
    legend->AddEntry(MET_Datamu0thru10);
    legend->AddEntry(MET_Datamu10thru20);
    legend->AddEntry(MET_Datamu20thru30);
    legend->AddEntry(MET_Datamu30thru40);
    legend->AddEntry(MET_Datamu40thru50);
    legend->AddEntry(MET_Datamu50thru60);
    legend->AddEntry(MET_Datamu60thru70);
    legend->Draw("SAME");
    gStyle->SetOptStat(0);
}

