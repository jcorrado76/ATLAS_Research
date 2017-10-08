#include <iostream>
#include "TObject.h"
#include "TString.h"

//TODO: add in a collection of TCut objects reflecting the parameters
//      so that if we need to do some treee analysis, there's an easy way to draw the tree using a
//      specific cut that was used during a given run without having to look into the file and see its
//      numeric value

TString zerobiasFileName = "PhysicsMain.All.noalgXEtriggers.2016.f731f758._m1659m1710.48Runs.root";
TString muonFilename = "PhysicsMain.L1KFmuontriggers.2016.f731f758_m1659m1710.Run309759.48Runs.root";
Int_t Nbins = 1200;
Float_t metMin = 0.0;
Float_t metMax = 300.0;
Float_t metl1Thresh = 50.0;
Float_t Frac = 0.0059;
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
        eps = epsilon;
        numzbRndm = 0;
        algAThresh = 0.0;
        algBThresh = 0.0;
        numMuonPassNumeratorAlgA = 0;
        numMuonPassNumeratorAlgB = 0;
        algAName = " [not entered yet] ";
        algBName = " [not entered yet] ";
        muonNentries = 0;
        zbNentries = 0;
        numMuonPassNumeratorAlgA = 0;
        numMuonPassNumeratorAlgB = 0;
        numMuonPassNumeratorAlgC = 0;
        numMuonDenominator = 0;
    }
    userInfo( TString algA , TString algB)
    {
        nbins = Nbins;
        metmin = metMin;
        metmax = metMax;
        metl1thresh = metl1Thresh;
        frac = Frac;
        zbFileName = zerobiasFileName;
        muonFileName = muonFilename;
        actintCut = actinTCut;
        eps = epsilon;
        numzbRndm = 0;
        algAThresh = 0.0;
        algBThresh = 0.0;
        numMuonPassNumeratorAlgA = 0;
        numMuonPassNumeratorAlgB = 0;
        algAName = algA;
        algBName = algB;
        muonNentries = 0;
        zbNentries = 0;
        numMuonPassNumeratorAlgA = 0;
        numMuonPassNumeratorAlgB = 0;
        numMuonPassNumeratorAlgC = 0;
        numMuonDenominator = 0;
    }
    //destructor
    ~userInfo();

    void Print() const{
        std::cout << "Printing the data members for the userInfo struct: " << std::endl;
        std::cout << "Alg A Name: " << algAName << std::endl;
        std::cout << "Alg B Name: " << algBName << std::endl;
        std::cout << "nbins: " << nbins << std::endl;
        std::cout << "MetMin: " << metmin << std::endl;
        std::cout << "MetMax: " << metmax << std::endl;
        std::cout << "METL1 thresh used: " << metl1thresh << std::endl;
        std::cout << "frac to keep: " << frac << std::endl;
        std::cout << "Zero Bias File Used: " << zbFileName << std::endl;
        std::cout << "Muon File Used: " << muonFileName << std::endl;
        std::cout << "Number of zerobias events that passed no alg and metl1: " << numzbRndm << std::endl;
        std::cout << "Threshold needed on A: " << algAThresh << std::endl;
        std::cout << "Threshold needed on B: " << algBThresh << std::endl;
        std::cout << "Muon Nentries: " << muonNentries << std::endl;
        std::cout << "ZeroBias Nentries: " << zbNentries << std::endl;
        std::cout << "Number of entries kept using combined thresholds: " <<  numMuonKeptCombined << std::endl;
        std::cout << "Number of entries that passed all muon cuts and " + algAName + " at Individ thresh: " << numMuonPassNumeratorAlgA << std::endl;
        std::cout << "Number of entries that passed all muon cuts and " + algBName + " at Individ thresh: " << numMuonPassNumeratorAlgB << std::endl;
        std::cout << "Number of entries that passed all muon cuts and both algs at Combined thresh: " << numMuonPassNumeratorAlgC << std::endl;
        std::cout << "Number entries that passed all muon cuts without alg: " << numMuonDenominator << std::endl;
        std::cout << "Epsilon tolerance on number events used for bisection: " << eps << std::endl;
        std::cout << "Actint cut: " << actintCut << "\n" << std::endl;
    }
    //getters
    TString get_zbFileName() const { return(zbFileName);}
    TString get_muonFileName() const { return(muonFileName);}
    Float_t getMetL1Thresh() const { return( metl1thresh); }
    Float_t getActintCut() const { return( actintCut);}
    Float_t getFrac() const { return (frac); }
    Float_t getMetMin() const {return (metmin);}
    Float_t getMetMax() const { return (metmax);}
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
    void setActintCut( const Float_t thresh ) { actintCut = thresh; };

    //this macro from Rtypes.h facilitates root I/O
    ClassDef( userInfo, 1);
};

#if !defined(__CLING__)
ClassImp(userInfo)
#endif
