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
#include <TH2.h>
#include <TEfficiency.h>
#include <TStyle.h>

// Headers needed by this particular selector
#include <vector>

class L1XEefficiencySelector : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain
   TEfficiency*            metcellmu0thru10 = 0;
   TEfficiency*            metcellmu10thru20 = 0;
   TEfficiency*            metcellmu20thru30 = 0;
   TEfficiency*            metcellmu30thru40 = 0;
   TEfficiency*            metcellmu40thru50 = 0;
   TEfficiency*            metcellmu50thru60 = 0;
   TEfficiency*            metcellmu60thru70 = 0;

   // Readers to access the data (delete the ones you do not need).{{{
   TTreeReaderValue<UInt_t> RunNumber = {fReader, "RunNumber"};
   TTreeReaderValue<ULong64_t> EventNumber = {fReader, "EventNumber"};
   TTreeReaderValue<UInt_t> LumiBlock = {fReader, "LumiBlock"};
   TTreeReaderValue<UInt_t> NPrimaryVertices = {fReader, "NPrimaryVertices"};
   TTreeReaderValue<Float_t> InTimePileup = {fReader, "InTimePileup"};
   TTreeReaderValue<Float_t> OutOfTimePileup = {fReader, "OutOfTimePileup"};
   TTreeReaderValue<Float_t> cell_mpx = {fReader, "cell.mpx"};
   TTreeReaderValue<Float_t> cell_mpy = {fReader, "cell.mpy"};
   TTreeReaderValue<Float_t> cell_sumet = {fReader, "cell.sumet"};
   TTreeReaderValue<Float_t> cell_met = {fReader, "cell.met"};
   TTreeReaderValue<Float_t> cell_phi = {fReader, "cell.phi"};
   TTreeReaderValue<Bool_t> HLT_xe110_pufit_L1XE50_passed = {fReader, "HLT_xe110_pufit_L1XE50.passed"};
   TTreeReaderValue<Float_t> HLT_xe110_pufit_L1XE50_prescale = {fReader, "HLT_xe110_pufit_L1XE50.prescale"};
   TTreeReaderValue<UInt_t> HLT_xe110_pufit_L1XE50_passBits = {fReader, "HLT_xe110_pufit_L1XE50.passBits"};
   TTreeReaderValue<Bool_t> L1_XE50_passed = {fReader, "L1_XE50.passed"};
   TTreeReaderValue<Float_t> L1_XE50_prescale = {fReader, "L1_XE50.prescale"};
   TTreeReaderValue<UInt_t> L1_XE50_passBits = {fReader, "L1_XE50.passBits"};
   TTreeReaderValue<Bool_t> L1_XE55_passed = {fReader, "L1_XE55.passed"};
   TTreeReaderValue<Float_t> L1_XE55_prescale = {fReader, "L1_XE55.prescale"};
   TTreeReaderValue<UInt_t> L1_XE55_passBits = {fReader, "L1_XE55.passBits"};
   TTreeReaderValue<Bool_t> L1_XE60_passed = {fReader, "L1_XE60.passed"};
   TTreeReaderValue<Float_t> L1_XE60_prescale = {fReader, "L1_XE60.prescale"};
   TTreeReaderValue<UInt_t> L1_XE60_passBits = {fReader, "L1_XE60.passBits"};
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

#ifdef L1XEefficiencySelector_cxx
void L1XEefficiencySelector::Init(TTree *tree)
{
   fReader.SetTree(tree);
}

Bool_t L1XEefficiencySelector::Notify()
{
   return kTRUE;
}


#endif // #ifdef L1XEefficiencySelector_cxx
