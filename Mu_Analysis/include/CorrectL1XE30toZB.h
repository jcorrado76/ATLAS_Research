//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jul 11 09:26:49 2018 by ROOT version 6.15/01
// from TChain METTree/jburrntuplechain
//////////////////////////////////////////////////////////

#ifndef CorrectL1XE30toZB_h
#define CorrectL1XE30toZB_h

#include "Jburr_Template_Selector.h"

class CorrectL1XE30toZB : public Jburr_Template_Selector {
public :
   CorrectL1XE30toZB() { }
   ~CorrectL1XE30toZB() { }
   // copy constructor
   CorrectL1XE30toZB( const Jburr_Template_Selector* rhs ){//{{{
    // we only need these collections from the computel1xe30efficiencies code
   HLT_ZB_L1ZB_MET_Distributions_by_Mubin = rhs->Get_Met_Distributions_By_Mu_Bin();
   Normalized_Met_Distributions = rhs->Get_Normalized_Met_Distributions();
   L1XE30_Efficiency_Objects = rhs->Get_L1XE30_Efficiency_Objects;
   L1XE30_Efficiency_Fit_Objects = rhs->Get_L1XE30_Efficiency_Fit_Objects();
   }//}}}
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

   ClassDef(CorrectL1XE30toZB,0);
};

#endif

