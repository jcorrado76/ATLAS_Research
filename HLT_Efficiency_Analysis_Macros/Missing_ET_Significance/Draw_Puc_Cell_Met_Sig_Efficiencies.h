//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Feb 11 09:46:20 2019 by ROOT version 6.16/00
// from TTree tree/tree
// found on file: ../../DATA/mincer_data/PhysicsMain.L1KFXEunprescaledtriggers.2016.f731f758_m1659m1710.Run309759.48Runs.root
//////////////////////////////////////////////////////////

#ifndef Draw_Puc_Cell_Met_Sig_Efficiencies_h
#define Draw_Puc_Cell_Met_Sig_Efficiencies_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TH2.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TEfficiency.h>
#include <TImage.h>
#include <TPaveText.h>


class Draw_Puc_Cell_Met_Sig_Efficiencies : public TSelector {
public :
   // Floats and objects {{{
   TTreeReader     fReader;
   TTree          *fChain = 0;
   TString AlgCellName = "metcell";
   TString AlgPucName = "mettopoclpuc";
   TString AlgMissingEtName = "missing_et_significance";
   const Float_t puc_efficiency_thresh = 138.62;
   const Float_t cell_efficiency_thresh = 113.38;
   const Float_t met_significance_thresh_one = 7.12;
   const Float_t met_significance_thresh_two = 5.0;
   const Float_t met_significance_thresh_three = 3.0;
   Float_t metnomu = 0.0;
   const TString cell_efficiency_title = AlgCellName + " > " + Form(" %.2f", cell_efficiency_thresh ); 
   const TString puc_efficiency_title = AlgPucName + " > " + Form(" %.2f", puc_efficiency_thresh ); 
   const TString met_significance_efficiency_title_one = AlgMissingEtName + " > " + Form(" %.2f", met_significance_thresh_one ); 
   const TString met_significance_efficiency_title_two = AlgMissingEtName + " > " + Form(" %.2f", met_significance_thresh_two ); 
   const TString met_significance_efficiency_title_three = AlgMissingEtName + " > " + Form(" %.2f", met_significance_thresh_three ); 
   TEfficiency* puc_efficiency = 0;
   TEfficiency* cell_efficiency = 0;
   TEfficiency* missing_et_efficiency_one = 0;
   TEfficiency* missing_et_efficiency_two = 0;
   TEfficiency* missing_et_efficiency_three = 0;
   const Int_t muonNbins = 200;
   const Double_t metMin = 0.0;
   const Double_t metMax = 300.0;
   const Double_t metl1thresh = 50.0;
   const Double_t actintCut = 0.0;
   Bool_t isMuon = 0;
   Bool_t isClean = 0;
   Bool_t passTransverseMassCut = 0; //}}}
   // TTreeReaders {{{
   TTreeReaderValue<Float_t> metl1 = {fReader, "metl1"};
   TTreeReaderValue<Float_t> metcell = {fReader, "metcell"};
   TTreeReaderValue<Float_t> setcell = {fReader, "setcell"};
   TTreeReaderValue<Float_t> mettopocl = {fReader, "mettopocl"};
   TTreeReaderValue<Float_t> mettopoclps = {fReader, "mettopoclps"};
   TTreeReaderValue<Float_t> mettopoclpuc = {fReader, "mettopoclpuc"};
   TTreeReaderValue<Float_t> metmht = {fReader, "metmht"};
   TTreeReaderValue<Float_t> metoffrecal = {fReader, "metoffrecal"};
   TTreeReaderValue<Float_t> mexoffrecal = {fReader, "mexoffrecal"};
   TTreeReaderValue<Float_t> meyoffrecal = {fReader, "meyoffrecal"};
   TTreeReaderValue<Float_t> metoffrecalmuon = {fReader, "metoffrecalmuon"};
   TTreeReaderValue<Float_t> mexoffrecalmuon = {fReader, "mexoffrecalmuon"};
   TTreeReaderValue<Float_t> meyoffrecalmuon = {fReader, "meyoffrecalmuon"};
   TTreeReaderValue<Int_t> passrndm = {fReader, "passrndm"};
   TTreeReaderValue<Int_t> passrndmj40 = {fReader, "passrndmj40"};
   TTreeReaderValue<Int_t> passmu24med = {fReader, "passmu24med"};
   TTreeReaderValue<Int_t> passmu24varmed = {fReader, "passmu24varmed"};
   TTreeReaderValue<Int_t> passmu26med = {fReader, "passmu26med"};
   TTreeReaderValue<Int_t> passmu26varmed = {fReader, "passmu26varmed"};
   TTreeReaderValue<Int_t> passnoalgL1XE10 = {fReader, "passnoalgL1XE10"};
   TTreeReaderValue<Int_t> passnoalgL1XE30 = {fReader, "passnoalgL1XE30"};
   TTreeReaderValue<Int_t> passnoalgL1XE40 = {fReader, "passnoalgL1XE40"};
   TTreeReaderValue<Int_t> passnoalgL1XE45 = {fReader, "passnoalgL1XE45"};
   TTreeReaderValue<Int_t> passnoalgL1XE300 = {fReader, "passnoalgL1XE300"};
   TTreeReaderValue<Int_t> recalbroke = {fReader, "recalbroke"};
   TTreeReaderValue<Int_t> passcleancuts = {fReader, "passcleancuts"};
   TTreeReaderValue<Int_t> runnum = {fReader, "runnum"};
   TTreeReaderValue<Int_t> eventnum = {fReader, "eventnum"};
   TTreeReaderValue<Int_t> bcid = {fReader, "bcid"};
   TTreeReaderValue<Float_t> actint = {fReader, "actint"};
   TTreeReaderValue<Float_t> avint = {fReader, "avint"};
   TTreeReaderValue<Float_t> missing_et_significance = {fReader, "missing_et_significance"};//}}}
   // Functions {{{
   Draw_Puc_Cell_Met_Sig_Efficiencies(TTree * /*tree*/ =0) { }
   virtual ~Draw_Puc_Cell_Met_Sig_Efficiencies() { }
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
   ClassDef(Draw_Puc_Cell_Met_Sig_Efficiencies,0); // }}}
};
#endif
