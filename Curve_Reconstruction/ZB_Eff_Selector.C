#define ZB_Eff_Selector_cxx

#include "ZB_Eff_Selector.h"

void ZB_Eff_Selector::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
}

void ZB_Eff_Selector::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();
   Float_t metmax = 200.0;
   Float_t metmin = 0.0;
   Int_t histnbins = 400;
   Float_t eff_binwidth = 10.0;
   Int_t eff_nbins = (metmax - metmin) / eff_binwidth;
   histo1 = new TH1F( "histo1", "Random Trigger" , histnbins , metmin , metmax );
   histo2 = new TH1F( "histo2", "Random Trigger XE20" , histnbins, metmin , metmax );
   XE_Ratio = new TEfficiency( "teff" , "Efficiency" , eff_nbins, metmin , metmax );
   fOutput->Add( histo1 );
   fOutput->Add( histo2 );
   fOutput->Add( XE_Ratio );
}

Bool_t ZB_Eff_Selector::Process(Long64_t entry)
{
   fReader.SetEntry(entry);
   if (*passrndm > 0.5 ){
       histo1->Fill( *metmht );
       XE_Ratio->Fill( *metl1 > 20.0 , *metmht );
       if ( *metl1>20.0 ){
           histo2->Fill( *metmht );
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
    random_canv->Divide(2,1);
    random_canv->cd(1);
    gStyle->SetOptStat(kFALSE);
    TString alg_name = "metmht";
    random_canv->RangeAxis( 1.0 , 1.0 , 500.0 , 1.0 );
    histo1->SetLineColor(kBlue);
    histo2->SetLineColor(kMagenta);
    XE_Ratio->SetLineColor(kRed);
    histo2->SetAxisRange(1.0,5.0e5,"Y");
    gPad->SetLogy();
    histo1->Draw();
    histo2->Draw("SAME");

    random_canv->cd(2);
    XE_Ratio->Draw();
    
    
    TLegend *legend = new TLegend( 0.57, 0.12 , 0.9, 0.4 , "" , "NDC");
    legend->AddEntry( histo1 , "metmht Random");
    legend->AddEntry( histo2 , "metmht Random XE20");
    legend->AddEntry( XE_Ratio , "Efficiency of ZBXE20 to ZB" );
    random_canv->cd(1); //change back to pad 1 to put tlegend on lhs of diagram
    legend->Draw();
    random_canv->Draw();
}
