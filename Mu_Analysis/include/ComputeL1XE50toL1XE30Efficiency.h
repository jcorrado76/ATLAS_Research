//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun 12 11:08:28 2018 by ROOT version 6.12/06
// from TTree METTree/METTree
// found on file: ../data/totalJburrTuple.root
//////////////////////////////////////////////////////////

#ifndef ComputeL1XE50toL1XE30Efficiency_h
#define ComputeL1XE50toL1XE30Efficiency_h

#include "Jburr_Template_Selector.h"

class ComputeL1XE50toL1XE30Efficiency : public Jburr_Template_Selector {
public :
   ComputeL1XE50toL1XE30Efficiency() { }
   ~ComputeL1XE50toL1XE30Efficiency() { }
   Bool_t  Process(Long64_t entry);
   void    Terminate();
   ClassDef(ComputeL1XE50toL1XE30Efficiency,0);


   float L1XE = 50.0;
};

#endif
