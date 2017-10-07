#ifndef userInfo_h
#define userInfo_h

#include <iostream>
#include "Rtypes.h"
#include "TObject.h"
#include "TString.h"

Int_t Nbins = 1200;
Float_t metMin = 0.0;
Float_t metMax = 300.0;
Float_t metl1Thresh = 50.0;
Float_t Frac = 0.0059;
TString zerobiasFileName = "PhysicsMain.All.noalgXEtriggers.2016.f731f758._m1659m1710.48Runs.root";
TString muonFilename = "PhysicsMain.L1KFmuontriggers.2016.f731f758_m1659m1710.Run309759.48Runs.root";
Float_t actinTCut = 35.0;
Int_t epsilon = 25;

class userInfo : public TObject {
private:
    TString algAName;
    TString algBName;
    Int_t nbins;
    Float_t metmin;
    Float_t metmax;
    Float_t metl1thresh;
    Float_t frac;
    TString zbFileName;
    TString muonFileName;
    Int_t numzbRndm;
    Float_t algAThresh;
    Float_t algBThresh;
    Int_t muonNentries;
    Int_t zbNentries;
    Int_t numMuonKeptCombined;
    Int_t numMuonPassNumeratorAlgA;
    Int_t numMuonPassNumeratorAlgB;
    Int_t numMuonPassNumeratorAlgC;
    Int_t numMuonDenominator;
    Float_t eps;
    Float_t actintCut;
public:
    //default constructor
    userInfo()
    {
        nbins = Nbins;
        metmin = metMin;
        metmax = metMax;
        metl1thresh = metl1Thresh;
        frac = Frac;
        zbFileName = zerobiasFileName;
        muonFileName = muonFilename;
        actintCut = actinTCut;
        eps = 25;
        numzbRndm = 0;
        algAThresh = 0.0;
        algBThresh = 0.0;
        numMuonPassNumeratorAlgA = 0;
        numMuonPassNumeratorAlgB = 0;
        algAName = " [not entered yet] ";
        algBName = " [not entered yet] ";
    }
    //destructor
    ~userInfo();
    void Print() const;
    //getters
    TString get_zbFileName() const { return(zbFileName); };
    TString get_muonFileName() const { return( muonFileName ); };
    //setters
    void setAlgAName( const TString algA ) { algAName = algA; };
    void setAlgBName( const TString algB ) { algBName = algB; };
    void setNum_zbRndm( const Float_t num ) { numzbRndm = num; };
    void setAlgAThresh( const Float_t thresh ) { algAThresh = thresh; };
    void setAlgBThresh( const Float_t thresh ) { algBThresh = thresh; };
    void setMuonNentries( const Int_t num ) { muonNentries = num; };
    void set_zbNentries( const Int_t num ) { zbNentries = num; };
    void setNumMuonKeptCombined( const Int_t num ) { numMuonKeptCombined = num; };
    void setNumPassA( const Int_t num ) { numMuonPassNumeratorAlgA = num; };
    void setNumPassB( const Int_t num ) { numMuonPassNumeratorAlgB = num; };
    void setNumPassCombined( const Int_t num ) { numMuonPassNumeratorAlgC = num; };
    void setNumTotal( const Int_t num ) { numMuonDenominator = num; };
    void setActintCut( const Float_t thresh ) { actintCut = threh; };




    //this macro from Rtypes.h facilitates root I/O
    ClassDef( userInfo, 1);

};

#if !defined(__CLING__)
ClassImp(userInfo)
#endif


#endif
