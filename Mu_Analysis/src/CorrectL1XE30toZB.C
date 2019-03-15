#include "CorrectL1XE30toZB.h"
ClassImp(CorrectL1XE30toZB);
void CorrectL1XE30toZB::Begin(){//{{{
    // getting these parameters needs to happen before process, but after construction
    // get values of efficiency fit parameters
   for (int i = 0 ; i < Number_Mu_Bins; i++){
        L1XE30fitPars[i][0] = ((TF1*)L1XE30_Efficiency_Fit_Objects->At(i))->GetParameter( 0 );
        L1XE30fitPars[i][1] = ((TF1*)L1XE30_Efficiency_Fit_Objects->At(i))->GetParameter( 1 );
        L1XE30fitPars[i][2] = ((TF1*)L1XE30_Efficiency_Fit_Objects->At(i))->GetParameter( 2 );

        // get values of uncertainties on efficiency fit parameters
        L1XE30fitParsErrs[i][0] = ((TF1*)L1XE30_Efficiency_Fit_Objects->At(i))->GetParError( 0 );
        L1XE30fitParsErrs[i][1] = ((TF1*)L1XE30_Efficiency_Fit_Objects->At(i))->GetParError( 1 );
        L1XE30fitParsErrs[i][2] = ((TF1*)L1XE30_Efficiency_Fit_Objects->At(i))->GetParError( 2 );
   }
   std::cout << "Evaluation of function inside correct l1xe30 to zb: " << ((TF1*)L1XE30_Efficiency_Fit_Objects->At(2))->Eval(20.) << std::endl;
}//}}}
Bool_t CorrectL1XE30toZB::Process(Long64_t entry)//{{{
{
   fReader.SetLocalEntry(entry);
    if ( isHLT_zb_L1XE30() && isGoodRun() ){
        for ( int i = 0 ; i < Number_Mu_Bins ; i++ ) {
            if ( inMuRange( Mu_Values[i] , Mu_Values[i+1] )){
                ((TH1F*)HLT_ZB_L1XE30_Corrected_to_ZB_MET_Distribution->At(i))->Fill( *cell_met , ComputeWeight( ((TF1*)L1XE30_Efficiency_Fit_Objects->At(i)) ) );
                // find the index of bin that this event falls into
                Int_t idx = ((TH1F*)HLT_ZB_L1XE30_Corrected_to_ZB_MET_Distribution->At(i))->GetBin( *cell_met );
                // error on the estimate of efficiency (de)
                Double_t de = TeffFitErr( *cell_met , L1XE30fitPars[i][0] , L1XE30fitPars[i][1] , L1XE30fitPars[i][2] , 
                            L1XE30fitParsErrs[i][0] , L1XE30fitParsErrs[i][1] , L1XE30fitParsErrs[i][2] , L1XE );
                // compute error on event: dn = (P * de / e**2); computeweight is P / e
                Double_t dn = de * ComputeWeight( ((TF1*)L1XE30_Efficiency_Fit_Objects->At(i)) ) / 
                    ((TF1*)L1XE30_Efficiency_Fit_Objects->At(i))->Eval( *cell_met );
                // increment error on that bin with the square of error on event (dn)^2
                L1XE30CorrectedToZBErrors[i][idx] = L1XE30CorrectedToZBErrors[i][idx] + pow(dn,2);
            }
        }
    }
   return kTRUE;
}//}}}
void CorrectL1XE30toZB::Terminate(){//{{{
    // do errors correctly
    for ( int i = 0 ; i < Number_Mu_Bins ; i++ ){
        for ( int j = 0 ; j < met_dist_nbins ; j++ ){
            ((TH1F*)HLT_ZB_L1XE30_Corrected_to_ZB_MET_Distribution->At(i))->SetBinError( j , TMath::Sqrt(L1XE30CorrectedToZBErrors[i][j]) );
        }
    }
	// Relative Normalization{{{
    // Scale the corrected ones to the original zb ones
    for (int i = 0 ;i < Number_Mu_Bins ; i++ ) {
        Scale_Factors[i] = ((TH1F*)HLT_ZB_L1ZB_MET_Distributions_by_Mubin->At(i))->GetBinContent( Normalization_Bin_Numbers[i] ) / 
            ((TH1F*)HLT_ZB_L1XE30_Corrected_to_ZB_MET_Distribution->At(i))->GetBinContent( Normalization_Bin_Numbers[i] );
        ((TH1F*)HLT_ZB_L1ZB_MET_Distributions_by_Mubin->At(i))->SetNormFactor( 1. );
        ((TH1F*)HLT_ZB_L1XE30_Corrected_to_ZB_MET_Distribution->At(i))->SetNormFactor( 1. );
        ((TH1F*)HLT_ZB_L1XE30_Corrected_to_ZB_MET_Distribution->At(i))->Scale( Scale_Factors[i] );
    }
    //}}}
}//}}}
