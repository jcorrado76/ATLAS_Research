#ifndef Compute_Trigger_Rate_TSelector_h
#define Compute_Trigger_Rate_TSelector_h
#include <TH2.h>
#include <TStyle.h>
#include <TH1.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
class Compute_Trigger_Rate_TSelector : public TSelector {
public :
   TTreeReader     fReader;  
   TTree          *fChain = 0;   
   Int_t numRndm = 0;
   Int_t numPassL1 = 0;
   TTreeReaderValue<Float_t> metl1 = {fReader, "metl1"};
   TTreeReaderValue<Int_t> passrndm = {fReader, "passrndm"};
   Compute_Trigger_Rate_TSelector(TTree * = 0) { }
   virtual ~Compute_Trigger_Rate_TSelector() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();
   ClassDef(Compute_Trigger_Rate_TSelector,0);
};
#endif
#ifdef Compute_Trigger_Rate_TSelector_cxx
void Compute_Trigger_Rate_TSelector::Init(TTree *tree){fReader.SetTree(tree);}
Bool_t Compute_Trigger_Rate_TSelector::Notify(){return kTRUE;}
#endif // #ifdef Compute_Trigger_Rate_TSelector_cxx
