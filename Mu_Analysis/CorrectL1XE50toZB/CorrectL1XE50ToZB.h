//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jul 11 09:26:49 2018 by ROOT version 6.15/01
// from TChain METTree/jburrntuplechain
//////////////////////////////////////////////////////////

#ifndef CorrectL1XE50ToZB_h
#define CorrectL1XE50ToZB_h

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
class CorrectL1XE50ToZB : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain
    TFile* mu_analysis_file = 0;
    const static Int_t Number_Mu_Bins = 7;
   TH1F* Met_Distributions_By_Mu_Bin[Number_Mu_Bins];
   TH1F* Normalized_Met_Distributions[Number_Mu_Bins];
   TEfficiency* L1XE30_Efficiency_Objects[Number_Mu_Bins];
   TF1* L1XE30_Efficiency_Fit_Objects[Number_Mu_Bins];
   TH1F* MET_Distribution = 0;
   TEfficiency* MET_L1XE30Efficiency = 0;
   TF1* MET_L1XE30EfficiencyFit = 0;
    TH1D*            MET_Correctedmu0thru10 = 0;
    TH1D*            MET_Correctedmu10thru20 = 0;
    TH1D*            MET_Correctedmu20thru30 = 0;
    TH1D*            MET_Correctedmu30thru40 = 0;
    TH1D*            MET_Correctedmu40thru50 = 0;
    TH1D*            MET_Correctedmu50thru60 = 0;
    TH1D*            MET_Correctedmu60thru70 = 0;

    TH1D* zbMETMuBin0thru10 = 0;
    TH1D* zbMETMuBin10thru20 = 0;
    TH1D* zbMETMuBin20thru30 = 0;
    TH1D* zbMETMuBin30thru40 = 0;
    TH1D* zbMETMuBin40thru50 = 0;
    TH1D* zbMETMuBin50thru60 = 0;
    TH1D* zbMETMuBin60thru70 = 0;

    TH1D*            MET_Correctedmu0thru10_copy = 0;
    TH1D*            MET_Correctedmu10thru20_copy = 0;
    TH1D*            MET_Correctedmu20thru30_copy = 0;
    TH1D*            MET_Correctedmu30thru40_copy = 0;
    TH1D*            MET_Correctedmu40thru50_copy = 0;
    TH1D*            MET_Correctedmu50thru60_copy = 0;
    TH1D*            MET_Correctedmu60thru70_copy = 0;

    TH1D* zbMETMuBin0thru10_copy = 0;
    TH1D* zbMETMuBin10thru20_copy = 0;
    TH1D* zbMETMuBin20thru30_copy = 0;
    TH1D* zbMETMuBin30thru40_copy = 0;
    TH1D* zbMETMuBin40thru50_copy = 0;
    TH1D* zbMETMuBin50thru60_copy = 0;
    TH1D* zbMETMuBin60thru70_copy = 0;

    TF1*             EfficiencyFitMuBin1 = 0;
    TF1*             EfficiencyFitMuBin2 = 0;
    TF1*             EfficiencyFitMuBin3 = 0;
    TF1*             EfficiencyFitMuBin4 = 0;
    TF1*             EfficiencyFitMuBin5 = 0;
    TF1*             EfficiencyFitMuBin6 = 0;
    TF1*             EfficiencyFitMuBin7 = 0;

    TF1*             L1XE50EfficiencyFitMuBin1 = 0;
    TF1*             L1XE50EfficiencyFitMuBin2 = 0;
    TF1*             L1XE50EfficiencyFitMuBin3 = 0;
    TF1*             L1XE50EfficiencyFitMuBin4 = 0;
    TF1*             L1XE50EfficiencyFitMuBin5 = 0;
    TF1*             L1XE50EfficiencyFitMuBin6 = 0;
    TF1*             L1XE50EfficiencyFitMuBin7 = 0;

    TEfficiency* efficiencyObjectMu0thru10 = 0;
    TEfficiency* efficiencyObjectMu10thru20 =0;
    TEfficiency* efficiencyObjectMu20thru30 =0;
    TEfficiency* efficiencyObjectMu30thru40 = 0;
    TEfficiency* efficiencyObjectMu40thru50 = 0;
    TEfficiency* efficiencyObjectMu50thru60 = 0;
    TEfficiency* efficiencyObjectMu60thru70 = 0;

    TEfficiency* L1XE50efficiencyObjectMu0thru10 = 0;
    TEfficiency* L1XE50efficiencyObjectMu10thru20 =0;
    TEfficiency* L1XE50efficiencyObjectMu20thru30 =0;
    TEfficiency* L1XE50efficiencyObjectMu30thru40 = 0;
    TEfficiency* L1XE50efficiencyObjectMu40thru50 = 0;
    TEfficiency* L1XE50efficiencyObjectMu50thru60 = 0;
    TEfficiency* L1XE50efficiencyObjectMu60thru70 = 0;

    Float_t binWidth = 1.0;
    Float_t gevLow = 0.0;
    Float_t gevHigh = 300.0;
    Int_t nbins = (gevHigh-gevLow)/binWidth;
    TString alg_name = "METCELL";
    TString xaxisTitle = alg_name + " [GeV]";
    TString yaxisTitle = "Number of Entries";

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<UInt_t> RunNumber = {fReader, "RunNumber"};
   TTreeReaderValue<Float_t> InTimePileup = {fReader, "InTimePileup"};
   TTreeReaderValue<Float_t> OutOfTimePileup = {fReader, "OutOfTimePileup"};
   TTreeReaderValue<Float_t> L1_met = {fReader, "L1.met"};
   TTreeReaderValue<Float_t> cell_met = {fReader, "cell.met"};
   TTreeReaderValue<Bool_t> HLT_noalg_zb_L1ZB_passed = {fReader, "HLT_noalg_zb_L1ZB.passed"};
   TTreeReaderValue<Float_t> HLT_noalg_zb_L1ZB_prescale = {fReader, "HLT_noalg_zb_L1ZB.prescale"};
   TTreeReaderValue<Bool_t> L1_XE50_passed = {fReader, "L1_XE50.passed"};
   TTreeReaderValue<Float_t> L1_XE50_prescale = {fReader, "L1_XE50.prescale"};

   CorrectL1XE50ToZB(TTree * /*tree*/ =0) { }
   virtual ~CorrectL1XE50ToZB() { }
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
   Bool_t isPassnoAlgL1XE30();
   Bool_t isPassnoAlgL1XE50();
   Bool_t inMuRange( Float_t , Float_t );
   Double_t ComputeWeight(TF1*,TF1*);

   ClassDef(CorrectL1XE50ToZB,0);

};

#endif

