//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun 12 21:21:22 2018 by ROOT version 6.12/06
// from TTree METTree/METTree
// found on file: ../data/totalJburrTuple.root
//////////////////////////////////////////////////////////

#ifndef L1XEefficiencySelector_h
#define L1XEefficiencySelector_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TEfficiency.h>
#include <TStyle.h>
#include <TString.h>
#include <TCanvas.h>
#include <THStack.h>
#include <TLegend.h>

// Headers needed by this particular selector
#include <vector>

class L1XEefficiencySelector : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain
   Float_t XE = 30.0; // L1 cut
    Float_t gevLow = 0.0;
    Float_t gevHigh = 300.0;
    Float_t width = 20.0; //want 20 GeV bins
    Int_t nbins = (gevHigh - gevLow) / width; // compute nbins as function of preferred width
   TString alg_name = "HLT_noalg_L1XE30.prescale"; // alg for which to compute efficiency 
   TString zb_alg_name = "HLT_noalg_zb_L1ZB.prescale";
   // initialize pointers to 0
   TEfficiency*            MET_Algmu0thru10Efficiency = 0;
   TEfficiency*            MET_Algmu10thru20Efficiency = 0;
   TEfficiency*            MET_Algmu20thru30Efficiency = 0;
   TEfficiency*            MET_Algmu30thru40Efficiency = 0;
   TEfficiency*            MET_Algmu40thru50Efficiency = 0;
   TEfficiency*            MET_Algmu50thru60Efficiency = 0;
   TEfficiency*            MET_Algmu60thru70Efficiency = 0;

   // Readers to access the data (delete the ones you do not need).{{{
   TTreeReaderValue<UInt_t> RunNumber = {fReader, "RunNumber"};
   TTreeReaderValue<UInt_t> LumiBlock = {fReader, "LumiBlock"};
   TTreeReaderValue<Float_t> InTimePileup = {fReader, "InTimePileup"};
   TTreeReaderValue<Float_t> OutOfTimePileup = {fReader, "OutOfTimePileup"};

   TTreeReaderValue<Float_t> cell_met = {fReader, "cell.met"};
   // this is the reference point what we want efficiency as a function of 
   TTreeReaderValue<Float_t> HLT_noalg_zb_L1ZB_prescale = {fReader, "HLT_noalg_zb_L1ZB.prescale"};
   // this is the algorithm we want to know the efficiency of 
   TTreeReaderValue<Float_t> HLT_noalg_L1XE30_prescale = {fReader, "HLT_noalg_L1XE30.prescale"};

   TTreeReaderValue<Float_t> L1_MET = {fReader, "L1.met"};

   L1XEefficiencySelector(TTree * /*tree*/ =0) { }
   virtual ~L1XEefficiencySelector() { }
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

   ClassDef(L1XEefficiencySelector,0);

};//}}}

#endif

