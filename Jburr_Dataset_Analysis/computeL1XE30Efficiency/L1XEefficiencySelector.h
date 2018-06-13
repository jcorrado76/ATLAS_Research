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
   // initialize pointers to 0
   TEfficiency*            metcellmu0thru10 = 0;
   TEfficiency*            metcellmu10thru20 = 0;
   TEfficiency*            metcellmu20thru30 = 0;
   TEfficiency*            metcellmu30thru40 = 0;
   TEfficiency*            metcellmu40thru50 = 0;
   TEfficiency*            metcellmu50thru60 = 0;
   TEfficiency*            metcellmu60thru70 = 0;

   // Readers to access the data (delete the ones you do not need).{{{
   TTreeReaderValue<UInt_t> RunNumber = {fReader, "RunNumber"};
   TTreeReaderValue<UInt_t> LumiBlock = {fReader, "LumiBlock"};
   TTreeReaderValue<Float_t> InTimePileup = {fReader, "InTimePileup"};
   TTreeReaderValue<Float_t> OutOfTimePileup = {fReader, "OutOfTimePileup"};
   TTreeReaderValue<Float_t> cell_met = {fReader, "cell.met"};
   TTreeReaderValue<Float_t> HLT_noalg_zb_L1ZB_prescale = {fReader, "HLT_noalg_zb_L1ZB.prescale"};
   // get efficiency of L1XE 30 
   TTreeReaderValue<Float_t> HLT_noalg_L1XE30_prescale = {fReader, "HLT_noalg_L1XE30.prescale"};

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
