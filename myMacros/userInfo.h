
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
    TString algAName;
    TString algBName;
    Int_t nbins;
    Float_t metmin;
    Float_t metmax;
    Float_t metl1thresh;
    Float_t frac;
    TString ThreshFileName;
    TString MuonFileName;
    Int_t numberEventsToKeep;
    TString zerobiasFileName;
    Float_t AlgAIndividThresh;
    Float_t AlgBIndividThresh;
    TString muonFilename;
    Int_t NumPassnoalgPassProcess1;
    Int_t NumMuonPassProcess1;
    Int_t NumPassnoalgProcess2AlgA;
    Int_t NumPassnoalgProcess2AlgB;
    Int_t NumPassnoalgProcess2AlgCombined;
    Int_t NumMuonPassProcess2AlgA;
    Int_t NumMuonPassProcess2AlgB;
    Int_t NumMuonPassProcess2Combined;
    Float_t algAIndividThresh;
    Float_t algBIndividThresh;
    Float_t algACombinedThresh;
    Float_t algBCombinedThresh;
    Int_t muonNentries;
    Int_t passnoAlgNentries;
    Int_t numMuonKeptCombined;
    Int_t numMuonDenominator;
    Int_t epsilon;
    Float_t actintCut;
    TDatime now;
    Float_t BinWidth;
    Float_t passnoalgcut;


public:
    //default constructor
    userInfo();
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
