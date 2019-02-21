//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Feb 21 11:29:06 2019 by ROOT version 6.16/00
// from TTree tree/tree
// found on file: ../../DATA/mincer_data/ZeroBiasL1KF2016R307195R311481.51Runs.root
//////////////////////////////////////////////////////////

#ifndef Count_ZB_Trigger_Rate_h
#define Count_ZB_Trigger_Rate_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TH2.h>
#include <TStyle.h>


class Count_ZB_Trigger_Rate : public TSelector {
public :
   TTreeReader     fReader;  
   TTree          *fChain = 0;
   // TObjects {{{
   TString AlgCellName = "metcell";
   TString AlgPucName = "mettopoclpuc";
   TString AlgMissingEtName = "missing_et_significance";
   const Float_t puc_efficiency_thresh = 138.62;
   const Float_t cell_efficiency_thresh = 113.38;
   const Float_t met_significance_thresh_one = 7.12;
   const Float_t met_significance_thresh_two = 5.0;
   const Float_t met_significance_thresh_three = 3.0;
   Int_t pass_puc = 0;
   Int_t pass_cell = 0;
   Int_t pass_etmiss_3 = 0;
   Int_t pass_etmiss_5 = 0;
   Int_t pass_etmiss_7 = 0;
   Int_t pass_transverse_mass = 0;
   Int_t pass_clean_cuts = 0;
   const TString cell_efficiency_title = AlgCellName + " > " + Form(" %.2f", cell_efficiency_thresh ); 
   const TString puc_efficiency_title = AlgPucName + " > " + Form(" %.2f", puc_efficiency_thresh ); 
   const TString met_significance_efficiency_title_one = AlgMissingEtName + " > " + Form(" %.2f", met_significance_thresh_one ); 
   const TString met_significance_efficiency_title_two = AlgMissingEtName + " > " + Form(" %.2f", met_significance_thresh_two ); 
   const TString met_significance_efficiency_title_three = AlgMissingEtName + " > " + Form(" %.2f", met_significance_thresh_three ); 
   const Int_t muonNbins = 200;
   const Double_t metMin = 0.0;
   const Double_t metMax = 300.0;
   const Double_t metl1thresh = 50.0;
   const Double_t actintCut = 0.0;
   const Double_t passnoalgcut = 0.5;
   Int_t isRndm = 0;
   Bool_t isClean = 0;
   Bool_t isL1 = 0;
   Bool_t isPassnoalg = 0;
   Bool_t passTransverseMassCut = 0; //}}}
   // TTreeReaders {{{
   TTreeReaderValue<Float_t> metl1 = {fReader, "metl1"};
   TTreeReaderValue<Float_t> metcell = {fReader, "metcell"};
   TTreeReaderValue<Float_t> mettopoclps = {fReader, "mettopoclps"};
   TTreeReaderValue<Float_t> mettopoclpuc = {fReader, "mettopoclpuc"};
   TTreeReaderValue<Float_t> metmht = {fReader, "metmht"};
   TTreeReaderValue<Float_t> metoffrecal = {fReader, "metoffrecal"};
   TTreeReaderValue<Float_t> mexoffrecal = {fReader, "mexoffrecal"};
   TTreeReaderValue<Float_t> meyoffrecal = {fReader, "meyoffrecal"};
   TTreeReaderValue<Float_t> metoffrecalmuon = {fReader, "metoffrecalmuon"};
   TTreeReaderValue<Float_t> mexoffrecalmuon = {fReader, "mexoffrecalmuon"};
   TTreeReaderValue<Float_t> meyoffrecalmuon = {fReader, "meyoffrecalmuon"};
   TTreeReaderValue<Int_t> passnoalgL1XE10 = {fReader, "passnoalgL1XE10"};
   TTreeReaderValue<Int_t> passnoalgL1XE30 = {fReader, "passnoalgL1XE30"};
   TTreeReaderValue<Int_t> passnoalgL1XE40 = {fReader, "passnoalgL1XE40"};
   TTreeReaderValue<Int_t> passnoalgL1XE45 = {fReader, "passnoalgL1XE45"};
   TTreeReaderValue<Int_t> passnoalgL1XE300 = {fReader, "passnoalgL1XE300"};
   TTreeReaderValue<Int_t> passrndm = {fReader, "passrndm"};
   TTreeReaderValue<Int_t> recalbroke = {fReader, "recalbroke"};
   TTreeReaderValue<Int_t> passcleancuts = {fReader, "passcleancuts"};
   TTreeReaderValue<Float_t> actint = {fReader, "actint"};
   TTreeReaderValue<Float_t> missing_et_significance = {fReader, "missing_et_significance"};//}}}
   // Functions {{{
   Count_ZB_Trigger_Rate(TTree * /*tree*/ =0) { }
   virtual ~Count_ZB_Trigger_Rate() { }
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
   ClassDef(Count_ZB_Trigger_Rate,0); //}}}
};
#endif
#ifdef Count_ZB_Trigger_Rate_cxx
void Count_ZB_Trigger_Rate::Init(TTree *tree){fReader.SetTree(tree);}
Bool_t Count_ZB_Trigger_Rate::Notify(){return kTRUE;}
#endif // #ifdef Count_ZB_Trigger_Rate_cxx
