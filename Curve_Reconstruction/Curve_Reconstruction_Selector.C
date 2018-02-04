#define Curve_Reconstruction_Selector_cxx

#include "Curve_Reconstruction_Selector.h"
#include <TH2.h>
#include <TStyle.h>

void Curve_Reconstruction_Selector::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
}

void Curve_Reconstruction_Selector::SlaveBegin(TTree * /*tree*/)
{

   TString option = GetOption();

   TH1F* histo = new TH1F( "histo", "Unbiased Curves" , 400 , 0.0 , 300.0 );


   fOutput->Add( histo );

}

Bool_t Curve_Reconstruction_Selector::Process(Long64_t entry)
{

   fReader.SetEntry(entry);


    histo->Fill( metcell );

   return kTRUE;
}

void Curve_Reconstruction_Selector::SlaveTerminate()
{
}

void Curve_Reconstruction_Selector::Terminate()
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
