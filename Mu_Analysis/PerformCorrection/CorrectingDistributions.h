//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jul 11 09:26:49 2018 by ROOT version 6.15/01
// from TChain METTree/jburrntuplechain
//////////////////////////////////////////////////////////

#ifndef CorrectingDistributions_h
#define CorrectingDistributions_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector
#include <vector>



class CorrectingDistributions : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain
   TH1F*            MET_Correctedmu0thru10 = 0;
   TH1F*            MET_Correctedmu10thru20 = 0;
   TH1F*            MET_Correctedmu20thru30 = 0;
   TH1F*            MET_Correctedmu30thru40 = 0;
   TH1F*            MET_Correctedmu40thru50 = 0;
   TH1F*            MET_Correctedmu50thru60 = 0;
   TH1F*            MET_Correctedmu60thru70 = 0;

   TF1*             EfficiencyFitMuBin1 = 0;
   TF1*             EfficiencyFitMuBin2 = 0;
   TF1*             EfficiencyFitMuBin3 = 0;
   TF1*             EfficiencyFitMuBin4 = 0;
   TF1*             EfficiencyFitMuBin5 = 0;
   TF1*             EfficiencyFitMuBin6 = 0;
   TF1*             EfficiencyFitMuBin7 = 0;

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<UInt_t> RunNumber = {fReader, "RunNumber"};
   TTreeReaderValue<ULong64_t> EventNumber = {fReader, "EventNumber"};
   TTreeReaderValue<UInt_t> LumiBlock = {fReader, "LumiBlock"};
   TTreeReaderValue<UInt_t> NPrimaryVertices = {fReader, "NPrimaryVertices"};
   TTreeReaderValue<Float_t> InTimePileup = {fReader, "InTimePileup"};
   TTreeReaderValue<Float_t> OutOfTimePileup = {fReader, "OutOfTimePileup"};
   TTreeReaderValue<Float_t> L1_mpx = {fReader, "L1.mpx"};
   TTreeReaderValue<Float_t> L1_mpy = {fReader, "L1.mpy"};
   TTreeReaderValue<Float_t> L1_sumet = {fReader, "L1.sumet"};
   TTreeReaderValue<Float_t> L1_met = {fReader, "L1.met"};
   TTreeReaderValue<Float_t> L1_phi = {fReader, "L1.phi"};
   TTreeReaderValue<Float_t> cell_mpx = {fReader, "cell.mpx"};
   TTreeReaderValue<Float_t> cell_mpy = {fReader, "cell.mpy"};
   TTreeReaderValue<Float_t> cell_sumet = {fReader, "cell.sumet"};
   TTreeReaderValue<Float_t> cell_met = {fReader, "cell.met"};
   TTreeReaderValue<Float_t> cell_phi = {fReader, "cell.phi"};
   TTreeReaderValue<Bool_t> HLT_noalg_zb_L1ZB_passed = {fReader, "HLT_noalg_zb_L1ZB.passed"};
   TTreeReaderValue<Float_t> HLT_noalg_zb_L1ZB_prescale = {fReader, "HLT_noalg_zb_L1ZB.prescale"};
   TTreeReaderValue<UInt_t> HLT_noalg_zb_L1ZB_passBits = {fReader, "HLT_noalg_zb_L1ZB.passBits"};
   TTreeReaderValue<Bool_t> HLT_j40_L1ZB_passed = {fReader, "HLT_j40_L1ZB.passed"};
   TTreeReaderValue<Float_t> HLT_j40_L1ZB_prescale = {fReader, "HLT_j40_L1ZB.prescale"};
   TTreeReaderValue<UInt_t> HLT_j40_L1ZB_passBits = {fReader, "HLT_j40_L1ZB.passBits"};
   TTreeReaderValue<Bool_t> HLT_noalg_L1XE10_passed = {fReader, "HLT_noalg_L1XE10.passed"};
   TTreeReaderValue<Float_t> HLT_noalg_L1XE10_prescale = {fReader, "HLT_noalg_L1XE10.prescale"};
   TTreeReaderValue<UInt_t> HLT_noalg_L1XE10_passBits = {fReader, "HLT_noalg_L1XE10.passBits"};
   TTreeReaderValue<Bool_t> HLT_noalg_L1XE20_passed = {fReader, "HLT_noalg_L1XE20.passed"};
   TTreeReaderValue<Float_t> HLT_noalg_L1XE20_prescale = {fReader, "HLT_noalg_L1XE20.prescale"};
   TTreeReaderValue<UInt_t> HLT_noalg_L1XE20_passBits = {fReader, "HLT_noalg_L1XE20.passBits"};
   TTreeReaderValue<Bool_t> HLT_noalg_L1XE30_passed = {fReader, "HLT_noalg_L1XE30.passed"};
   TTreeReaderValue<Float_t> HLT_noalg_L1XE30_prescale = {fReader, "HLT_noalg_L1XE30.prescale"};
   TTreeReaderValue<UInt_t> HLT_noalg_L1XE30_passBits = {fReader, "HLT_noalg_L1XE30.passBits"};
   TTreeReaderValue<Bool_t> HLT_noalg_L1XE40_passed = {fReader, "HLT_noalg_L1XE40.passed"};
   TTreeReaderValue<Float_t> HLT_noalg_L1XE40_prescale = {fReader, "HLT_noalg_L1XE40.prescale"};
   TTreeReaderValue<UInt_t> HLT_noalg_L1XE40_passBits = {fReader, "HLT_noalg_L1XE40.passBits"};
   TTreeReaderValue<Bool_t> HLT_noalg_L1XE45_passed = {fReader, "HLT_noalg_L1XE45.passed"};
   TTreeReaderValue<Float_t> HLT_noalg_L1XE45_prescale = {fReader, "HLT_noalg_L1XE45.prescale"};
   TTreeReaderValue<UInt_t> HLT_noalg_L1XE45_passBits = {fReader, "HLT_noalg_L1XE45.passBits"};

   CorrectingDistributions(TTree * /*tree*/ =0) { }
   virtual ~CorrectingDistributions() { }
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

   ClassDef(CorrectingDistributions,0);

};

#endif

#ifdef CorrectingDistributions_cxx
void CorrectingDistributions::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t CorrectingDistributions::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef CorrectingDistributions_cxx
