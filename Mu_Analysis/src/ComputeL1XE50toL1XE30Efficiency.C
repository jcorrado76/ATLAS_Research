#include "ComputeL1XE50toL1XE30Efficiency.h"
ClassImp(ComputeL1XE50toL1XE30Efficiency);
Bool_t ComputeL1XE50toL1XE30Efficiency::Process(Long64_t entry)//{{{
{
   fReader.SetLocalEntry(entry);
   if ( isHLT_zb_L1XE30()  && isGoodRun() ){
       Float_t muLow , muHigh;
       for ( int i = 0; i < Number_Mu_Bins ; i++ ){
           muLow = Mu_Values[ i ];
           muHigh = Mu_Values[ i + 1 ];
           if ( inMuRange( muLow , muHigh ) ){
               for ( int j = 0 ; j < Number_Mu_Bins ; j++ ){
                   HLT_ZB_L1XE30_MET_Distributions_by_Mubin[j]->Fill(*MET_Data , *HLT_noalg_L1XE30_prescale);
                   L1XE50_Efficiency_Objects[j]->Fill(*L1_MET > L1XE , *MET_Data);
               }
           }
       }
   }
   return kTRUE;
}//}}}
void ComputeL1XE50toL1XE30Efficiency::Terminate()//{{{
{
    for (int i = 0 ; i < Number_Mu_Bins ; i++ ){
       L1XE50_Efficiency_Fit_Objects[i] = generateFitFunction( L1XE50_Efficiency_Objects[i] );
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
        HLT_ZB_L1XE30_MET_Distributions_by_Mubin[i]->Write(Name);
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
