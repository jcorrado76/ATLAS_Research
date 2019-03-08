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
                   HLT_ZB_L1XE30_MET_Distributions_by_Mubin[j]->Fill(*cell_met , *HLT_noalg_L1XE30_prescale);
                   L1XE50_Efficiency_Objects[j]->Fill(*L1_met > L1XE , *cell_met);
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
}//}}}
void ComputeL1XE50toL1XE30Efficiency::Streamer( TBuffer &R__b ){//{{{
    if (R__b.IsReading()) {
      TObject::Streamer(R__b);
      for ( int i = 0 ; i < Number_Mu_Bins ; i++ ){
       R__b >> HLT_ZB_L1ZB_MET_Distributions_by_Mubin.at(i);
       R__b >> HLT_ZB_L1XE30_MET_Distributions_by_Mubin.at(i);
       R__b >> HLT_ZB_L1XE30_Corrected_to_ZB_MET_Distribution.at(i);
       R__b >> HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution.at(i);
       R__b >> L1XE30_Efficiency_Objects.at(i);
       R__b >> L1XE50_Efficiency_Objects.at(i);
       R__b >> L1XE30_Efficiency_Fit_Objects.at(i);
       R__b >> L1XE50_Efficiency_Fit_Objects.at(i);
      }
   } else {
      R__b.WriteVersion(Jburr_Template_Selector::IsA());
      TObject::Streamer(R__b);
      for ( int i = 0 ; i < Number_Mu_Bins ; i++ ){
       R__b << HLT_ZB_L1ZB_MET_Distributions_by_Mubin.at(i);
       R__b << HLT_ZB_L1XE30_MET_Distributions_by_Mubin.at(i);
       R__b << HLT_ZB_L1XE30_Corrected_to_ZB_MET_Distribution.at(i);
       R__b << HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution.at(i);
       R__b << L1XE30_Efficiency_Objects.at(i);
       R__b << L1XE50_Efficiency_Objects.at(i);
       R__b << L1XE30_Efficiency_Fit_Objects.at(i);
       R__b << L1XE50_Efficiency_Fit_Objects.at(i);
      }
   }
}//}}}
