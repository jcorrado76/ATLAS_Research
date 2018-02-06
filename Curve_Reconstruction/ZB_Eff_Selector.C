#define ZB_Eff_Selector_cxx

#include "ZB_Eff_Selector.h"

void ZB_Eff_Selector::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
}

void ZB_Eff_Selector::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();
   histo = new TH1F( "histo", "Unbiased Curves" , 400 , 0.0 , 300.0 );
   fOutput->Add( histo );
}

Bool_t ZB_Eff_Selector::Process(Long64_t entry)
{
   fReader.SetEntry(entry);
   histo->Fill( *metcell );
   return kTRUE;
}

void ZB_Eff_Selector::SlaveTerminate()
{
}

void ZB_Eff_Selector::Terminate()
{
    TCanvas* Histo_Canv = new TCanvas( "mycanv" , "Random Trigger Curves" );
    TString alg_name = "metcell";
    Histo_Canv->RangeAxis( 0.0 , 0.0 , 500.0 , 1.0 );
    histo->Draw();
    TLegend *legend = new TLegend( 0.57, 0.12 , 0.9, 0.4 , "" , "NDC");
    legend->AddEntry( histo , alg_name );
    legend->Draw();
    Histo_Canv->Draw();
}
