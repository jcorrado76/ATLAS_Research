#ifndef CorrectL1XE50ToZB_h
#define CorrectL1XE50ToZB_h

#include "Jburr_Template_Selector.h"

class CorrectL1XE50toZB : public Jburr_Template_Selector {
public :
   CorrectL1XE50toZB(){ 
       for (int i = 0 ; i < Number_Mu_Bins; i++){
           Corrected_Name.Form("L1XE50CorrectedToZBmubin%d", i);
           Corrected_Title.Form("L1XE50 Data Corrected back to Zerobias For Actint bin %d" , i);
           HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution->Add(new TH1D( Corrected_Name , Corrected_Title , met_dist_nbins , gevLow , gevHigh ));
           ((TH1D*)HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution->At(i))->SetLineColor( Colors[i] );
       }
   }
   float L1XE = 50.0;
   void    UpdateFitParameters();
   ~CorrectL1XE50toZB() { }
   Bool_t  Process(Long64_t entry);
   void    Terminate();
   void Write( TString fname );
   ClassDef(CorrectL1XE50toZB,0);
};

#endif
