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

class ComputeL1XE50toL1XE30Efficiency : public TSelector {
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

    Float_t gevLow = 0.0;
    Float_t gevHigh = 300.0;
    Float_t met_dist_binwidth = 1.0;
    Float_t efficiency_bin_width = 20.0; //want 20 GeV bins
    Int_t met_dist_nbins = (gevHigh - gevLow) / met_dist_binwidth; // compute nbins as function of preferred width
    Int_t efficiency_nbins = (gevHigh - gevLow) / efficiency_bin_width;

    Float_t Mu_Values[Number_Mu_Bins+1] = {0.0};
    Int_t Colors[Number_Mu_Bins] = {1,2,3,4,12,6,9};
    Int_t MarkerStyles[Number_Mu_Bins] = {29,20,3,4,27,22,21};

   Float_t XE = 50.0; // L1 cut
   TString Alg_Name = "CELL MET";
   TString zb_alg_name = "cell.met";
   TString l1_alg_name = "L1.met";
    // set titles and axis labels.
    TString efficiency_title = zb_alg_name + " Efficiency";
    TString efficiency_xaxis = zb_alg_name + " [GeV]";
    TString efficiency_yaxis = "efficiency";

    TString met_dist_xaxis = zb_alg_name + " [GeV]";
    TString met_dist_yaxis = "Number of Entries";

   TTreeReaderValue<UInt_t> RunNumber = {fReader, "RunNumber"};
   TTreeReaderValue<ULong64_t> EventNumber = {fReader, "EventNumber"};
   TTreeReaderValue<Float_t> InTimePileup = {fReader, "InTimePileup"};

   TTreeReaderValue<Float_t> MET_Data = {fReader, zb_alg_name };
   TTreeReaderValue<Float_t> L1_MET = {fReader, l1_alg_name};

   TTreeReaderValue<Bool_t> HLT_noalg_zb_L1ZB_passed = {fReader, "HLT_noalg_zb_L1ZB.passed"};
   TTreeReaderValue<Bool_t> HLT_noalg_L1XE30_passed = {fReader, "HLT_noalg_L1XE30.passed"};
   TTreeReaderValue<Float_t> HLT_noalg_zb_L1ZB_prescale = {fReader, "HLT_noalg_zb_L1ZB.prescale"};
   TTreeReaderValue<Float_t> HLT_noalg_L1XE30_prescale = {fReader, "HLT_noalg_L1XE30.prescale"};


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
