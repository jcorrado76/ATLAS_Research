#define L1XEefficiencySelector_cxx
#include "L1XEefficiencySelector.h"

void L1XEefficiencySelector::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
    Int_t nbins = 1000;
    Float_t gevLow = 0.0;
    Float_t gevHigh = 100.0;
    metcellmu0thru10Efficiency = new TEfficiency("cellmu0thru10Efficiency","MET Cell Efficiency for actint between 0 and 10", nbins , gevLow , gevHigh );
    metcellmu10thru20Efficiency = new TEfficiency("cellmu10thru20Efficiency","MET Cell Efficiency for actint between 10 and 20", nbins , gevLow , gevHigh );
    metcellmu20thru30Efficiency = new TEfficiency("cellmu20thru30Efficiency","MET Cell Efficiency for actint between 20 and 30", nbins , gevLow , gevHigh );
    metcellmu30thru40Efficiency = new TEfficiency("cellmu30thru40Efficiency","MET Cell Efficiency for actint between 30 and 40", nbins , gevLow , gevHigh );
    metcellmu40thru50Efficiency = new TEfficiency("cellmu40thru50Efficiency","MET Cell Efficiency for actint between 40 and 50", nbins , gevLow , gevHigh );
    metcellmu50thru60Efficiency = new TEfficiency("cellmu50thru60Efficiency","MET Cell Efficiency for actint between 50 and 60", nbins , gevLow , gevHigh );
    metcellmu60thru70Efficiency = new TEfficiency("cellmu60thru70Efficiency","MET Cell Efficiency for actint between 60 and 70", nbins , gevLow , gevHigh );
}

void L1XEefficiencySelector::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();

}

Bool_t L1XEefficiencySelector::Process(Long64_t entry)
{
   fReader.SetEntry(entry);
   if (*RunNumber != 33023 && *RunNumber != 331975 && *RunNumber != 334487 ){
       if ( *InTimePileup > 0.0 && *InTimePileup < 10.0  ){
           metcellmu0thru10Efficiency->Fill(*cell_met);
       }
       if ( *InTimePileup > 10.0 && *InTimePileup < 20.0  ){
           metcellmu10thru20Efficiency->Fill(*cell_met);
       }
       if ( *InTimePileup > 20.0 && *InTimePileup < 30.0  ){
           metcellmu20thru30Efficiency->Fill(*cell_met);
       }
       if ( *InTimePileup > 30.0 && *InTimePileup < 40.0  ){
           metcellmu30thru40Efficiency->Fill(*cell_met);
       }
       if ( *InTimePileup > 40.0 && *InTimePileup < 50.0  ){
           metcellmu40thru50Efficiency->Fill(*cell_met);
       }
       if ( *InTimePileup > 50.0 && *InTimePileup < 60.0  ){
           metcellmu50thru60Efficiency->Fill(*cell_met);
       }
       if ( *InTimePileup > 60.0 && *InTimePileup < 70.0  ){
           metcellmu60thru70Efficiency->Fill(*cell_met);
       }
   }

   return kTRUE;
}

void L1XEefficiencySelector::SlaveTerminate()
{
}

void L1XEefficiencySelector::Terminate()
{
    TCanvas* mycanv = new TCanvas("cellMuSlices", "MET Cell Slices in Mu");
    THStack* muSlicesStack = new THStack("muStack","CELL MET Hists in Mu Slices without runs 33023, 331975, and 334487");

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
