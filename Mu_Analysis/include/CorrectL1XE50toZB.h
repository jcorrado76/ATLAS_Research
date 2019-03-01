#ifndef CorrectL1XE50ToZB_h
#define CorrectL1XE50ToZB_h

#include "Jburr_Template_Selector.h"

class CorrectL1XE50toZB : public Jburr_Template_Selector {
public :
   CorrectL1XE50toZB() { }
   ~CorrectL1XE50toZB() { }
   // copy constructor
   CorrectL1XE50toZB( const Jburr_Template_Selector* rhs ){
   HLT_ZB_L1ZB_MET_Distributions_by_Mubin = rhs->Get_HLT_ZB_L1ZB_MET_Distributions_by_Mubin();
   L1XE30_Efficiency_Fit_Objects = rhs->Get_L1XE30_Efficiency_Fit_Objects();
   L1XE50_Efficiency_Fit_Objects = rhs->Get_L1XE50_Efficiency_Fit_Objects();
   }
   void    Begin(TTree *tree);
   Bool_t  Process(Long64_t entry);
   void    Terminate();
   ClassDef(CorrectL1XE50toZB,0);
};

#endif
