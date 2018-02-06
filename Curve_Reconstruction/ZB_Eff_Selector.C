#define ZB_Eff_Selector_cxx

#include "ZB_Eff_Selector.h"

void ZB_Eff_Selector::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
}

void ZB_Eff_Selector::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();
   histo1 = new TH1F( "histo1", "Unbiased Curves" , 400 , 0.0 , 300.0 );
   histo2 = new TH1F( "histo2", "Unbiased Curves" , 400 , 0.0 , 300.0 );
   XE_Ratio = new TEfficiency( "teff" , "Efficiency of ZB to ZB XE 20" , 400 , 0.0 , 300.0 );
   fOutput->Add( histo1 );
   fOutput->Add( histo2 );
   fOutput->Add( XE_Ratio );
}

Bool_t ZB_Eff_Selector::Process(Long64_t entry)
{
   fReader.SetEntry(entry);
   if (*passrndm > 0.5 ){
       histo1->Fill( *metcell );
       histo2->Fill( *metcell );
       XE_Ratio->Fill( *metl1 > 20.0 , *metcell );
   }
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
    histo1->SetLineColor(kBlue);
    histo2->SetLineColor(kTeal);
    XE_Ratio->SetLineColor(kRed);
    histo1->Draw();
    histo2->Draw();
    XE_Ratio->Draw();
    TLegend *legend = new TLegend( 0.57, 0.12 , 0.9, 0.4 , "" , "NDC");
    legend->AddEntry( histo1 , "metcell plot");
    legend->AddEntry( histo2 , "metcell plot");
    legend->AddEntry( XE_Ratio , "Efficiency of ZB to ZBXE20");
    legend->Draw();
    Histo_Canv->Draw();
}
