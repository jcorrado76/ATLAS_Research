#ifndef CorrectL1XE50ToZB_h
#define CorrectL1XE50ToZB_h

#include "Jburr_Template_Selector.h"
#include "ComputeL1XE50toL1XE30Efficiency.h"

class CorrectL1XE50toZB : public Jburr_Template_Selector {
public :
   CorrectL1XE50toZB() { }
   ~CorrectL1XE50toZB() { }
   CorrectL1XE50toZB( const ComputeL1XE50toL1XE30Efficiency* rhs ): Jburr_Template_Selector(rhs){}
   void    Begin(TTree *tree);
   Bool_t  Process(Long64_t entry);
   void    Terminate();
   ClassDef(CorrectL1XE50toZB,0);
};

#endif
