#define ZB_Eff_Selector_cxx


#include "ZB_Eff_Selector.h"

void ZB_Eff_Selector::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
}

void ZB_Eff_Selector::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();
   histo1 = new TH1F( "histo1" , "ZeroBias Alone" , 400 , 0.0 , 100.0 );
   histo2 = new TH1F( "histo2" , "ZeroBias with XE" , 400 , 0.0 , 100.0 );

   XE_Ratio = new TEfficiency( "teff" , "Ratio of ZB with XE to ZB" , 400 , 0.0 , 100.0 );

   fOutput->Add( histo1 );
   fOutput->Add( histo2 );
   fOutput->Add( XE_Ratio );
}

Bool_t ZB_Eff_Selector::Process(Long64_t entry)
{

   fReader.SetEntry(entry);

    if ( *passrndm ){
       histo1->Fill( *metcell );
    }

    if ( *passrndm > 0.5 and *passnoalgL1XE30 > 0.5){
       histo2->Fill( *metcell );
    }

   XE_Ratio->Fill( *passnoalgL1XE30 > 0.5 , *metcell );  


   return kTRUE;
}

void ZB_Eff_Selector::SlaveTerminate()
{

}

void ZB_Eff_Selector::Terminate()
{
    TCanvas* Histo_Canv = new TCanvas( "mycanv" , "ZeroBias XE Efficiency Corrections" );
    TLegend *legend = new TLegend( 0.57, 0.12 , 0.9, 0.4 , "" , "NDC");
    Histo_Canv->RangeAxis( 0.0 , 0.0 , 500.0 , 1.0 );

    histo1->SetLineColor( kBlue );
    histo2->SetLineColor( kTeal );
    XE_Ratio->SetLineColor( kRed );

    histo1->Draw();
    histo2->Draw("SAME");
    XE_Ratio->Draw("SAME");
    legend->AddEntry( histo1, "ZeroBias No XE" );
    legend->AddEntry( histo2, "ZeroBias XE" );
    legend->AddEntry( XE_Ratio , "ZB Eff of XE" );
    legend->Draw();
    Histo_Canv->Draw();
}
