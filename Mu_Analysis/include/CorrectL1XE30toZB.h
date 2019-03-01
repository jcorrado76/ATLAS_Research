#ifndef CorrectL1XE30toZB_h
#define CorrectL1XE30toZB_h
#include "Jburr_Template_Selector.h"
class CorrectL1XE30toZB : public Jburr_Template_Selector {
public :
   CorrectL1XE30toZB() { }
   ~CorrectL1XE30toZB() { }
   // copy constructor {{{
   CorrectL1XE30toZB( const Jburr_Template_Selector* rhs ){
   HLT_ZB_L1ZB_MET_Distributions_by_Mubin = rhs->Get_Met_Distributions_By_Mu_Bin();
   L1XE30_Efficiency_Fit_Objects = rhs->Get_L1XE30_Efficiency_Fit_Objects();
   }//}}}
    // TODO: eventually the copy constructor will replace what begin does
   void    Begin(TTree *tree);
   Bool_t  Process(Long64_t entry);
   void    Terminate();
   ClassDef(CorrectL1XE30toZB,0);
};
#endif
