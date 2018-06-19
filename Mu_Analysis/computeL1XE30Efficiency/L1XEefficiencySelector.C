#define L1XEefficiencySelector_cxx
#include "L1XEefficiencySelector.h"

void L1XEefficiencySelector::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
    MET_Algmu0thru10Efficiency = new TEfficiency("metmu0thru10Efficiency","MET Alg Efficiency for actint between 0 and 10", nbins , gevLow , gevHigh );
    MET_Algmu10thru20Efficiency = new TEfficiency("metmu10thru20Efficiency","MET Alg Efficiency for actint between 10 and 20", nbins , gevLow , gevHigh );
    MET_Algmu20thru30Efficiency = new TEfficiency("metmu20thru30Efficiency","MET Alg Efficiency for actint between 20 and 30", nbins , gevLow , gevHigh );
    MET_Algmu30thru40Efficiency = new TEfficiency("metmu30thru40Efficiency","MET Alg Efficiency for actint between 30 and 40", nbins , gevLow , gevHigh );
    MET_Algmu40thru50Efficiency = new TEfficiency("metmu40thru50Efficiency","MET Alg Efficiency for actint between 40 and 50", nbins , gevLow , gevHigh );
    MET_Algmu50thru60Efficiency = new TEfficiency("metmu50thru60Efficiency","MET Alg Efficiency for actint between 50 and 60", nbins , gevLow , gevHigh );
    MET_Algmu60thru70Efficiency = new TEfficiency("metmu60thru70Efficiency","MET Alg Efficiency for actint between 60 and 70", nbins , gevLow , gevHigh );
}

void L1XEefficiencySelector::SlaveBegin(TTree * /*tree*/)// {{{
{
   TString option = GetOption();
}// }}}

Bool_t L1XEefficiencySelector::Process(Long64_t entry)
{
   fReader.SetEntry(entry);
   if ( isGoodRun() ){
       if ( *InTimePileup > 0.0 && *InTimePileup < 10.0  ){
           MET_Algmu0thru10Efficiency->Fill(*L1_MET > XE, *cell_met);
       }
       if ( *InTimePileup > 10.0 && *InTimePileup < 20.0  ){
           MET_Algmu10thru20Efficiency->Fill(*L1_MET > XE, *cell_met);
       }
       if ( *InTimePileup > 20.0 && *InTimePileup < 30.0  ){
           MET_Algmu20thru30Efficiency->Fill(*L1_MET > XE, *cell_met);
       }
       if ( *InTimePileup > 30.0 && *InTimePileup < 40.0  ){
           MET_Algmu30thru40Efficiency->Fill(*L1_MET > XE, *cell_met);
       }
       if ( *InTimePileup > 40.0 && *InTimePileup < 50.0  ){
           MET_Algmu40thru50Efficiency->Fill(*L1_MET > XE, *cell_met);
       }
       if ( *InTimePileup > 50.0 && *InTimePileup < 60.0  ){
           MET_Algmu50thru60Efficiency->Fill(*L1_MET > XE, *cell_met);
       }
       if ( *InTimePileup > 60.0 && *InTimePileup < 70.0  ){
           MET_Algmu60thru70Efficiency->Fill(*L1_MET > XE, *cell_met);
       }
   }

   return kTRUE;
}

void L1XEefficiencySelector::SlaveTerminate()
{
}

void L1XEefficiencySelector::Terminate() // Plotting {{{
{
    TCanvas* mycanv = new TCanvas("metMuSlices", "MET Slices in Mu");

    MET_Algmu0thru10Efficiency->SetLineColor(1);
    MET_Algmu10thru20Efficiency->SetLineColor(2);
    MET_Algmu20thru30Efficiency->SetLineColor(3);
    MET_Algmu30thru40Efficiency->SetLineColor(4);
    MET_Algmu40thru50Efficiency->SetLineColor(12);
    MET_Algmu50thru60Efficiency->SetLineColor(6);
    MET_Algmu60thru70Efficiency->SetLineColor(9);

    MET_Algmu0thru10Efficiency->SetTitle(  title + ";" + xaxis + ";" +  yaxis  );

    MET_Algmu0thru10Efficiency->Draw();
    MET_Algmu10thru20Efficiency->Draw("SAME");
    MET_Algmu20thru30Efficiency->Draw("SAME");
    MET_Algmu30thru40Efficiency->Draw("SAME");
    MET_Algmu40thru50Efficiency->Draw("SAME");
    MET_Algmu50thru60Efficiency->Draw("SAME");
    MET_Algmu60thru70Efficiency->Draw("SAME");
    
    mycanv->SetTitle("MET Slices in Mu");
    gPad->SetLogy();
    TLegend* legend = new TLegend();
    legend->AddEntry(MET_Algmu0thru10Efficiency);
    legend->AddEntry(MET_Algmu10thru20Efficiency);
    legend->AddEntry(MET_Algmu20thru30Efficiency);
    legend->AddEntry(MET_Algmu30thru40Efficiency);
    legend->AddEntry(MET_Algmu40thru50Efficiency);
    legend->AddEntry(MET_Algmu50thru60Efficiency);
    legend->AddEntry(MET_Algmu60thru70Efficiency);
    legend->Draw("SAME");
    gStyle->SetOptStat(0);
} //}}}

void L1XEefficiencySelector::Init(TTree *tree)
{
   fReader.SetTree(tree);
}

Bool_t L1XEefficiencySelector::Notify() // {{{
{
   return kTRUE;
} // }}}

Bool_t PlotMETDistsVersMu::isGoodRun(){ // {{{
    return (*RunNumber != 33023 && *RunNumber != 331975 && *RunNumber != 334487);
} // }}}

Bool_t PlotMETDistsVersMu::passedL1ZB(){ // {{{ 
    return (*HLT_noalg_zb_L1ZB_passed);
} // }}}

Bool_t PlotMETDistsVersMu::isPassnoAlgXE30(){ // {{{
    return (*HLT_noalg_L1XE30_passed);
} // }}}

