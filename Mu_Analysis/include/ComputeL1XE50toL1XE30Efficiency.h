//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun 12 11:08:28 2018 by ROOT version 6.12/06
// from TTree METTree/METTree
// found on file: ../data/totalJburrTuple.root
//////////////////////////////////////////////////////////

#ifndef ComputeL1XE50toL1XE30Efficiency_h
#define ComputeL1XE50toL1XE30Efficiency_h

#include "Jburr_Template_Selector.h"
#include "CorrectL1XE30toZB.h"

class ComputeL1XE50toL1XE30Efficiency : public Jburr_Template_Selector {
public :
   ComputeL1XE50toL1XE30Efficiency() { }
   ~ComputeL1XE50toL1XE30Efficiency() { }
   ComputeL1XE50toL1XE30Efficiency( const CorrectL1XE30toZB* rhs ): Jburr_Template_Selector(rhs){}
   Bool_t  Process(Long64_t entry);
   void    Terminate();
   ClassDef(ComputeL1XE50toL1XE30Efficiency,0);


   float L1XE = 50.0;
};

#endif
