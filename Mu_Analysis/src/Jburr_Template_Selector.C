#define Jburr_Template_Selector_cxx
#include "Jburr_Template_Selector.h"
#if !defined(__CINT__)
ClassImp(Jburr_Template_Selector);
#endif
void Jburr_Template_Selector::Begin(TTree *){} 
Bool_t Jburr_Template_Selector::Process(Long64_t entry)//{{{
{
   fReader.SetLocalEntry(entry);
   return kTRUE;
}//}}}
void Jburr_Template_Selector::Terminate(){}
void Jburr_Template_Selector::SlaveBegin(TTree*){TString option = GetOption();}
void Jburr_Template_Selector::SlaveTerminate(){}
void Jburr_Template_Selector::Init(TTree *tree){fReader.SetTree(tree);}
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
TF1* Jburr_Template_Selector::generateFitFunction(TEfficiency* teff_obj, float L1XE , int i ,
        float initial_slope, float initial_intercept, float initial_sigma ,  Bool_t verbose ){//{{{
    // return a fit function object whose parameters have been set

    TF1* fitErrorFunction = new TF1();
    if ( L1XE == 30.0 ){
        fitErrorFunction = new TF1( "fitFunction" , L1XE30fitFunction , gevLow , gevHigh , 3);
    }else{
        fitErrorFunction = new TF1( "fitFunction" , L1XE50fitFunction , gevLow , gevHigh , 3);
    }

    fitErrorFunction->SetLineColor( Colors[i] );
    //TODO: use a class the static fitting function with an evsl method

    fitErrorFunction->SetParameters(initial_slope, initial_intercept , initial_sigma);
    //initializing parameters reasonably is important because it is a maximum likelihood fit
    fitErrorFunction->SetParNames("Slope","Intercept","Sigma");

    //"R" tells the fit function from BinomialEfficiency::Fit to use the range of the TF1 as the fitting range
    teff_obj->Fit( fitErrorFunction  , "R+");

    if (verbose){
        std::cout << "Value of fit for m: " << fitErrorFunction->GetParameter(0) << std::endl;
        std::cout << "Value of error on m: " << fitErrorFunction->GetParError(0) << std::endl;
        std::cout << "Value of fit for b: " << fitErrorFunction->GetParameter(1) << std::endl;
        std::cout << "Value of error on b: " << fitErrorFunction->GetParError(1) << std::endl;
        std::cout << "Value of fit for sigma: " << fitErrorFunction->GetParameter(2) << std::endl;
        std::cout << "Value of error on sigma: " << fitErrorFunction->GetParError(2) << std::endl;
    }
    return fitErrorFunction;
}//}}}
Double_t Jburr_Template_Selector::ComputeWeight(TF1* fitFunc, TF1* fitFunc2 )//{{{
{
    Double_t factor = 1.;
    if (!fitFunc2){
        // inside correct l1xe30 to zb
        factor = *HLT_noalg_L1XE30_prescale / fitFunc->Eval( *cell_met );
    }else{
        // inside correct l1xe50 to zb
        factor = (*L1_XE50_prescale ) / 
            (fitFunc->Eval( *cell_met ) * fitFunc2->Eval( *cell_met ));
    }
    return factor;
}//}}}
double Jburr_Template_Selector::L1XE30fitFunction(double *x , double *par){//{{{
    /*
     * Parameter 0 - initial slope
     * Parameter 1 - initial intercept
     * Parameter 2 - initial sigma
     */

    double fitval = (1./2.)*(1.+TMath::Erf((par[0]*x[0]+par[1]-30.0)/(par[2]*TMath::Sqrt(2.))));
    return fitval;
}//}}}
double Jburr_Template_Selector::L1XE50fitFunction(double *x , double *par){//{{{
    /*
     * Parameter 0 - initial slope
     * Parameter 1 - initial intercept
     * Parameter 2 - initial sigma
     */

    double fitval = (1./2.)*(1.+TMath::Erf((par[0]*x[0]+par[1]-50.0)/(par[2]*TMath::Sqrt(2.))));
    return fitval;
}//}}}
Double_t Jburr_Template_Selector::TeffFitErr( Double_t x , Double_t m , Double_t b , Double_t sigma , Double_t dm ,Double_t db ,Double_t ds ,Double_t l1xe ){//{{{
    Double_t z = ( b + m * x - l1xe ) / ( TMath::Sqrt(2) * sigma );
    Double_t prefactor = 1. / TMath::Sqrt( 2 * TMath::Pi() * pow(sigma ,2));
    Double_t exp = TMath::Exp( -pow(z,2) );
    Double_t factor = TMath::Sqrt( pow(dm * x,2) + pow(db,2) + pow(ds * (( m * x + b - l1xe ) / ( sigma ) ),2));
    return prefactor * exp * factor;
}//}}}
Bool_t Jburr_Template_Selector::Notify(){return kTRUE;}
