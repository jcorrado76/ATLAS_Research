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
               ((TH1F*)HLT_ZB_L1XE30_MET_Distributions_by_Mubin->At(i))->Fill(*cell_met , *HLT_noalg_L1XE30_prescale);
               ((TEfficiency*)L1XE50_Efficiency_Objects->At(i))->Fill(*L1_met > L1XE , *cell_met);
           }
       }
   }
   return kTRUE;
}//}}}
void ComputeL1XE50toL1XE30Efficiency::Terminate()//{{{
{
    for (int i = 0 ; i < Number_Mu_Bins ; i++ ){
       //L1XE50_Efficiency_Fit_Objects->Add(generateFitFunction( ((TEfficiency*)L1XE50_Efficiency_Objects->At(i)), L1XE ,0.1,0.0,10.0,true));
       L1XE50_Efficiency_Fit_Objects->Add(generateFitFunction( ((TEfficiency*)L1XE50_Efficiency_Objects->At(i)), 0.0 ,0.1,0.0,10.0,true));
       ((TF1*)L1XE50_Efficiency_Fit_Objects->At(i))->SetLineColor( Colors[i] );
       Name.Form("l1xe50_efficiency_fit_obj_%d" , i );
       ((TF1*)L1XE50_Efficiency_Fit_Objects->At(i))->SetName( Name );
    }
}//}}}
