
#ifndef userInfo_h
#define userInfo_h

#include <string>
#include <iostream>
#include <fstream>

#include "TMath.h"
#include "TH1.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TROOT.h"
#include "TEfficiency.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TF1.h"
#include "TNtuple.h"
#include "TBenchmark.h"
#include "TObject.h"
#include "TDatime.h"
#include "TChain.h"
#include"TCut.h"


class userInfo : public TObject {

private:
    TString M_Name;
    TString M_AlgAName;
    TString M_AlgBName;
    Int_t M_Nbins;
    Float_t M_Metmin;
    Float_t M_Metmax;
    Float_t M_Metl1thresh;
    Float_t M_Frac;
    TString M_ThreshFileName;
    TString M_MuonFileName;
    Int_t M_NumberEventsToKeep;
    TString M_ZerobiasFileName;
    TString M_MuonFilename;
    Int_t M_NumPassnoalgPassProcess1;
    Int_t M_NumPassnoalgProcess2AlgA;
    Int_t M_NumPassnoalgProcess2AlgB;
    Int_t M_NumPassnoalgProcess2AlgCombined;
    Int_t M_NumMuonPassProcess1;
    Int_t M_NumMuonPassProcess2AlgA;
    Int_t M_NumMuonPassProcess2AlgB;
    Int_t M_NumMuonPassProcess2Combined;
    Float_t M_AlgAIndividThresh;
    Float_t M_AlgBIndividThresh;
    Float_t M_AlgACombinedThresh;
    Float_t M_AlgBCombinedThresh;
    Int_t M_MuonNentries;
    Int_t M_PassnoAlgNentries;
    Int_t M_NumMuonKeptCombined;
    Int_t M_NumMuonDenominator;
    Int_t M_Epsilon;
    Float_t M_ActintCut;
    TDatime M_Now;
    Float_t M_BinWidth;
    Float_t M_Passnoalgcut;
    TNtuple* M_BisectionData;
    Float_t M_Passrndmcut;



public:
    //default constructor
    userInfo();
    const char *GetName() const;
    void Print(Option_t *option = "") const;
    TString Get_ThreshFileName()      const;
    TString Get_MuonFileName()        const;
    Float_t Get_MetL1Thresh()         const;
    Float_t Get_ActintCut()           const;
    Float_t Get_Frac()                const;
    Float_t Get_MetMin()              const;
    Float_t Get_MetMax()              const;
    Int_t   Get_Nbins()               const;
    Int_t   Get_Epsilon()             const;
    Int_t   Get_MuonNentries()        const;
    Int_t   Get_ThreshNentries()      const;
    TDatime Get_Date()                const;
    TString Get_AlgAName()            const;
    TString Get_AlgBName()            const;
    Int_t   Get_NumberEventsToKeep()  const;
    Float_t Get_IndividAlgAThresh()   const;
    Float_t Get_IndividAlgBThresh()   const;
    Float_t Get_CombinedAlgAThresh()  const;
    Float_t Get_CombinedAlgBThresh()  const;
    Int_t Get_NumThreshPassProcess1() const;
    Float_t Get_BinWidth()            const;
    Float_t Get_Passnoalgcut()        const;
    Float_t Get_Passrndmcut()         const;

    void Fill_Bisection_Data                   ( const Float_t input , const Float_t output ,
                                                 const Int_t numEvents,const Float_t threshA,
                                                 const Float_t threshB );
    void Read_Parameter_File                   ( const TString FilePath );
    void Set_AlgAName                          ( const TString algA );
    void Set_AlgBName                          ( const TString algB );
    void Set_ThresholdFile                     ( const TString file );
    void Set_MuonFile                          ( const TString file );
    void Set_NumPassNoAlgPassProcess1          ( const Float_t num );
    void Set_NumMuonPassProcess1               ( const Float_t num );
    void Set_NumPassNoAlgPassProcess2AlgA      ( const Float_t num );
    void Set_NumPassNoAlgPassProcess2AlgB      ( const Float_t num );
    void Set_NumPassNoAlgPassProcess2Combined  ( const Float_t num );
    void Set_NumMuonPassProcess2AlgA           ( const Float_t num );
    void Set_NumMuonPassProcess2AlgB           ( const Float_t num );
    void Set_NumMuonPassProcess2Combined       ( const Float_t num );
    void Set_AlgAIndividThresh                 ( const Float_t thresh );
    void Set_AlgBIndividThresh                 ( const Float_t thresh );
    void Set_AlgACombinedThresh                ( const Float_t thresh );
    void Set_AlgBCombinedThresh                ( const Float_t thresh );
    void Set_MuonNentries                      ( const Int_t num );
    void Set_PassnoalgNentries                 ( const Int_t num );
    void Set_NumMuonKeptCombinedAtThresh       ( const Int_t num );
    void Set_Num_PassProcess2AlgA              ( const Int_t num );
    void Set_Num_PassProcess2AlgB              ( const Int_t num );
    void Set_Num_PassProcess2Combined          ( const Int_t num );
    void Set_NumTotal                          ( const Int_t num );
    void Set_ActintCut                         ( const Float_t thresh );
    void Set_Epsilon                           ( const Int_t epsilon );

    ClassDef( userInfo, 1)
};

/*#ifndef __CINT__
extern userInfo* parameters;
#endif*/

#endif
