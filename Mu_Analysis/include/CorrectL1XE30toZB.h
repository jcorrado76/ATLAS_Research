#ifndef CorrectL1XE30toZB_h
#define CorrectL1XE30toZB_h
#include "Jburr_Template_Selector.h"
class CorrectL1XE30toZB : public Jburr_Template_Selector {
public :
   CorrectL1XE30toZB(){
       std::cout << "Calling the CorrectL1XE30toZB Constructor" << std::endl;
       for (int i = 0 ; i < Number_Mu_Bins; i++){
           Corrected_Name.Form("L1XE30CorrectedToZBmubin%d" , i);
           Corrected_Title.Form("L1XE30 Data Corrected back to Zerobias For Actint bin %d", i);
           HLT_ZB_L1XE30_Corrected_to_ZB_MET_Distribution[i] = new TH1F( Corrected_Name , Corrected_Title , met_dist_nbins , gevLow , gevHigh );
           HLT_ZB_L1XE30_Corrected_to_ZB_MET_Distribution[i]->SetLineColor( Colors[i] );
       }
}
   ~CorrectL1XE30toZB() { }
   Bool_t  Process(Long64_t entry);
   void    Terminate();
   ClassDef(CorrectL1XE30toZB,0);
};
#endif
