//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jul 11 09:26:49 2018 by ROOT version 6.15/01
// from TChain METTree/jburrntuplechain
//////////////////////////////////////////////////////////

#ifndef CorrectL1XE30toZB_h
#define CorrectL1XE30toZB_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TStyle.h>
#include <vector>
#include <TF1.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TPad.h>
#include <TEfficiency.h>
#include <TDirectory.h>
#include <TGaxis.h>
class CorrectL1XE30toZB : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

    const static Int_t Number_Mu_Bins = 7;
    TH1F* ZB_MET_Distributions[Number_Mu_Bins];
    TH1F* Corrected_MET_Distributions[Number_Mu_Bins];
    TF1* L1XE30_Efficiency_Fit_Objects[Number_Mu_Bins];
    TEfficiency* L1XE30_Efficiency_Objects[Number_Mu_Bins];
    TFile* mu_analysis_file = 0;

   Float_t Mu_Values[Number_Mu_Bins+1] = { 0.0 };
   Int_t Colors[Number_Mu_Bins] = {1,2,3,4,12,6,9};
   Int_t MarkerStyles[Number_Mu_Bins] = {29,20,3,4,27,22,21};
   Int_t Normalization_Bin_Numbers[Number_Mu_Bins] = {40,52,60,56,55,52,40};
   Float_t Scale_Factors[Number_Mu_Bins] = { 0.0 };

    Float_t binWidth = 1.0;
    Float_t gevLow = 0.0;
    Float_t gevHigh = 300.0;
    Int_t nbins = (gevHigh-gevLow)/binWidth;
    TString Alg_Name = "METCELL";
    TString xaxisTitle = Alg_Name + " [GeV]";
    TString yaxisTitle = "Number of Entries";
   CorrectL1XE30toZB(TTree * /*tree*/ =0) { }
   ~CorrectL1XE30toZB() { }
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

   ClassDef(CorrectL1XE30toZB,0);
};

#endif

