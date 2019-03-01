#ifndef CorrectL1XE30toZB_h
#define CorrectL1XE30toZB_h
#include "Jburr_Template_Selector.h"
#include "ComputeL1XE30toZBEfficiency.h"
class CorrectL1XE30toZB : public Jburr_Template_Selector {
public :
   CorrectL1XE30toZB() { }
   ~CorrectL1XE30toZB() { }
   CorrectL1XE30toZB( const ComputeL1XE30toZBEfficiency* rhs ): Jburr_Template_Selector(rhs){}
   void    Begin(TTree *tree);
   Bool_t  Process(Long64_t entry);
   void    Terminate();
   ClassDef(CorrectL1XE30toZB,0);
};
#endif
