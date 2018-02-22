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
   //Float_t eff_binwidth = 1.0;
   Int_t eff_nbins = (metmax - metmin) / eff_binwidth;
   histo1 = new TH1F( "histo1", "Passrndm Trigger" , histnbins , metmin , metmax );
   histo2 = new TH1F( "histo2", "Passrndm Trigger XE20" , histnbins, metmin , metmax );
   XE_Ratio = new TEfficiency( "teff" , "Passrndm Efficiency" , eff_nbins, metmin , metmax );
   histo1j40= new TH1F( "histo1j40", "Passrndmj40 Trigger" , histnbins , metmin , metmax );
   histo2j40 = new TH1F( "histo2j40", "Passrndmj40 Trigger XE20" , histnbins, metmin , metmax );
   XE_Ratioj40 = new TEfficiency( "teffj40" , "Passrndmj40 Efficiency" , eff_nbins, metmin , metmax );
   fOutput->Add( histo1 );
   fOutput->Add( histo2 );
   fOutput->Add( XE_Ratio );
   fOutput->Add( histo1j40 );
   fOutput->Add( histo2j40 );
   fOutput->Add( XE_Ratioj40 );
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
   if (*passrndmj40 > 0.5 ){
       histo1j40->Fill( *metcell );
       XE_Ratioj40->Fill( *metl1 > 20.0 , *metcell );
       if ( *metl1>20.0 ){
           histo2j40->Fill( *metcell );
       }
   }
   return kTRUE;
}

void ZB_Eff_Selector::SlaveTerminate()
{
}

void ZB_Eff_Selector::Terminate()
{

    TFile* tempfile = new TFile("temp.root","RECREATE");


    if ( tempfile->IsOpen() ) printf("File opened successfully\n");
    histo1->Write();
    histo2->Write();
    XE_Ratio->Write();
    histo1j40->Write();
    histo2j40->Write();
    XE_Ratioj40->Write();
    tempfile->Close();

    TCanvas* random_canv = new TCanvas( "mycanv" , "Random Trigger Curves" );
    random_canv->Divide(2,1);
    random_canv->cd(1);
    gStyle->SetOptStat(kFALSE);
    TString alg_name = "metcell";
    random_canv->RangeAxis( 1.0 , 1.0 , 500.0 , 1.0 );

    histo1->SetLineColor(kBlue);
    histo2->SetLineColor(kMagenta);
    XE_Ratio->SetLineColor(kRed);

    histo1j40->SetLineColor(7);
    histo2j40->SetLineColor(12);
    XE_Ratioj40->SetLineColor(8);

    histo1j40->SetLineStyle(9);
    histo2j40->SetLineStyle(9);
    XE_Ratioj40->SetLineStyle(9);

    histo2->SetAxisRange(1.0,5.0e5,"Y");
    gPad->SetLogy();
    histo1->Draw();
    histo2->Draw("SAME");
    histo1j40->Draw("SAME");
    histo2j40->Draw("SAME");


    random_canv->cd(2);
    XE_Ratio->Draw();
    XE_Ratioj40->Draw("SAME");
    
    
    TLegend *legend = new TLegend( 0.57, 0.12 , 0.9, 0.4 , "" , "NDC");
    legend->AddEntry( histo1 , "metcell Random");
    legend->AddEntry( histo2 , "metcell Random XE20");
    legend->AddEntry( XE_Ratio , "Efficiency of ZBXE20 to ZB" );

    legend->AddEntry( histo1j40 , "metcell passrndmj40");
    legend->AddEntry( histo2j40 , "metcell passrndmj40 XE20");
    legend->AddEntry( XE_Ratioj40 , "Efficiency of passrndmj40 ZBXE20 to ZB" );
    random_canv->cd(1); //change back to pad 1 to put tlegend on lhs of diagram
    legend->Draw();
    random_canv->Draw();
}
