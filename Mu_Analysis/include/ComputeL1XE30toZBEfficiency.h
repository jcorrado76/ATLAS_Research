#ifndef ComputeL1XE30toZBEfficiency_h
#define ComputeL1XE30toZBEfficiency_h
#include "Jburr_Template_Selector.h"
class ComputeL1XE30toZBEfficiency : public Jburr_Template_Selector {
public :
   ComputeL1XE30toZBEfficiency(){};
   ~ComputeL1XE30toZBEfficiency() { };
   Bool_t  Process(Long64_t entry);
   void    Terminate();
   ClassDef(ComputeL1XE30toZBEfficiency,0);

   const float L1XE = 30.0;
};
