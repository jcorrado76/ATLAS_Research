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
                ((TH1F*)HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution->At(i))->Fill( *cell_met , ComputeWeight( ((TF1*)L1XE30_Efficiency_Fit_Objects->At(i)), ((TF1*)L1XE50_Efficiency_Fit_Objects->At(i)) ) );
            }
        }
   }
   return kTRUE;
}//}}}
void CorrectL1XE50toZB::Terminate(){//{{{
	// Relative Normalization
    // TODO: do this better
    for ( int i = 0 ; i < Number_Mu_Bins ; i++ ){
        Scale_Factors[i] = ((TH1F*)HLT_ZB_L1ZB_MET_Distributions_by_Mubin->At(i))->GetBinContent( Normalization_Bin_Numbers[i] ) / 
            ((TH1F*)HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution->At(i))->GetBinContent( Normalization_Bin_Numbers[i] );
        std::cout << "Scale factor: " << i << " = " << Scale_Factors[i] << std::endl;
        ((TH1F*)HLT_ZB_L1ZB_MET_Distributions_by_Mubin->At(i))->SetNormFactor( 1. );
        ((TH1F*)HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution->At(i))->SetNormFactor( 1. );
        ((TH1F*)HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution->At(i))->Scale( Scale_Factors[i] );
    }
}//}}}
void CorrectL1XE50toZB::Write( TString fname ){//{{{
    TFile* mu_analysis_file = TFile::Open("mu_analysis.root","UPDATE");
    if ( mu_analysis_file->IsOpen() ){
        printf("File opened successfully\n");
            HLT_ZB_L1ZB_MET_Distributions_by_Mubin->Write("",TObject::kSingleKey);
            HLT_ZB_L1XE30_MET_Distributions_by_Mubin->Write("",TObject::kSingleKey);
            HLT_ZB_L1XE30_Corrected_to_ZB_MET_Distribution->Write("",TObject::kSingleKey);
            HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution->Write("",TObject::kSingleKey);
            L1XE30_Efficiency_Objects->Write("",TObject::kSingleKey);
            L1XE50_Efficiency_Objects->Write("",TObject::kSingleKey);
            L1XE30_Efficiency_Fit_Objects->Write("",TObject::kSingleKey);
            L1XE50_Efficiency_Fit_Objects->Write("",TObject::kSingleKey);
    }else{
        printf("Unable to open file\n");
    }

    mu_analysis_file->Close();
}//}}}
