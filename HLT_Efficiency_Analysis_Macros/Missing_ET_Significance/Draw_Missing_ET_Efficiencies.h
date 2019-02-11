//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Feb 11 09:46:20 2019 by ROOT version 6.16/00
// from TTree tree/tree
// found on file: ../../DATA/mincer_data/PhysicsMain.L1KFXEunprescaledtriggers.2016.f731f758_m1659m1710.Run309759.48Runs.root
//////////////////////////////////////////////////////////

#ifndef Draw_Missing_ET_Efficiencies_h
#define Draw_Missing_ET_Efficiencies_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

class Draw_Missing_ET_Efficiencies : public TSelector {
public :
   TTreeReader     fReader;
   TTree          *fChain = 0;
   TString AlgAName = "metcell";
   TString AlgBName = "missing_et_significance";
    const Float_t AlgAIndividThresh = 113.38;
    const Float_t AlgBIndividThresh = 7.12;
    const Float_t CombinedThreshAlgA = 63.62;
    const Float_t CombinedThreshAlgB = 4.12;
   const TString astring = AlgAName + " > " + Form(" %.2f", AlgAIndividThresh ); // titles
   const TString bstring = AlgBName + " > " + Form(" %.2f", AlgBIndividThresh );
   const TString cstring = AlgAName + " > " + Form(" %.2f", CombinedThreshAlgA) + " and " + AlgBName + " > " + Form(" %.2f", CombinedThreshAlgB);
   TEfficiency* Ateff = 0;
   TEfficiency* Bteff = 0;
   TEfficiency* Cteff = 0;
   const Int_t muonNbins = 200;
   const Double_t metMin = 0.0;
   const Double_t metMax = 300.0;
   const Double_t metl1thresh = 50.0;
   const Double_t actintCut = 0.0;
   Bool_t isMuon = 0;
   Bool_t isClean = 0;
   Bool_t passTransverseMassCut = 0;
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
   Draw_Missing_ET_Efficiencies(TTree * /*tree*/ =0) { }
   virtual ~Draw_Missing_ET_Efficiencies() { }
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

   ClassDef(Draw_Missing_ET_Efficiencies,0);

};

#endif

#ifdef Draw_Missing_ET_Efficiencies_cxx
void Draw_Missing_ET_Efficiencies::Init(TTree *tree){fReader.SetTree(tree);}
Bool_t Draw_Missing_ET_Efficiencies::Notify(){return kTRUE;}

#endif // #ifdef Draw_Missing_ET_Efficiencies_cxx
