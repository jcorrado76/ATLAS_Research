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
    // TODO: do this better
    for ( int i = 0 ; i < Number_Mu_Bins ; i++ ){
        Scale_Factors[i] = HLT_ZB_L1ZB_MET_Distributions_by_Mubin[i]->GetBinContent( Normalization_Bin_Numbers[i] ) / 
            HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution[i]->GetBinContent( Normalization_Bin_Numbers[i] );
        std::cout << "Scale factor: " << i << " = " << Scale_Factors[i] << std::endl;
        HLT_ZB_L1ZB_MET_Distributions_by_Mubin[i]->SetNormFactor( 1. );
        HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution[i]->SetNormFactor( 1. );
        HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution[i]->Scale( Scale_Factors[i] );
    }
}//}}}
void CorrectL1XE50toZB::Write( TString fname ){//{{{
    TFile* mu_analysis_file = TFile::Open("mu_analysis.root","UPDATE");
    if ( mu_analysis_file->IsOpen() ){
        printf("File opened successfully\n");
        for ( int i = 0 ; i < Number_Mu_Bins ; i++ ){
            HLT_ZB_L1ZB_MET_Distributions_by_Mubin.at(i)->Write("",kOverwrite);
            HLT_ZB_L1XE30_MET_Distributions_by_Mubin.at(i)->Write("",kOverwrite);
            HLT_ZB_L1XE30_Corrected_to_ZB_MET_Distribution.at(i)->Write("",kOverwrite);
            HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution.at(i)->Write("",kOverwrite);
            L1XE30_Efficiency_Objects.at(i)->Write("",kOverwrite);
            L1XE50_Efficiency_Objects.at(i)->Write("",kOverwrite);
            L1XE30_Efficiency_Fit_Objects.at(i)->Write("",kOverwrite);
            L1XE50_Efficiency_Fit_Objects.at(i)->Write("",kOverwrite);
      }
    }else{
        printf("Unable to open file\n");
    }

    mu_analysis_file->Close();
}//}}}
