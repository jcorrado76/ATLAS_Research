//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Nov 24 01:37:36 2017 by ROOT version 6.10/00
// from TTree tree/tree
// found on file: ../myData/ZeroBiasKF2016R307195R311481Runs51.root
//////////////////////////////////////////////////////////

#ifndef ZBKFThresh_h
#define ZBKFThresh_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include "userInfo.h"
// Headers needed by this particular selector


class ZBKFThresh : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain
    userInfo*       M_Parameters = 0; //PARAMETERS OBJECT
    TH1* AlgAHist = 0;
    TH1* AlgBHist = 0;

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Float_t> Passrndm = {fReader, "passrndm"};
   TTreeReaderValue<Float_t> AlgAMET= {fReader, };
   TTreeReaderValue<Float_t> AlgBMET = {fReader, "avint"};
   


   ZBKFThresh(TTree * /*tree*/ =0, userInfo* parameters ) { }
   virtual ~ZBKFThresh() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree, userInfo* parameters );
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

   ClassDef(ZBKFThresh,0);

};

#endif

#ifdef ZBKFThresh_cxx
void ZBKFThresh::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t ZBKFThresh::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef ZBKFThresh_cxx
