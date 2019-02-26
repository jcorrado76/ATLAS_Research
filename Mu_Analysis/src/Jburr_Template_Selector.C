#define Jburr_Template_Selector_cxx
#include "Jburr_Template_Selector.h"
#if !defined(__CINT__)
ClassImp(Jburr_Template_Selector);
#endif
Bool_t Jburr_Template_Selector::isGoodRun(){ //{{{
    // return true if the event is not any of the bad run numbers
    return (*RunNumber != 330203 && *RunNumber != 331975 && *RunNumber != 334487);
} // }}}
Bool_t Jburr_Template_Selector::isHLT_zb_L1ZB(){ //{{{
    // return true if the event passed hlt noalg , l1 zb
    return (*HLT_noalg_zb_L1ZB_passed);
} //}}}
Bool_t Jburr_Template_Selector::isHLT_zb_L1XE30(){ //{{{
    // return true if is hlt passnoalg and l1 xe30
    return (*HLT_noalg_L1XE30_passed);
} //}}}
Bool_t Jburr_Template_Selector::isHLT_zb_L1XE50(){ //{{{
    // return true if is hlt passnoalg and l1 xe50
    return (*L1_XE50_passed);
} //}}}
Bool_t Jburr_Template_Selector::inMuRange( Float_t a , Float_t b ){ //{{{
    // return true if in local mu bin
    return ( *InTimePileup > a && *InTimePileup < b );
} //}}}
Double_t Jburr_Template_Selector::fitFunction(Double_t *x , Double_t *par ){//{{{
    // return the value of the fitfunction evaluted at x with the given par
    // TODO: take l1cut as a parameter, but this actually messes up root's system for generating the functor to pass
    // this function to the generateFitFunction routine. so need to find a workaround
    Double_t l1cut = 30.0;
    Double_t fitval = (1./2.)*(1.+TMath::Erf((par[0]*x[0]+par[1]-l1cut)/(par[2]*TMath::Sqrt(2.))));
    return fitval;
}//}}}
TF1* Jburr_Template_Selector::generateFitFunction(TEfficiency* teff_obj, float gevMax, float initial_slope, float initial_intercept, float initial_sigma , Bool_t verbose ){//{{{
    // return a fit function object whose parameters have been set

    TF1 *fitErrorFunction = new TF1( "fitFunction" , fitFunction , 0.0 , gevMax , 3 );
    fitErrorFunction->SetParameter(0, initial_slope);
    fitErrorFunction->SetParameter(1, initial_intercept);
    fitErrorFunction->SetParameter(2, initial_sigma);
    //initializing parameters reasonably is important because it is a maximum likelihood fit
    fitErrorFunction->SetParNames("Slope","Translation","Sigma");
    //"R" tells the fit function from BinomialEfficiency::Fit to use the range of the TF1 as the fitting range
    teff_obj->Fit( fitErrorFunction  , "R+");

    if (verbose){
        std::cout << "Value of fit for a: " << fitErrorFunction->GetParameter(0) << std::endl;
        std::cout << "Value of error on a: " << fitErrorFunction->GetParError(0) << std::endl;
        std::cout << "Value of fit for b: " << fitErrorFunction->GetParameter(1) << std::endl;
        std::cout << "Value of error on b: " << fitErrorFunction->GetParError(1) << std::endl;
        std::cout << "Value of fit for sigma: " << fitErrorFunction->GetParameter(2) << std::endl;
        std::cout << "Value of error on sigma: " << fitErrorFunction->GetParError(2) << std::endl;
    }
    return fitErrorFunction;
}//}}}
Double_t Jburr_Template_Selector::ComputeWeight(TF1* fitFunc, TF1* fitFunc2 )//{{{
{
    Float_t numerator = *HLT_noalg_L1XE30_prescale;
    Double_t denominator = 1.;
    if (!fitFunc2){
        denominator = fitFunc->Eval( *cell_met );
    }else{
        denominator = fitFunc->Eval( *cell_met ) * fitFunc2->Eval( *cell_met );
    }
    return numerator / denominator;
}//}}}
void Jburr_Template_Selector::Init(TTree *tree)//{{{
{
   fReader.SetTree(tree);
}//}}}
Bool_t Jburr_Template_Selector::Notify()//{{{
{
   return kTRUE;
}//}}}
