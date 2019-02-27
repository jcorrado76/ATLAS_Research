#define ComputeL1XE30toZBEfficiency_cxx
#include "ComputeL1XE30toZBEfficiency.h"
ClassImp(ComputeL1XE30toZBEfficiency);
void ComputeL1XE30toZBEfficiency::Begin(TTree *) // {{{
{
   TString option = GetOption();
   std::cout << "Creating the proper met distribution, l1xe30 efficiency and l1xe30 efficiency fit objects" << std::endl;
   for (int i = 0 ; i < Number_Mu_Bins ; i++){
       muLow = Mu_Values[i];
       muHigh = Mu_Values[i+1];
       Name.Form("metmu%.0fthru%.0f" , muLow , muHigh );
       EfficiencyName.Form("metmu%.0fthru%.0fEfficiency", muLow , muHigh );
       Title.Form("ZeroBias MET Distribution for %s With Actint Between %.0f and %.0f" ,Alg_Name.Data(), muLow , muHigh );
       EfficiencyTitle.Form("Efficiency of L1XE 30 As a Function of %s for Actint Between %.0f and %.0f", Alg_Name.Data() , muLow , muHigh );

       Met_Distributions_By_Mu_Bin[i] = new TH1F( Name , Title , met_dist_nbins , gevLow , gevHigh );
       L1XE30_Efficiency_Objects[i] = new TEfficiency( EfficiencyName , EfficiencyTitle , efficiency_nbins , gevLow , gevHigh );
       L1XE30_Efficiency_Fit_Objects[i] = new TF1();
   }
} // }}}
Bool_t ComputeL1XE30toZBEfficiency::Process(Long64_t entry)//{{{
{
   fReader.SetLocalEntry(entry);

   // if the event has passed HLT_noalg_zb_L1ZB_passed, and is not one of the bad run numbers
   if ( isHLT_zb_L1ZB()  && isGoodRun() ){
       Float_t muLow, muHigh;
       for ( int i = 0; i < Number_Mu_Bins ; i++ ){
           muLow = Mu_Values[ i ];
           muHigh = Mu_Values[ i + 1 ];
           if ( inMuRange( muLow , muHigh ) ){
               for ( int j = 0 ; j < Number_Mu_Bins ; j++ ){
                   Met_Distributions_By_Mu_Bin[j]->Fill(*MET_Data , *HLT_noalg_zb_L1ZB_prescale);
                   L1XE30_Efficiency_Objects[j]->Fill(*L1_MET > XE , *MET_Data);
               }
           }
       }
   }
   return kTRUE;
}//}}}
void ComputeL1XE30toZBEfficiency::Terminate() //{{{
{
    // Set plot colors and generate fit functions {{{
   for ( int i = 0; i < Number_Mu_Bins ; i++ ){
       L1XE30_Efficiency_Objects[i]->SetLineColor( Colors[i] );
       L1XE30_Efficiency_Objects[i]->SetMarkerStyle( Colors[i] );
       L1XE30_Efficiency_Fit_Objects[i] = generateFitFunction( L1XE30_Efficiency_Objects[i] );
       L1XE30_Efficiency_Fit_Objects[i]->SetLineColor( Colors[i] );
       Met_Distributions_By_Mu_Bin[i]->SetLineColor( Colors[i] );
   }
   //}}}
    // Write MET Histograms, Efficiency Objects and Efficiency Fits to File {{{
    std::cout << "Writing the met distributions to zb_met_distributions" << std::endl;
    TFile* Mu_Analysis_File = TFile::Open("run_files/mu_analysis.root", "RECREATE");
    TDirectory* zb_met_distributions = Mu_Analysis_File->mkdir("zb_met_distributions");
    zb_met_distributions->cd();
    for ( int  i = 0 ; i < Number_Mu_Bins ; i++ ){

        Name.Form("zb_met_dist_mubin%d" , i );
        Met_Distributions_By_Mu_Bin[i]->Write(Name);
    }

    std::cout << "Writing the l1xe30 efficiency curves to l1xe30_efficiency_curves" << std::endl;
    TDirectory* efficiency_curves = Mu_Analysis_File->mkdir("l1xe30_efficiency_curves");
    efficiency_curves->cd();
    for ( int  i = 0 ; i < Number_Mu_Bins ; i++ ){
        Name.Form("l1xe30_efficiency_object%d" , i );
        L1XE30_Efficiency_Objects[i]->Write(Name);
    }

    std::cout << "Writing the l1xe30 efficiency curve objects to l1xe30_efficiency_curves" << std::endl;
    TDirectory* L1XE30_Efficiency_Fit_Objects_Dir = Mu_Analysis_File->mkdir("l1xe30_efficiency_fits");
    L1XE30_Efficiency_Fit_Objects_Dir->cd();
    for ( int  i = 0 ; i < Number_Mu_Bins ; i++ ){
        Name.Form("l1xe30_efficiency_fit%d" , i );
        L1XE30_Efficiency_Fit_Objects[i]->Write(Name);
    }

    Mu_Analysis_File->Close();//}}}
}//}}}
void ComputeL1XE30toZBEfficiency::SlaveBegin(TTree*){TString option = GetOption();}
void ComputeL1XE30toZBEfficiency::SlaveTerminate(){}
void ComputeL1XE30toZBEfficiency::Init(TTree *tree){fReader.SetTree(tree);}
