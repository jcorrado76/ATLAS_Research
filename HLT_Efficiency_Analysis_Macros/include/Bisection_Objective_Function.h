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
   Int_t events_kept = 0;
   Int_t zerobias_events = 0;
   Int_t number_events_to_keep = 0;

   Float_t AlgAThreshold, AlgBThreshold, MetL1Threshold, ActintCut;
   Float_t RndmCut = 0.5;

   TH1F* algAHist = 0;
   TH1F* algBHist = 0;

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

   Bool_t IsPassnoAlgOrRndm(); 
   Bool_t IsClean(); 
   Bool_t PassActint(); 
   Bool_t AlgAPass();
   Bool_t AlgBPass(); 
   Bool_t PassL1();


    void SetAlgAName( TString name ){ AlgAName = name; }
    void SetAlgBName( TString name ){ AlgBName = name; }
    void Set_AlgAHist( const TH1F* algAHist ){ algAHist = algAHist }
    void Set_AlgBHist( const TH1F* algBHist ){ algBHist = algBHist }
    void SetAlgAThresh( const Float_t thresh ){ AlgAThreshold = thresh; }
    void SetAlgBThresh( const Float_t thresh ){ AlgBThreshold = thresh; }
    void SetL1Thresh( const Float_t thresh ){ MetL1Threshold = thresh; }
    void SetActintCut( const Float_t thresh ){ ActintCut = thresh; }
    void SetNumbToKeep( const Int_t num ){ number_events_to_keep = num; }
    void Clear(){ events_kept = 0; }

    float GetTriggerRate(){ return events_kept / zerobias_events; }

   ClassDef(Bisection_Objective_Function,0);
};

#endif

#ifdef Bisection_Objective_Function_cxx
void Bisection_Objective_Function::Init(TTree *tree){fReader.SetTree(tree);}
Bool_t Bisection_Objective_Function::Notify(){return kTRUE;}


#endif 
