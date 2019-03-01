//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jul 11 09:26:49 2018 by ROOT version 6.15/01
// from TChain METTree/jburrntuplechain
//////////////////////////////////////////////////////////

#ifndef CorrectL1XE50ToZB_h
#define CorrectL1XE50ToZB_h

#include "Jburr_Template_Selector.h"

class CorrectL1XE50toZB : public Jburr_Template_Selector {
public :
   CorrectL1XE50toZB() { }
   ~CorrectL1XE50toZB() { }
   // copy constructor
   CorrectL1XE50toZB( const CorrectL1XE50toZB* rhs ){}
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
   ClassDef(CorrectL1XE50toZB,0);
};

#endif
