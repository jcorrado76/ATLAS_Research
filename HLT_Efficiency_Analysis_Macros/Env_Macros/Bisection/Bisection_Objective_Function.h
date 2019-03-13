#ifndef Bisection_Objective_Function_h
#define Bisection_Objective_Function_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

class Bisection_Objective_Function : public TSelector {
public :
   TTreeReader     fReader;  
   TTree          *fChain = 0;   
   TString AlgAName, AlgBName;
   Float_t AlgAThreshold, AlgBThreshold, MetL1Threshold;
   Int_t NumberEventsKept;
   Float_t RndmCut = 0.5;

   // Readers to access the data (delete the ones you do not need){{{
   TTreeReaderValue<Float_t> AlgA = { fReader, AlgAName };
   TTreeReaderValue<Float_t> AlgB = { fReader, AlgBName };

   TTreeReaderValue<Float_t> metl1 = {fReader, "metl1"};
   TTreeReaderValue<Float_t> metcell = {fReader, "metcell"};
   TTreeReaderValue<Float_t> mettopocl = {fReader, "mettopocl"};
   TTreeReaderValue<Float_t> mettopoclps = {fReader, "mettopoclps"};
   TTreeReaderValue<Float_t> mettopoclpuc = {fReader, "mettopoclpuc"};
   TTreeReaderValue<Float_t> metmht = {fReader, "metmht"};
   TTreeReaderValue<Float_t> metrefwmuon = {fReader, "metrefwmuon"};
   TTreeReaderValue<Float_t> metoffrecal = {fReader, "metoffrecal"};
   TTreeReaderValue<Float_t> mexoffrecal = {fReader, "mexoffrecal"};
   TTreeReaderValue<Float_t> meyoffrecal = {fReader, "meyoffrecal"};
   TTreeReaderValue<Float_t> setoffrecal = {fReader, "setoffrecal"};
   TTreeReaderValue<Float_t> metrefmuon = {fReader, "metrefmuon"};
   TTreeReaderValue<Float_t> mexrefmuon = {fReader, "mexrefmuon"};
   TTreeReaderValue<Float_t> meyrefmuon = {fReader, "meyrefmuon"};
   TTreeReaderValue<Float_t> metoffrecalmuon = {fReader, "metoffrecalmuon"};
   TTreeReaderValue<Float_t> mexoffrecalmuon = {fReader, "mexoffrecalmuon"};
   TTreeReaderValue<Float_t> meyoffrecalmuon = {fReader, "meyoffrecalmuon"};
   TTreeReaderValue<Int_t> passrndm = {fReader, "passrndm"};
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
   TTreeReaderValue<Float_t> actint = {fReader, "actint"};
   //}}}

   Bisection_Objective_Function(TTree * = 0) { }
   ~Bisection_Objective_Function() { }
   Int_t   Version() const { return 2; }
   void    Begin(TTree *tree);
   void    SlaveBegin(TTree *tree);
   void    Init(TTree *tree);
   Bool_t  Notify();
   Bool_t  Process(Long64_t entry);
   Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   void    SetOption(const char *option) { fOption = option; }
   void    SetObject(TObject *obj) { fObject = obj; }
   void    SetInputList(TList *input) { fInput = input; }
   TList  *GetOutputList() const { return fOutput; }
   void    SlaveTerminate();
   void    Terminate();

   Bool_t IsPassnoAlgOrRndm() const { return ( *passrndm > RndmCut || *passnoalgL1XE10 > RndmCut || 
           *passnoalgL1XE30 > RndmCut || *passnoalgL1XE40 > RndmCut || *passnoalgL1XE45 > RndmCut  );}
   Bool_t IsClean() const { return *passcleancuts > 0.1 && *recalbroke < 0.1; }
   Bool_t PassActint() const { return *actint > ActintCut; }
   Bool_t AlgAPass() const { return *AlgA > AlgAThreshold; }
   Bool_t AlgBPass() const { return *AlgB > AlgBThreshold; }
   Bool_t PassL1() const { return *metl1 > MetL1Threshold; }

   Int_t GetNumbEventsKeptCombined() const { return NumberEventsKept; }


   ClassDef(Bisection_Objective_Function,0);
};

#endif

#ifdef Bisection_Objective_Function_cxx
void Bisection_Objective_Function::Init(TTree *tree)
{
   fReader.SetTree(tree);
}

Bool_t Bisection_Objective_Function::Notify()
{
   return kTRUE;
}


#endif 
