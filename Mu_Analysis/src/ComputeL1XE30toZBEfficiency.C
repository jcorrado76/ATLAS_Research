#include "ComputeL1XE30toZBEfficiency.h"
ClassImp(ComputeL1XE30toZBEfficiency);
Bool_t ComputeL1XE30toZBEfficiency::Process(Long64_t entry)//{{{
{
   fReader.SetLocalEntry(entry);
   if ( isHLT_zb_L1ZB()  && isGoodRun() && *RunNumber < 325500){
       Float_t muLow, muHigh;
       for ( int i = 0; i < Number_Mu_Bins ; i++ ){
           muLow = Mu_Values[ i ];
           muHigh = Mu_Values[ i + 1 ];
           if ( inMuRange( muLow , muHigh ) ){
               ((TH1D*)HLT_ZB_L1ZB_MET_Distributions_by_Mubin->At(i))->Fill(*cell_met , *HLT_noalg_zb_L1ZB_prescale);
               ((TEfficiency*)L1XE30_Efficiency_Objects->At(i))->Fill(*L1_met > L1XE , *cell_met);
           }
       }
   }
   return kTRUE;
}//}}}
void ComputeL1XE30toZBEfficiency::Terminate() //{{{
{
    for ( int i = 0; i < Number_Mu_Bins ; i++ ){
        L1XE30_Efficiency_Fit_Objects->Add( generateFitFunction( ((TEfficiency*)L1XE30_Efficiency_Objects->At(i)), L1XE ));
       ((TF1*)L1XE30_Efficiency_Fit_Objects->At(i))->SetLineColor( Colors[i] );
       Name.Form("l1xe30_efficiency_fit_obj_%d" , i );
       ((TF1*)L1XE30_Efficiency_Fit_Objects->At(i))->SetName( Name );
       ((TF1*)L1XE30_Efficiency_Fit_Objects->At(i))->SetTitle( Name );
    }
}//}}}
