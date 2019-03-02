#ifndef CorrectL1XE30toZB_h
#define CorrectL1XE30toZB_h
#include "Jburr_Template_Selector.h"
class CorrectL1XE30toZB : public Jburr_Template_Selector {
public :
   CorrectL1XE30toZB() { }
   ~CorrectL1XE30toZB() { }
   void    Begin(TTree *tree);
   Bool_t  Process(Long64_t entry);
   void    Terminate();
   ClassDef(CorrectL1XE30toZB,0);
};
#endif
