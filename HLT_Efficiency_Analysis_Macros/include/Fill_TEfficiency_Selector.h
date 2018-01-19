//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jan 15 19:20:16 2018 by ROOT version 6.13/01
// from TTree tree/tree
// found on file: ../../ATLAS_DATA/PhysicsMain.L1KFmuontriggers.2016.f731f758_m1659m1710.Run309759.48Runs.root
//////////////////////////////////////////////////////////

#ifndef TEfficiency_Selector_h
#define TEfficiency_Selector_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TH2.h>
#include <TStyle.h>
#include "Efficiency_Lib.h"


class TEfficiency_Selector : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain
   userInfo		  *M_Parameters;
   Float_t 			ACTINT_CUT=0.0;
   Float_t 			METL1_CUT=0.0;

   // Readers to access the data (delete the ones you do not need){{{
   TTreeReaderValue<Float_t> metl1 = {fReader, "metl1"};
   TTreeReaderValue<Float_t> mexl1 = {fReader, "mexl1"};
   TTreeReaderValue<Float_t> meyl1 = {fReader, "meyl1"};
   TTreeReaderValue<Float_t> setl1 = {fReader, "setl1"};
   TTreeReaderValue<Int_t> mexl1overflow = {fReader, "mexl1overflow"};
   TTreeReaderValue<Int_t> meyl1overflow = {fReader, "meyl1overflow"};
   TTreeReaderValue<Int_t> metl1overflow = {fReader, "metl1overflow"};
   TTreeReaderValue<Float_t> metl1kf = {fReader, "metl1kf"};
   TTreeReaderValue<Float_t> mexl1kf = {fReader, "mexl1kf"};
   TTreeReaderValue<Float_t> meyl1kf = {fReader, "meyl1kf"};
   TTreeReaderValue<Float_t> setl1kf = {fReader, "setl1kf"};
   TTreeReaderValue<Float_t> metl1mht = {fReader, "metl1mht"};
   TTreeReaderValue<Float_t> mexl1mht = {fReader, "mexl1mht"};
   TTreeReaderValue<Float_t> meyl1mht = {fReader, "meyl1mht"};
   TTreeReaderValue<Float_t> setl1mht = {fReader, "setl1mht"};
   TTreeReaderValue<Float_t> metl1mhtkf = {fReader, "metl1mhtkf"};
   TTreeReaderValue<Float_t> mexl1mhtkf = {fReader, "mexl1mhtkf"};
   TTreeReaderValue<Float_t> meyl1mhtkf = {fReader, "meyl1mhtkf"};
   TTreeReaderValue<Float_t> setl1mhtkf = {fReader, "setl1mhtkf"};
   TTreeReaderValue<Float_t> metl2feb = {fReader, "metl2feb"};
   TTreeReaderValue<Float_t> mexl2feb = {fReader, "mexl2feb"};
   TTreeReaderValue<Float_t> meyl2feb = {fReader, "meyl2feb"};
   TTreeReaderValue<Float_t> setl2feb = {fReader, "setl2feb"};
   TTreeReaderValue<Float_t> metcell = {fReader, "metcell"};
   TTreeReaderValue<Float_t> mexcell = {fReader, "mexcell"};
   TTreeReaderValue<Float_t> meycell = {fReader, "meycell"};
   TTreeReaderValue<Float_t> setcell = {fReader, "setcell"};
   TTreeReaderValue<Float_t> mettopocl = {fReader, "mettopocl"};
   TTreeReaderValue<Float_t> mextopocl = {fReader, "mextopocl"};
   TTreeReaderValue<Float_t> meytopocl = {fReader, "meytopocl"};
   TTreeReaderValue<Float_t> settopocl = {fReader, "settopocl"};
   TTreeReaderValue<Float_t> mextopoclmuon = {fReader, "mextopoclmuon"};
   TTreeReaderValue<Float_t> meytopoclmuon = {fReader, "meytopoclmuon"};
   TTreeReaderValue<Float_t> mettopoclem = {fReader, "mettopoclem"};
   TTreeReaderValue<Float_t> mextopoclem = {fReader, "mextopoclem"};
   TTreeReaderValue<Float_t> meytopoclem = {fReader, "meytopoclem"};
   TTreeReaderValue<Float_t> settopoclem = {fReader, "settopoclem"};
   TTreeReaderValue<Float_t> mettopoclps = {fReader, "mettopoclps"};
   TTreeReaderValue<Float_t> mextopoclps = {fReader, "mextopoclps"};
   TTreeReaderValue<Float_t> meytopoclps = {fReader, "meytopoclps"};
   TTreeReaderValue<Float_t> settopoclps = {fReader, "settopoclps"};
   TTreeReaderValue<Float_t> mettopoclpuc = {fReader, "mettopoclpuc"};
   TTreeReaderValue<Float_t> mextopoclpuc = {fReader, "mextopoclpuc"};
   TTreeReaderValue<Float_t> meytopoclpuc = {fReader, "meytopoclpuc"};
   TTreeReaderValue<Float_t> settopoclpuc = {fReader, "settopoclpuc"};
   TTreeReaderValue<Float_t> metmht = {fReader, "metmht"};
   TTreeReaderValue<Float_t> mexmht = {fReader, "mexmht"};
   TTreeReaderValue<Float_t> meymht = {fReader, "meymht"};
   TTreeReaderValue<Float_t> setmht = {fReader, "setmht"};
   TTreeReaderValue<Float_t> metrefwmuon = {fReader, "metrefwmuon"};
   TTreeReaderValue<Float_t> mexrefwmuon = {fReader, "mexrefwmuon"};
   TTreeReaderValue<Float_t> meyrefwmuon = {fReader, "meyrefwmuon"};
   TTreeReaderValue<Float_t> setrefwmuon = {fReader, "setrefwmuon"};
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
   TTreeReaderValue<Float_t> metoffrecaltrksft = {fReader, "metoffrecaltrksft"};
   TTreeReaderValue<Float_t> mexoffrecaltrksft = {fReader, "mexoffrecaltrksft"};
   TTreeReaderValue<Float_t> meyoffrecaltrksft = {fReader, "meyoffrecaltrksft"};
   TTreeReaderValue<Int_t> npv = {fReader, "npv"};
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
   TTreeReaderValue<Int_t> passxe100 = {fReader, "passxe100"};
   TTreeReaderValue<Int_t> passxe100mu = {fReader, "passxe100mu"};
   TTreeReaderValue<Int_t> passxe160tclcw = {fReader, "passxe160tclcw"};
   TTreeReaderValue<Int_t> passxe160tclcwmu = {fReader, "passxe160tclcwmu"};
   TTreeReaderValue<Int_t> passxe130tcem = {fReader, "passxe130tcem"};
   TTreeReaderValue<Int_t> passxe130tcemmu = {fReader, "passxe130tcemmu"};
   TTreeReaderValue<Int_t> passxe110mht = {fReader, "passxe110mht"};
   TTreeReaderValue<Int_t> passxe110mhtmu = {fReader, "passxe110mhtmu"};
   TTreeReaderValue<Int_t> passxe105pufit = {fReader, "passxe105pufit"};
   TTreeReaderValue<Int_t> passxe110pufit = {fReader, "passxe110pufit"};
   TTreeReaderValue<Int_t> passxe140pufit = {fReader, "passxe140pufit"};
   TTreeReaderValue<Int_t> passxe140pufitmu = {fReader, "passxe140pufitmu"};
   TTreeReaderValue<Int_t> passxe140pueta = {fReader, "passxe140pueta"};
   TTreeReaderValue<Int_t> passxe140puetamu = {fReader, "passxe140puetamu"};
   TTreeReaderValue<Int_t> recalbroke = {fReader, "recalbroke"};
   TTreeReaderValue<Int_t> passcleancuts = {fReader, "passcleancuts"};
   TTreeReaderValue<Int_t> runnum = {fReader, "runnum"};
   TTreeReaderValue<Int_t> eventnum = {fReader, "eventnum"};
   TTreeReaderValue<Int_t> bcid = {fReader, "bcid"};
   TTreeReaderValue<Float_t> actint = {fReader, "actint"};
   TTreeReaderValue<Float_t> avint = {fReader, "avint"};
   //}}}
   TEfficiency_Selector(TTree * /*tree*/ =0) { }//{{{
   virtual ~TEfficiency_Selector() { }
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
   //}}}

    Bool_t IsMuon(){
            return( *passmuvarmed > 0.1 || *passmuon > 0.1 );
    }

    Bool_t IsClean(){
            return( *passcleancuts > 0.1 && *recalbroke < 0.1 );
    }

    Bool_t PassActintCut(){
            return( *actint > ACTINT_CUT );
    } 

	Bool_t PassTransverseMassCut(){
			return( Efficiency_Lib::passTransverseMassCut( *metoffrecal , *mexoffrecal  , *meyoffrecal ,
									*metoffrecalmuon , *mexoffrecalmuon , *meyoffrecalmuon ) );
	}

	Bool_t PassL1Cut(){
			return( *metl1 > METL1_CUT );
	}

	Float_t ComputeMetnomu(){
			return( Efficiency_Lib::computeMetNoMu( *mexoffrecal , *meyoffrecal , *mexoffrecalmuon , *meyoffrecalmuon ) );
	}


   ClassDef(TEfficiency_Selector,0);

};

#endif

#ifdef TEfficiency_Selector_cxx
void TEfficiency_Selector::Init(TTree *tree)
{
   fReader.SetTree(tree);
}

Bool_t TEfficiency_Selector::Notify()
{
   return kTRUE;
}


#endif // #ifdef TEfficiency_Selector_cxx
