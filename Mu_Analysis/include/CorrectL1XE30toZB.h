#ifndef CorrectL1XE30toZB_h
#define CorrectL1XE30toZB_h
#include "Jburr_Template_Selector.h"
class CorrectL1XE30toZB : public Jburr_Template_Selector {
public :
   CorrectL1XE30toZB(){
       for (int i = 0 ; i < Number_Mu_Bins; i++){
           Corrected_Name.Form("L1XE30CorrectedToZBmubin%d" , i);
           Corrected_Title.Form("L1XE30 Data Corrected back to Zerobias For %d < #mu < %d", i*10,(i+1)*10);
           HLT_ZB_L1XE30_Corrected_to_ZB_MET_Distribution->Add(new TH1D( Corrected_Name , Corrected_Title , met_dist_nbins , gevLow , gevHigh ));
           ((TH1D*)HLT_ZB_L1XE30_Corrected_to_ZB_MET_Distribution->At(i))->SetLineColor( Colors[i] );
       }
    }
   float L1XE = 30.0;
   ~CorrectL1XE30toZB() { }
   void    UpdateFitParameters();
   Bool_t  Process(Long64_t entry);
   void    Terminate();
   ClassDef(CorrectL1XE30toZB,0);
};
#endif
