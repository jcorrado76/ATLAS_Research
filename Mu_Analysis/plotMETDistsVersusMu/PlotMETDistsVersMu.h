//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun 12 11:08:28 2018 by ROOT version 6.12/06
// from TTree METTree/METTree
// found on file: ../data/totalJburrTuple.root
//////////////////////////////////////////////////////////

#ifndef PlotMETDistsVersMu_h
#define PlotMETDistsVersMu_h

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
#include <vector>
#include <THStack.h>

class PlotMETDistsVersMu : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain
   TH1F*            MET_Datamu0thru10 = 0;
   TH1F*            MET_Datamu10thru20 = 0;
   TH1F*            MET_Datamu20thru30 = 0;
   TH1F*            MET_Datamu30thru40 = 0;
   TH1F*            MET_Datamu40thru50 = 0;
   TH1F*            MET_Datamu50thru60 = 0;
   TH1F*            MET_Datamu60thru70 = 0;
   TString alg_name = "cell.met"; 
    Int_t nbins = 1000;
    Float_t gevLow = 0.0;
    Float_t gevHigh = 100.0;
    TString xaxisTitle = alg_name + " [GeV]";
    TString yaxisTitle = "Number of Entries";
    TCanvas* mycanv = new TCanvas("MET_AlgMuSlices", "MET Slices in Mu");
    THStack* muSlicesStack = new THStack("muStack","MET Hists in Mu Slices After Removing Runs 33023, 331975, and 334487");

   // Readers to access the data (delete the ones you do not need).{{{
   TTreeReaderValue<UInt_t> RunNumber = {fReader, "RunNumber"};
   TTreeReaderValue<ULong64_t> EventNumber = {fReader, "EventNumber"};
   TTreeReaderValue<Float_t> InTimePileup = {fReader, "InTimePileup"};
   TTreeReaderValue<Float_t> OutOfTimePileup = {fReader, "OutOfTimePileup"};
   TTreeReaderValue<Float_t> MET_Data = {fReader, alg_name };
   TTreeReaderValue<Bool_t> HLT_noalg_zb_L1ZB_passed = {fReader, "HLT_noalg_zb_L1ZB.passed"};
   TTreeReaderValue<Bool_t> HLT_noalg_L1XE30_passed = {fReader, "HLT_noalg_L1XE30.passed"};


   PlotMETDistsVersMu(TTree * =0) { }
   virtual ~PlotMETDistsVersMu() { }
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
   Bool_t isGoodRun();
   Bool_t passedL1ZB();
   Boolt_ isPassnoAlg30();

   ClassDef(PlotMETDistsVersMu,0);

};
// }}}

#endif

