#define ComputeL1XE30toZBEfficiency_cxx
#include "ComputeL1XE30toZBEfficiency.h"
ClassImp(ComputeL1XE30toZBEfficiency);
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
               HLT_ZB_L1ZB_MET_Distributions_by_Mubin.at(i)->Fill(*cell_met , *HLT_noalg_zb_L1ZB_prescale);
               L1XE30_Efficiency_Objects.at(i)->Fill(*L1_met > L1XE , *cell_met);
           }
       }
   }
   return kTRUE;
}//}}}
void ComputeL1XE30toZBEfficiency::Terminate() //{{{
{
    // create the fit function for the l1xe30 efficiencies
    for ( int i = 0; i < Number_Mu_Bins ; i++ ){
    L1XE30_Efficiency_Fit_Objects[i] = generateFitFunction( L1XE30_Efficiency_Objects[i] );
    }
}//}}}
