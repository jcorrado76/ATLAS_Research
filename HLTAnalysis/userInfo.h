
#ifndef userInfo_h
#define userInfo_h

#include "TObject.h"
#include "TString.h"
#include "TDatime.h"


class userInfo : public TObject {
private:
    TString algAName;
    TString algBName;
    Int_t nbins;
    Float_t metmin;
    Float_t metmax;
    Float_t metl1thresh;
    Float_t frac;
    TString passNoAlgFile;
    TString muonFileName;

    Int_t NumPassnoalgPassProcess1;
    Int_t NumMuonPassProcess1;

    Int_t NumPassnoalgProcess2AlgA;
    Int_t NumPassnoalgProcess2AlgB;
    Int_t NumPassnoalgProcess2AlgCombined;

    Int_t NumMuonPassProcess2AlgA;
    Int_t NumMuonPassProcess2AlgB;
    Int_t NumMuonPassProcess2Combined;

    //passnoalg thresholds are being used on muon algs as well
    //thresholds to separately keep trigger rate
    Float_t algAIndividThresh;
    Float_t algBIndividThresh;
    //thresholds such that combined keep trigger rate
    Float_t algACombinedThresh;
    Float_t algBCombinedThresh;
    Int_t muonNentries;
    Int_t passnoAlgNentries;
    Int_t numMuonKeptCombined;
    Int_t numMuonDenominator;
    Int_t epsilon;
    Float_t actintCut;
    TDatime now;
public:
    //default constructor
    userInfo();
    //destructor
    void Print(Option_t *option = "") const;
    //getters
    TString get_passnoalgFileName() const;
    TString get_muonFileName() const;
    Float_t getMetL1Thresh() const;
    Float_t getActintCut() const;
    Float_t getFrac() const;
    Float_t getMetMin() const;
    Float_t getMetMax() const;
    Int_t getNbins() const;
    Int_t getEpsilon() const;
    TDatime getDate() const;
    //setters
    void setAlgAName( const TString algA );
    void setAlgBName( const TString algB );

    void setNumPassNoAlgPassProcess1( const Float_t num );
    void setNumMuonPassProcess1( const Float_t num );

    void setNumPassNoAlgPassProcess2AlgA( const Float_t num );
    void setNumPassNoAlgPassProcess2AlgB( const Float_t num );
    void setNumPassNoAlgPassProcess2Combined( const Float_t num );

    void setNumMuonPassProcess2AlgA( const Float_t num );
    void setNumMuonPassProcess2AlgB( const Float_t num );
    void setNumMuonPassProcess2Combined( const Float_t num );

    void setAlgAIndividThresh( const Float_t thresh );
    void setAlgBIndividThresh( const Float_t thresh );
    void setAlgACombinedThresh( const Float_t thresh );
    void setAlgBCombinedThresh( const Float_t thresh );
    void setMuonNentries( const Int_t num );
    void set_PassnoalgNentries( const Int_t num );
    void setNumMuonKeptCombinedAtThresh( const Int_t num );
    void setNum_PassProcess2AlgA( const Int_t num );
    void setNum_PassProcess2AlgB( const Int_t num );
    void setNum_PassProcess2Combined( const Int_t num );
    void setNumTotal( const Int_t num );
    void setActintCut( const Float_t thresh );
    void setEpsilon( const Int_t epsilon );

    //this macro from Rtypes.h facilitates root I/O
    ClassDef( userInfo, 1)
};

#ifndef __CINT__
extern userInfo* logFileParams;
#endif

#endif
