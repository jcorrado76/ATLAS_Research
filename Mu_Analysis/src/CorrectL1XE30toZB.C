#include "CorrectL1XE30toZB.h"
ClassImp(CorrectL1XE30toZB);
void CorrectL1XE30toZB::UpdateFitParameters(){//{{{
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
}//}}}
Bool_t CorrectL1XE30toZB::Process(Long64_t entry)//{{{
{
   fReader.SetLocalEntry(entry);
    if ( isHLT_zb_L1XE30() && isGoodRun() ){
        for ( int i = 0 ; i < Number_Mu_Bins ; i++ ) {
            if ( inMuRange( Mu_Values[i] , Mu_Values[i+1] )){
                ((TH1D*)HLT_ZB_L1XE30_Corrected_to_ZB_MET_Distribution->At(i))->Fill( *cell_met , ComputeWeight( ((TF1*)L1XE30_Efficiency_Fit_Objects->At(i)) ) );
                // find the index of bin that this event falls into
                Int_t idx = ((TH1D*)HLT_ZB_L1XE30_Corrected_to_ZB_MET_Distribution->At(i))->FindBin( *cell_met );
                // error on the estimate of efficiency (de)
                Double_t de = TeffFitErr( *cell_met , L1XE30fitPars[i][0] , L1XE30fitPars[i][1] , L1XE30fitPars[i][2] , 
                            L1XE30fitParsErrs[i][0] , L1XE30fitParsErrs[i][1] , L1XE30fitParsErrs[i][2] , L1XE );
                // (dn)^2 = (P/e)^2 * [ (de/e)^2 + 1 ];computeweight is P / e
                Double_t e30ZB = ((TF1*)L1XE30_Efficiency_Fit_Objects->At(i))->Eval( *cell_met );
                Double_t dn2 = pow( ComputeWeight( ((TF1*)L1XE30_Efficiency_Fit_Objects->At(i)) ),2 ) * 
                    ( pow(de / e30ZB,2) + 1 );
                // increment error on that bin with the square of error on event (dn)^2
                L1XE30CorrectedToZBErrors[i][idx] = L1XE30CorrectedToZBErrors[i][idx] + dn2;
                // compute this just in case. ROOT does it on its own, but i want to compare my error to ROOTS
                // error
                ZBErrors[i][idx] = ZBErrors[i][idx] + pow(*HLT_noalg_zb_L1ZB_prescale,2);
                RootZBErrVersMyErrL2Norm[i][idx] = RootZBErrVersMyErrL2Norm[i][idx] + pow(*HLT_noalg_zb_L1ZB_prescale,2);
            }
        }
    }
   return kTRUE;
}//}}}
void CorrectL1XE30toZB::Terminate(){//{{{
    // do errors correctly
    Double_t sumOfSquareDeviations = 0.0;
    for ( int i = 0 ; i < Number_Mu_Bins ; i++ ){
        for ( int j = 0 ; j < met_dist_nbins ; j++ ){
            if (L1XE30CorrectedToZBErrors[i][j] == 0 && ((TH1D*)HLT_ZB_L1XE30_Corrected_to_ZB_MET_Distribution->At(i))->GetBinContent( j ) != 0 ){
                std::cout << "Got zero error, but nonzero number of entries in corrected bin" << std::endl;
                std::cout << "At i= " << i << " and j = " << j << std::endl;
            }
            ((TH1D*)HLT_ZB_L1XE30_Corrected_to_ZB_MET_Distribution->At(i))->SetBinError( j , TMath::Sqrt(L1XE30CorrectedToZBErrors[i][j]) );
            sumOfSquareDeviations = sumOfSquareDeviations + pow(TMath::Sqrt(RootZBErrVersMyErrL2Norm[i][j]) - 
                    ((TH1D*)HLT_ZB_L1ZB_MET_Distributions_by_Mubin->At(i))->GetBinError(j),2);
        }
    }
    // Relative Normalization{{{
    // Scale the corrected ones to the original zb ones
    TH1D* zb_dist;
    TH1D* l1xe30_corrected_zb_dist;
    for (int i = 0 ;i < Number_Mu_Bins ; i++ ) {
        // get histograms
        zb_dist = ((TH1D*)(HLT_ZB_L1ZB_MET_Distributions_by_Mubin->At(i)));
        l1xe30_corrected_zb_dist = ((TH1D*)(HLT_ZB_L1XE30_Corrected_to_ZB_MET_Distribution->At(i)));
        for (int j = 0 ; j < Number_Scale_Factor_Samples ; j++ ){
            int bin_number = Normalization_Bin_Number[i] + j * 1;
            // compute f_i's, how to pick the samples determines j dependency of rhs here
            L1XE30Scale_Factors[i][j] = zb_dist->GetBinContent(bin_number) / 
                l1xe30_corrected_zb_dist->GetBinContent(bin_number); // shift bin number by 1 for each sample; this corresponds to 5GeV
            // compute (sigma_i)^2's
            L1XE30Scale_Factor_Errors[i][j] = pow(L1XE30Scale_Factors[i][j],2) *
                ( pow( L1XE30CorrectedToZBErrors[i][bin_number] / 
                      l1xe30_corrected_zb_dist->GetBinContent(bin_number) ,2) +
                  pow( zb_dist->GetBinError(bin_number) / 
                      zb_dist->GetBinContent(bin_number) ,2)
                  );
        }
        // compute f_mle
        Double_t numerator = 0.0;
        Double_t denominator = 0.0;
        for (int j = 0 ; j < Number_Scale_Factor_Samples ; j++ ){
            if ( !(isnan(L1XE30Scale_Factors[i][j])) && !(isnan(L1XE30Scale_Factor_Errors[i][j])) && 
                    !(L1XE30Scale_Factor_Errors[i][j]==0) ){
                    // these errs are already squared
                    numerator = numerator + (L1XE30Scale_Factors[i][j] / L1XE30Scale_Factor_Errors[i][j]);                     
                    denominator = denominator + (1./L1XE30Scale_Factor_Errors[i][j]);
            }else{
                std::cout << "\nSomething wrong with scale factor j = " << j << " in mubin i = " << i << 
                    ". skipping..." << std::endl;
                std::cout << "L1XE30Scale_Factors[i][j] = " << L1XE30Scale_Factors[i][j] << 
                    "\tL1XE30Scale_Factor_Errors[i][j] = " << L1XE30Scale_Factor_Errors[i][j] << "\n" << std::endl;
            }
        }
        Double_t f_mle = numerator / denominator;
        std::cout << "L1XE30 Scale factor: " << i << " = " << f_mle << std::endl;
        (l1xe30_corrected_zb_dist)->Scale( f_mle );
    }
    //}}}
}//}}}
