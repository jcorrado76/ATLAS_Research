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
   ComputeL1XE50toL1XE30Efficiency(TTree * =0) { }
   ~ComputeL1XE50toL1XE30Efficiency() { }
   Int_t   Version() const { return 2; }
   void    Begin(TTree *tree);
   void    SlaveBegin(TTree *tree);
   void    Init(TTree *tree);
   Bool_t  Process(Long64_t entry);
   Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   void    SetOption(const char *option) { fOption = option; }
   void    SetObject(TObject *obj) { fObject = obj; }
   void    SetInputList(TList *input) { fInput = input; }
   TList  *GetOutputList() const { return fOutput; }
   void    SlaveTerminate();
   void    Terminate();
   ClassDef(ComputeL1XE50toL1XE30Efficiency,0);

};

#endif
