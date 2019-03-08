#define CorrectL1XE50toZB_cxx
#include "CorrectL1XE50toZB.h"
#include <math.h>
ClassImp(CorrectL1XE50toZB);
Bool_t CorrectL1XE50toZB::Process(Long64_t entry)//{{{
{
   fReader.SetLocalEntry(entry);
   // still need to compute new error and pass it to this fill function somehow
   if ( isHLT_zb_L1XE50() && isGoodRun() ){
       for ( int i = 0 ; i < Number_Mu_Bins ; i++ ) {
           if ( inMuRange( Mu_Values[i] , Mu_Values[i+1] )){
                HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution[i]->Fill( *cell_met , ComputeWeight( L1XE30_Efficiency_Fit_Objects[i], L1XE50_Efficiency_Fit_Objects[i] ) );
            }
        }
   }
   return kTRUE;
}//}}}
void CorrectL1XE50toZB::Terminate(){//{{{
	// Relative Normalization
    for ( int i = 0 ; i < Number_Mu_Bins ; i++ ){
        Scale_Factors[i] = HLT_ZB_L1ZB_MET_Distributions_by_Mubin[i]->GetBinContent( Normalization_Bin_Numbers[i] ) / 
            HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution[i]->GetBinContent( Normalization_Bin_Numbers[i] );
        //if (isnan( Scale_Factors[i] )){
            //std::cout << "Scale factor " << i << ": " << Scale_Factors[i] << " is NaN" << std::endl;
            //std::cout << "MET Counts in mubin " << i << ": " << 
                //HLT_ZB_L1ZB_MET_Distributions_by_Mubin[i]->GetBinContent( Normalization_Bin_Numbers[i] ) << 
                //" in normalization bin number: " << Normalization_Bin_Numbers[i] << std::endl;
            //std::cout << "Counts in the Normalized MET distribution bin: " << 
                //HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution[i]->GetBinContent( Normalization_Bin_Numbers[i] ) << std::endl;
        //}
        std::cout << "Scale factor: " << i << " = " << Scale_Factors[i] << std::endl;
        HLT_ZB_L1ZB_MET_Distributions_by_Mubin[i]->SetNormFactor( 1. );
        HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution[i]->SetNormFactor( 1. );
        HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution[i]->Scale( Scale_Factors[i] );
    }
}//}}}
