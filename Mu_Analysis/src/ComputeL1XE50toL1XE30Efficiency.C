#define PlotMETDistsVersMu_cxx
#include "ComputeL1XE50toL1XE30Efficiency.h"
ClassImp(ComputeL1XE50toL1XE30Efficiency);
void ComputeL1XE50toL1XE30Efficiency::Begin(TTree *) // {{{
{
   TString option = GetOption();
   for (int i = 0 ; i < Number_Mu_Bins ; i++){
       muLow = Mu_Values[i];
       muHigh = Mu_Values[i+1];
       Name.Form("metmu%.0fthru%.0f" , muLow , muHigh );
       EfficiencyName.Form("metmu%.0fthru%.0fEfficiency", muLow , muHigh );
       Title.Form("L1 XE 30 MET Distribution for %s With Actint Between %.0f and %.0f" ,Alg_Name.Data(), muLow , muHigh );
       EfficiencyTitle.Form("Efficiency of L1XE 50 As a Function of %s for Actint Between %.0f and %.0f", Alg_Name.Data() , muLow , muHigh );

       Met_Distributions_By_Mu_Bin[i] = new TH1F( Name , Title , met_dist_nbins , gevLow , gevHigh );
       L1XE50_Efficiency_Objects[i] = new TEfficiency( EfficiencyName , EfficiencyTitle , efficiency_nbins , gevLow , gevHigh );
       L1XE50_Efficiency_Fit_Objects[i] = new TF1();
   }
} // }}}
Bool_t ComputeL1XE50toL1XE30Efficiency::Process(Long64_t entry)//{{{
{
   fReader.SetLocalEntry(entry);
   // if the event has passed HLT_noalg_zb_L1ZB_passed, and is not one of the bad run numbers
   if ( isHLT_zb_L1XE30()  && isGoodRun() ){
       Float_t muLow , muHigh;
       for ( int i = 0; i < Number_Mu_Bins ; i++ ){
           muLow = Mu_Values[ i ];
           muHigh = Mu_Values[ i + 1 ];
           if ( inMuRange( muLow , muHigh ) ){
               for ( int j = 0 ; j < Number_Mu_Bins ; j++ ){
                   Met_Distributions_By_Mu_Bin[j]->Fill(*MET_Data , *HLT_noalg_L1XE30_prescale);
                   L1XE50_Efficiency_Objects[j]->Fill(*L1_MET > XE , *MET_Data);
               }
           }
       }
   }
   return kTRUE;
}//}}}
void ComputeL1XE50toL1XE30Efficiency::Terminate()//{{{
{
    for (int i = 0 ; i < Number_Mu_Bins ; i++ ){
       L1XE50_Efficiency_Objects[i]->SetLineColor( Colors[i] );
       L1XE50_Efficiency_Objects[i]->SetMarkerStyle( Colors[i] );
       L1XE50_Efficiency_Fit_Objects[i] = generateFitFunction( L1XE50_Efficiency_Objects[i] );
       L1XE50_Efficiency_Fit_Objects[i]->SetLineColor( Colors[i] );
       Met_Distributions_By_Mu_Bin[i]->SetLineColor( Colors[i] );
       Normalized_Met_Distributions[i] = ((TH1F*)(Met_Distributions_By_Mu_Bin[i])->Clone());
       Normalized_Met_Distributions[i]->SetNormFactor(1.);
    }

    // WRITE TO FILE {{{
    TFile* Mu_Analysis_File = TFile::Open("run_files/mu_analysis.root", "UPDATE");
    TDirectory* l1xe30_met_distributions = (TDirectory*) Mu_Analysis_File->Get("l1xe30_met_distributions");
    if (!l1xe30_met_distributions){
        l1xe30_met_distributions = Mu_Analysis_File->mkdir("l1xe30_met_distributions");
    }
    l1xe30_met_distributions->cd();
    for ( int i = 0 ; i < Number_Mu_Bins ; i++ ) {
        Name.Form("l1xe30_met_distribution_mubin%d" , i );
        Met_Distributions_By_Mu_Bin[i]->Write(Name);
    }

    TDirectory* efficiency_curves = Mu_Analysis_File->mkdir("l1xe50_efficiency_curves");
    efficiency_curves->cd();
    for ( int i = 0 ; i < Number_Mu_Bins ; i++ ){
        Name.Form("l1xe50_efficiency_object_mubin%d" , i );
        L1XE50_Efficiency_Objects[i]->Write(Name);
    }

    TDirectory* L1XE50_Efficiency_Fit_Objects_Dir = Mu_Analysis_File->mkdir("l1xe50_efficiency_fits");
    L1XE50_Efficiency_Fit_Objects_Dir->cd();
    for ( int i = 0 ; i < Number_Mu_Bins ; i++ ){
        Name.Form("l1xe50_efficiency_fit_mubin%d" , i );
        L1XE50_Efficiency_Fit_Objects[i]->Write(Name);
    }

    Mu_Analysis_File->Close();//}}}
}//}}}
void ComputeL1XE50toL1XE30Efficiency::SlaveBegin(TTree*){TString option = GetOption();}
void ComputeL1XE50toL1XE30Efficiency::SlaveTerminate(){}
void ComputeL1XE50toL1XE30Efficiency::Init(TTree *tree){fReader.SetTree(tree);}
