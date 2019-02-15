//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun 12 11:08:28 2018 by ROOT version 6.12/06
// from TTree METTree/METTree
// found on file: ../data/totalJburrTuple.root
//////////////////////////////////////////////////////////

#ifndef ComputeL1XE50toL1XE30Efficiency_h
#define ComputeL1XE50toL1XE30Efficiency_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TLegend.h>
#include <TString.h>
#include <TEfficiency.h>
#include <TF1.h>
#include "Jburr_Template_Selector.h"

class ComputeL1XE50toL1XE30Efficiency : public Jburr_Template_Selector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

    const static Int_t Number_Mu_Bins = 7;
   TH1F* Met_Distributions_By_Mu_Bin[Number_Mu_Bins];
   TH1F* Normalized_Met_Distributions[Number_Mu_Bins];
   TEfficiency* L1XE50_Efficiency_Objects[Number_Mu_Bins];
   TF1* L1XE50_Efficiency_Fit_Objects[Number_Mu_Bins];
   TH1F* MET_Distribution = 0;
   TEfficiency* MET_L1XE50Efficiency = 0;
   TF1* MET_L1XE50EfficiencyFit = 0;

   TTreeReaderValue<UInt_t> RunNumber = {fReader, "RunNumber"};
   TTreeReaderValue<ULong64_t> EventNumber = {fReader, "EventNumber"};
   TTreeReaderValue<Float_t> InTimePileup = {fReader, "InTimePileup"};

   TTreeReaderValue<Float_t> MET_Data = {fReader, zb_alg_name };
   TTreeReaderValue<Float_t> L1_MET = {fReader, l1_alg_name};

   ComputeL1XE50toL1XE30Efficiency() { }
   ComputeL1XE50toL1XE30Efficiency(TTree * =0) { }
   ~ComputeL1XE50toL1XE30Efficiency() { }
   Int_t   Version() const { return 2; }
   void    Begin(TTree *tree);
   void    SlaveBegin(TTree *tree);
   void    Init(TTree *tree);
   Bool_t  Notify();
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
