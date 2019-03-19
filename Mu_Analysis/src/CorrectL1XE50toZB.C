#define CorrectL1XE50toZB_cxx
#include "CorrectL1XE50toZB.h"
#include <math.h>
ClassImp(CorrectL1XE50toZB);
void CorrectL1XE50toZB::UpdateFitParameters(){//{{{
    // getting these parameters needs to happen before process, but after construction
    // get values of efficiency fit parameters
   for (int i = 0 ; i < Number_Mu_Bins; i++){
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
   if ( isHLT_zb_L1XE50() && isGoodRun() ){
       for ( int i = 0 ; i < Number_Mu_Bins ; i++ ) {
           if ( inMuRange( Mu_Values[i] , Mu_Values[i+1] )){
                ((TH1F*)HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution->At(i))->Fill( *cell_met , ComputeWeight( ((TF1*)L1XE30_Efficiency_Fit_Objects->At(i)), ((TF1*)L1XE50_Efficiency_Fit_Objects->At(i)) ) );
                // find the index of bin that this event falls into
                Int_t idx = ((TH1F*)HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution->At(i))->GetBin( *cell_met );
                // error on the estimate of efficiency (de)
                Double_t deXE30 = TeffFitErr( *cell_met , L1XE30fitPars[i][0] , L1XE30fitPars[i][1] , L1XE30fitPars[i][2] , 
                            L1XE30fitParsErrs[i][0] , L1XE30fitParsErrs[i][1] , L1XE30fitParsErrs[i][2] , 30.0 );
                Double_t deXE50 = TeffFitErr( *cell_met , L1XE50fitPars[i][0] , L1XE50fitPars[i][1] , L1XE50fitPars[i][2] , 
                            L1XE50fitParsErrs[i][0] , L1XE50fitParsErrs[i][1] , L1XE50fitParsErrs[i][2] , 50.0 );
                // compute error on event: dn^2 = (P /(e1 * e2))^2*((de1/e1)^2+(de2/e2)^2); computeweight is P / (e1 * e2)
                Double_t dn2 = pow(ComputeWeight( ((TF1*)L1XE30_Efficiency_Fit_Objects->At(i)),((TF1*)L1XE50_Efficiency_Fit_Objects->At(i)) ),2) *
                    (pow(deXE30/(((TF1*)L1XE30_Efficiency_Fit_Objects->At(i))->Eval(*cell_met)),2) + pow(deXE50/(((TF1*)L1XE50_Efficiency_Fit_Objects->At(i))->Eval(*cell_met)),2));
                // increment error on that bin with the square of error on event (dn)^2
                L1XE50CorrectedToZBErrors[i][idx] = L1XE50CorrectedToZBErrors[i][idx] + dn2;
            }
        }
   }
   return kTRUE;
}//}}}
void CorrectL1XE50toZB::Terminate(){//{{{
    // do errors correctly
    for ( int i = 0 ; i < Number_Mu_Bins ; i++ ){
        for ( int j = 0 ; j < met_dist_nbins ; j++ ){
            ((TH1F*)HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution->At(i))->SetBinError( j , TMath::Sqrt(L1XE50CorrectedToZBErrors[i][j]) );
        }
    }
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
            HLT_ZB_L1ZB_MET_Distributions_by_Mubin->Write("hlt_zb_l1zb_met_distributions",TObject::kSingleKey | TObject::kWriteDelete);
            HLT_ZB_L1XE30_MET_Distributions_by_Mubin->Write("hlt_zb_l1xe30_met_distributions",TObject::kSingleKey | TObject::kWriteDelete);
            HLT_ZB_L1XE30_Corrected_to_ZB_MET_Distribution->Write("hlt_zb_l1xe30_corrected_zb_met_distributions",TObject::kSingleKey | TObject::kWriteDelete);
            HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution->Write("hlt_zb_l1xe50_corrected_zb_met_distributions",TObject::kSingleKey | TObject::kWriteDelete);
            L1XE30_Efficiency_Objects->Write("l1xe30_efficiency_objects",TObject::kSingleKey | TObject::kWriteDelete);
            L1XE50_Efficiency_Objects->Write("l1xe50_efficiency_objects",TObject::kSingleKey | TObject::kWriteDelete);
            L1XE30_Efficiency_Fit_Objects->Write("l1xe30_efficiency_fit_objects",TObject::kSingleKey | TObject::kWriteDelete);
            L1XE50_Efficiency_Fit_Objects->Write("l1xe50_efficiency_fit_objects",TObject::kSingleKey | TObject::kWriteDelete);
    }else{
        printf("Unable to open file\n");
    }

    mu_analysis_file->Close();
}//}}}
