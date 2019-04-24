#include "CorrectL1XE50toZB.h"
ClassImp(CorrectL1XE50toZB);
void CorrectL1XE50toZB::UpdateFitParameters(){//{{{
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


        L1XE50fitPars[i][0] = ((TF1*)L1XE50_Efficiency_Fit_Objects->At(i))->GetParameter( 0 );
        L1XE50fitPars[i][1] = ((TF1*)L1XE50_Efficiency_Fit_Objects->At(i))->GetParameter( 1 );
        L1XE50fitPars[i][2] = ((TF1*)L1XE50_Efficiency_Fit_Objects->At(i))->GetParameter( 2 );

        // get values of uncertainties on efficiency fit parameters
        L1XE50fitParsErrs[i][0] = ((TF1*)L1XE50_Efficiency_Fit_Objects->At(i))->GetParError( 0 );
        L1XE50fitParsErrs[i][1] = ((TF1*)L1XE50_Efficiency_Fit_Objects->At(i))->GetParError( 1 );
        L1XE50fitParsErrs[i][2] = ((TF1*)L1XE50_Efficiency_Fit_Objects->At(i))->GetParError( 2 );
   }
}//}}}
Bool_t CorrectL1XE50toZB::Process(Long64_t entry)//{{{
{
   fReader.SetLocalEntry(entry);
   // still need to compute new error and pass it to this fill function somehow
   if ( isHLT_zb_L1XE50() && isGoodRun()  ){
       for ( int i = 0 ; i < Number_Mu_Bins ; i++ ) {
           if ( inMuRange( Mu_Values[i] , Mu_Values[i+1] )){
                ((TH1D*)HLT_ZB_L1XE50_MET_Distributions_by_Mubin->At(i))->Fill(*cell_met , *L1_XE50_prescale);
                ((TH1D*)HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution->At(i))->Fill( *cell_met , ComputeWeight( ((TF1*)L1XE30_Efficiency_Fit_Objects->At(i)), ((TF1*)L1XE50_Efficiency_Fit_Objects->At(i)) ) );
                // find the index of bin that this event falls into
                Int_t idx = ((TH1D*)HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution->At(i))->FindBin( *cell_met );
                // error on the estimate of efficiency (de)
                Double_t deXE30 = TeffFitErr( *cell_met , L1XE30fitPars[i][0] , L1XE30fitPars[i][1] , L1XE30fitPars[i][2] , 
                            L1XE30fitParsErrs[i][0] , L1XE30fitParsErrs[i][1] , L1XE30fitParsErrs[i][2] , 30.0 );
                Double_t deXE50 = TeffFitErr( *cell_met , L1XE50fitPars[i][0] , L1XE50fitPars[i][1] , L1XE50fitPars[i][2] , 
                            L1XE50fitParsErrs[i][0] , L1XE50fitParsErrs[i][1] , L1XE50fitParsErrs[i][2] , 50.0 );
                // compute error on event: dn^2 = (P /(e1 * e2))^2*((de1/e1)^2+(de2/e2)^2); computeweight is P / (e1 * e2)
                Double_t dn2 = pow(ComputeWeight( ((TF1*)L1XE30_Efficiency_Fit_Objects->At(i)),((TF1*)L1XE50_Efficiency_Fit_Objects->At(i)) ),2) *
                    (pow(deXE30/(((TF1*)L1XE30_Efficiency_Fit_Objects->At(i))->Eval(*cell_met)),2) + pow(deXE50/(((TF1*)L1XE50_Efficiency_Fit_Objects->At(i))->Eval(*cell_met)),2)+1.);
                if (isnan(dn2)){
                    std::cout << "got a dn2 that was a nan at: idx = " << idx << " and i = " << i << std::endl;
                }
                // increment error on that bin with the square of error on event (dn)^2
                L1XE50CorrectedToZBErrors[i][idx] = L1XE50CorrectedToZBErrors[i][idx] + dn2;
                ZBErrors[i][idx] = ZBErrors[i][idx] + pow(*HLT_noalg_zb_L1ZB_prescale,2);
                RootZBErrVersMyErrL2Norm[i][idx] = RootZBErrVersMyErrL2Norm[i][idx] + pow(*HLT_noalg_zb_L1ZB_prescale,2);
            }
        }
   }
   return kTRUE;
}//}}}
void CorrectL1XE50toZB::Terminate(){//{{{
    // do errors correctly
    Double_t sumOfSquareDeviations = 0.0;
    for ( int i = 0 ; i < Number_Mu_Bins ; i++ ){
        for ( int j = 0 ; j < met_dist_nbins ; j++ ){
            //std::cout << L1XE50CorrectedToZBErrors[i][j] << " ";
            if (L1XE50CorrectedToZBErrors[i][j] == 0 && ((TH1D*)HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution->At(i))->GetBinContent( j ) != 0 ){
                std::cout << "Got zero error, but nonzero number of entries in corrected bin" << std::endl;
                std::cout << "At i= " << i << " and j = " << j << std::endl;
            }
            ((TH1D*)HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution->At(i))->SetBinError( j , TMath::Sqrt(L1XE50CorrectedToZBErrors[i][j]) );
            sumOfSquareDeviations = sumOfSquareDeviations + pow(TMath::Sqrt(RootZBErrVersMyErrL2Norm[i][j]) - 
                    ((TH1D*)HLT_ZB_L1ZB_MET_Distributions_by_Mubin->At(i))->GetBinError(j),2);
        }
    }
	// Relative Normalization
    TH1D* zb_dist;
    TH1D* l1xe50_corrected_zb_dist;
    for (int i = 0 ;i < Number_Mu_Bins ; i++ ) {
        // get histograms
        zb_dist = ((TH1D*)(HLT_ZB_L1ZB_MET_Distributions_by_Mubin->At(i)));
        l1xe50_corrected_zb_dist = ((TH1D*)(HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution->At(i)));
        for (int j = 0 ; j < Number_Scale_Factor_Samples ; j++ ){
            // determine j dependence on samples
            int bin_number = Normalization_Bin_Number[i] + j * 1;
            // compute f_i's, how to pick the samples determines j dependency of rhs here
            L1XE50Scale_Factors[i][j] = zb_dist->GetBinContent(bin_number) / 
                l1xe50_corrected_zb_dist->GetBinContent(bin_number); // shift bin number by 1 for each sample; 5 GeV shift
            // compute (sigma_i)^2's
            L1XE50Scale_Factor_Errors[i][j] = pow(L1XE50Scale_Factors[i][j],2) *
                ( pow( L1XE50CorrectedToZBErrors[i][bin_number] / 
                      l1xe50_corrected_zb_dist->GetBinContent(bin_number) ,2) +
                  pow( zb_dist->GetBinError(bin_number) / 
                      zb_dist->GetBinContent(bin_number) ,2)
                  );
        }
        // compute f_mle
        Double_t numerator = 0.0;
        Double_t denominator = 0.0;
        for (int j = 0 ; j < Number_Scale_Factor_Samples ; j++ ){
            if (!(isnan(L1XE50Scale_Factors[i][j]))&&!(isnan(L1XE50Scale_Factor_Errors[i][j]))&&!(L1XE50Scale_Factor_Errors[i][j]==0)&&!(isnan(L1XE50Scale_Factor_Errors[i][j]))&&!(L1XE50Scale_Factor_Errors[i][j]==0)){
                numerator = numerator + (L1XE50Scale_Factors[i][j] / L1XE50Scale_Factor_Errors[i][j]); // these errs are already squared
                denominator = denominator + (1./L1XE50Scale_Factor_Errors[i][j]);
            }else{
                std::cout << "\nSomething wrong with scale factor j = " << j << " in mubin i = " << i << 
                    ". skipping..." << std::endl;
                std::cout << "L1XE50Scale_Factors[i][j] = " << L1XE50Scale_Factors[i][j] << 
                    "\tL1XE50Scale_Factor_Errors[i][j] = " << L1XE50Scale_Factor_Errors[i][j] << "\n" << std::endl;
            }
        }
        Double_t f_mle = numerator / denominator;
        std::cout << "L1XE50 Scale factor: " << i << " = " << f_mle << std::endl;
        (l1xe50_corrected_zb_dist)->Scale( f_mle );
    }
}//}}}
void CorrectL1XE50toZB::Write( TString fname ){//{{{
    TFile* mu_analysis_file = TFile::Open("mu_analysis.root","UPDATE");
    if ( mu_analysis_file->IsOpen() ){
            std::cout << "File opened successfully" << std::endl;
            HLT_ZB_L1ZB_MET_Distributions_by_Mubin->Write("hlt_zb_l1zb_met_distributions",TObject::kSingleKey | TObject::kWriteDelete);
            HLT_ZB_L1XE30_MET_Distributions_by_Mubin->Write("hlt_zb_l1xe30_met_distributions",TObject::kSingleKey | TObject::kWriteDelete);
            HLT_ZB_L1XE50_MET_Distributions_by_Mubin->Write("hlt_zb_l1xe50_met_distributions",TObject::kSingleKey | TObject::kWriteDelete);
            HLT_ZB_L1XE30_Corrected_to_ZB_MET_Distribution->Write("hlt_zb_l1xe30_corrected_zb_met_distributions",TObject::kSingleKey | TObject::kWriteDelete);
            HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution->Write("hlt_zb_l1xe50_corrected_zb_met_distributions",TObject::kSingleKey | TObject::kWriteDelete);
            L1XE30_Efficiency_Objects->Write("l1xe30_efficiency_objects",TObject::kSingleKey | TObject::kWriteDelete);
            L1XE50_Efficiency_Objects->Write("l1xe50_efficiency_objects",TObject::kSingleKey | TObject::kWriteDelete);
            L1XE30_Efficiency_Fit_Objects->Write("l1xe30_efficiency_fit_objects",TObject::kSingleKey | TObject::kWriteDelete);
            L1XE50_Efficiency_Fit_Objects->Write("l1xe50_efficiency_fit_objects",TObject::kSingleKey | TObject::kWriteDelete);
            std::cout << "All folders written" << std::endl;
    }else{
        std::cout << "Unable to open file" << std::endl;
    }

    mu_analysis_file->Close();
    std::cout << "File Closed" << std::endl;
}//}}}
