#ifndef CorrectL1XE30toZB_h
#define CorrectL1XE30toZB_h
#include "Jburr_Template_Selector.h"
class CorrectL1XE30toZB : public Jburr_Template_Selector {
public :
    float fitPars[Number_Mu_Bins][3];
    float fitParsErrs[Number_Mu_Bins][3];
   CorrectL1XE30toZB(){
   for (int i = 0 ; i < Number_Mu_Bins; i++){
       Corrected_Name.Form("L1XE30CorrectedToZBmubin%d" , i);
       Corrected_Title.Form("L1XE30 Data Corrected back to Zerobias For Actint bin %d", i);
       HLT_ZB_L1XE30_Corrected_to_ZB_MET_Distribution->Add(new TH1F( Corrected_Name , Corrected_Title , met_dist_nbins , gevLow , gevHigh ));
       ((TH1F*)HLT_ZB_L1XE30_Corrected_to_ZB_MET_Distribution->At(i))->SetLineColor( Colors[i] );

       // TODO: these haven't been passed to this object at the time of construction. So this needs to happen
       // before process but after constructor. 
       std::cout << ((TF1*)L1XE30_Efficiency_Fit_Objects->At(i))->GetName() << std::endl;
       //std::cout << ((TF1*)L1XE30_Efficiency_Fit_Objects->At(i))->GetParameter( 0 ) << std::endl;
       fitPars[i][0] = ((TF1*)L1XE30_Efficiency_Fit_Objects->At(i))->GetParameter( 0 );
       fitPars[i][1] = ((TF1*)L1XE30_Efficiency_Fit_Objects->At(i))->GetParameter( 1 );
       fitPars[i][2] = ((TF1*)L1XE30_Efficiency_Fit_Objects->At(i))->GetParameter( 2 );

       // get values of uncertainties on efficiency fit parameters
       fitParsErrs[i][0] = ((TF1*)L1XE30_Efficiency_Fit_Objects->At(i))->GetParError( 0 );
       fitParsErrs[i][1] = ((TF1*)L1XE30_Efficiency_Fit_Objects->At(i))->GetParError( 1 );
       fitParsErrs[i][2] = ((TF1*)L1XE30_Efficiency_Fit_Objects->At(i))->GetParError( 2 );
   }
   float L1XE = 30.0;
}
   ~CorrectL1XE30toZB() { }
   void    Begin(TTree *tree);
   Bool_t  Process(Long64_t entry);
   void    Terminate();
   ClassDef(CorrectL1XE30toZB,0);
};
#endif
