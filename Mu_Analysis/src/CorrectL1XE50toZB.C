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
void CorrectL1XE50toZB::Write( TString fname ){//{{{
    TFile* mu_analysis_file = TFile::Open("mu_analysis.root","UPDATE");
    if ( mu_analysis_file->IsOpen() ){
        printf("File opened successfully\n");
        for ( int i = 0 ; i < Number_Mu_Bins ; i++ ){
            HLT_ZB_L1ZB_MET_Distributions_by_Mubin.at(i)->Write("",kOverwrite);
            std::cout << "wrote hlt_zb_l1_zb_dist_" << i << std::endl;
            HLT_ZB_L1XE30_MET_Distributions_by_Mubin.at(i)->Write("",kOverwrite);
            std::cout << "wrote hlt_zb_l1_zb_dist_" << i << std::endl;
            HLT_ZB_L1XE30_Corrected_to_ZB_MET_Distribution.at(i)->Write("",kOverwrite);
            std::cout << "wrote corrected_hlt_zb_l1_xe30_tozb_dist_" << i << std::endl;
            HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution.at(i)->Write("",kOverwrite);
            std::cout << "wrote corrected_hlt_zb_l1xe50_tozb_dist_" << i << std::endl;
            L1XE30_Efficiency_Objects.at(i)->Write("",kOverwrite);
            std::cout << "wrote l1xe30EfficiencyObject_" << i << std::endl;
            L1XE50_Efficiency_Objects.at(i)->Write("",kOverwrite);
            std::cout << "wrote l1xe50efficiencyObject_" << i << std::endl;
            L1XE30_Efficiency_Fit_Objects.at(i)->Write("",kOverwrite);
            std::cout << "l1xe30efficiencyFitObject_" << i << std::endl;
            L1XE50_Efficiency_Fit_Objects.at(i)->Write("",kOverwrite);
            std::cout << "wrote l1xe50efficiencyFitObject_" << i << std::endl;
      }
    }else{
        printf("Unable to open file\n");
    }

    mu_analysis_file->Close();
}//}}}
