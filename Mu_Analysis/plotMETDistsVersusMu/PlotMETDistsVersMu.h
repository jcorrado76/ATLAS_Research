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
#include <TEfficiency.h>
#include <TF1.h>

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
   TEfficiency*            MET_Algmu0thru10Efficiency = 0;
   TEfficiency*            MET_Algmu10thru20Efficiency = 0;
   TEfficiency*            MET_Algmu20thru30Efficiency = 0;
   TEfficiency*            MET_Algmu30thru40Efficiency = 0;
   TEfficiency*            MET_Algmu40thru50Efficiency = 0;
   TEfficiency*            MET_Algmu50thru60Efficiency = 0;
   TEfficiency*            MET_Algmu60thru70Efficiency = 0;


    Float_t gevLow = 0.0;
    Float_t gevHigh = 300.0;
    Float_t met_dist_binwidth = 1.0;
    Float_t efficiency_bin_width = 20.0; //want 20 GeV bins
    Int_t met_dist_nbins = (gevHigh - gevLow) / met_dist_binwidth; // compute nbins as function of preferred width
    Int_t efficiency_nbins = (gevHigh - gevLow) / efficiency_bin_width;




   Float_t XE = 30.0; // L1 cut
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
   Bool_t isPassnoAlgXE30();
   Bool_t inMuRange( Float_t , Float_t );
   static Double_t fitFunction(Double_t *x , Double_t *par );
   TF1* generateFitFunction(TEfficiency* teff_obj, float gevMax = 300.0, float initial_slope = 0.1 , float initial_intercept = 0.0, float initial_sigma = 10.0);

   ClassDef(PlotMETDistsVersMu,0);

};

#endif

