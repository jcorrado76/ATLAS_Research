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
#include <THStack.h>
#include <TString.h>

// Headers needed by this particular selector
#include <vector>

class PlotMETDistsVersMu : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain
   TString alg_name = "cell.met"; //CHANGE THIS FOR WHICH MET DISTRIBUTION YOU WANT TO USE 
   TH1F*            MET_Datamu0thru10 = 0;
   TH1F*            MET_Datamu10thru20 = 0;
   TH1F*            MET_Datamu20thru30 = 0;
   TH1F*            MET_Datamu30thru40 = 0;
   TH1F*            MET_Datamu40thru50 = 0;
   TH1F*            MET_Datamu50thru60 = 0;
   TH1F*            MET_Datamu60thru70 = 0;

   // Readers to access the data (delete the ones you do not need).{{{
   TTreeReaderValue<UInt_t> RunNumber = {fReader, "RunNumber"};
   TTreeReaderValue<ULong64_t> EventNumber = {fReader, "EventNumber"};
   TTreeReaderValue<UInt_t> LumiBlock = {fReader, "LumiBlock"};
   TTreeReaderValue<UInt_t> NPrimaryVertices = {fReader, "NPrimaryVertices"};
   TTreeReaderValue<Float_t> InTimePileup = {fReader, "InTimePileup"};
   TTreeReaderValue<Float_t> OutOfTimePileup = {fReader, "OutOfTimePileup"};
   TTreeReaderValue<Float_t> MET_Data = {fReader, alg_name };


   PlotMETDistsVersMu(TTree * /*tree*/ =0) { }
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

   ClassDef(PlotMETDistsVersMu,0);

};
// }}}

#endif

#ifdef PlotMETDistsVersMu_cxx
void PlotMETDistsVersMu::Init(TTree *tree)
{
   fReader.SetTree(tree);
}

Bool_t PlotMETDistsVersMu::Notify()
{
   return kTRUE;
}


#endif // #ifdef PlotMETDistsVersMu_cxx
