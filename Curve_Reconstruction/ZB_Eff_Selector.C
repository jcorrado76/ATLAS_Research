#define ZB_Eff_Selector_cxx

#include "ZB_Eff_Selector.h"

void ZB_Eff_Selector::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
}

void ZB_Eff_Selector::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();
   histo1 = new TH1F( "histo1", "Random Trigger" , 400 , 0.0 , 100.0 );
   histo2 = new TH1F( "histo2", "Random Trigger XE20" , 400 , 0.0 , 100.0 );
   XE_Ratio = new TEfficiency( "teff" , "Efficiency" , 400 , 0.0 , 100.0 );
   fOutput->Add( histo1 );
   fOutput->Add( histo2 );
   fOutput->Add( XE_Ratio );
}

Bool_t ZB_Eff_Selector::Process(Long64_t entry)
{
   fReader.SetEntry(entry);
   if (*passrndm > 0.5 ){
       histo1->Fill( *metcell );
       XE_Ratio->Fill( *metl1 > 20.0 , *metcell );
       if ( *metl1>20.0 ){
           histo2->Fill( *metcell );
       }
   }
   return kTRUE;
}

void ZB_Eff_Selector::SlaveTerminate()
{
}

void ZB_Eff_Selector::Terminate()
{
    TCanvas* random_canv = new TCanvas( "mycanv" , "Random Trigger Curves" );
    gStyle->SetOptStat(kFALSE);
    TString alg_name = "metcell";
    random_canv->RangeAxis( 1.0 , 1.0 , 500.0 , 1.0 );
    histo1->SetLineColor(kBlue);
    histo2->SetLineColor(kMagenta);
    histo2->SetAxisRange(1.0,5.0e5,"Y");
    XE_Ratio->SetLineColor(kRed);
    random_canv->SetLogy();
    histo1->Draw();
    histo2->Draw("SAME");
    //XE_Ratio->Draw();
    TLegend *legend = new TLegend( 0.57, 0.12 , 0.9, 0.4 , "" , "NDC");
    legend->AddEntry( histo1 , "Metcell Random");
    legend->AddEntry( histo2 , "Metcell Random XE20");
    legend->AddEntry( XE_Ratio , "Efficiency of ZBXE20 to ZB" );
    legend->Draw();
    random_canv->Draw();
}
