#include <iostream>
#include "TObject.h"
#include "TString.h"

//TODO: add in a collection of TCut objects reflecting the parameters
//      so that if we need to do some treee analysis, there's an easy way to draw the tree using a
//      specific cut that was used during a given run without having to look into the file and see its
//      numeric value

//TODO: create a constructor that takes the two algs to be used as args for initialization


Int_t Nbins = 1200;
Float_t metMin = 0.0;
Float_t metMax = 300.0;
Float_t metl1Thresh = 50.0;
Float_t Frac = 0.0059;
TString zerobiasFileName = "PhysicsMain.All.noalgXEtriggers.2016.f731f758._m1659m1710.48Runs.root";
TString muonFilename = "PhysicsMain.L1KFmuontriggers.2016.f731f758_m1659m1710.Run309759.48Runs.root";
Float_t actinTCut = 35.0;
Int_t epsilon = 25;


    userInfo::userInfo()
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
    //getters
    TString userInfo::get_zbFileName() const { return(zbFileName);}
    TString userInfo::get_muonFileName() const { return(muonFileName);}
    Float_t userInfo::getMetL1Thresh() const { return( metl1thresh); }
    Float_t userInfo::getActintCut() const { return( actintCut);}
    Float_t userInfo::getFrac() const { return (frac); }
    Float_t userInfo::getMetMin() const {return (metmin);}
    Float_t userInfo::getMetMax() const { return (metmax);}
    //setters
    void userInfo::setAlgAName( const TString algA ) { algAName = algA; };
    void userInfo::setAlgBName( const TString algB ) { algBName = algB; };
    void userInfo::setNum_zbRndm( const Float_t num ) { numzbRndm = num; };
    void userInfo::setAlgAThresh( const Float_t thresh ) { algAThresh = thresh; };
    void userInfo::setAlgBThresh( const Float_t thresh ) { algBThresh = thresh; };
    void userInfo::setMuonNentries( const Int_t num ) { muonNentries = num; };
    void userInfo::set_zbNentries( const Int_t num ) { zbNentries = num; };
    void userInfo::setNumMuonKeptCombined( const Int_t num ) { numMuonKeptCombined = num; };
    void userInfo::setNumPassA( const Int_t num ) { numMuonPassNumeratorAlgA = num; };
    void userInfo::setNumPassB( const Int_t num ) { numMuonPassNumeratorAlgB = num; };
    void userInfo::setNumPassCombined( const Int_t num ) { numMuonPassNumeratorAlgC = num; };
    void userInfo::setNumTotal( const Int_t num ) { numMuonDenominator = num; };
    void userInfo::setActintCut( const Float_t thresh ) { actintCut = thresh; };

#if !defined(__CLING__)
ClassImp(userInfo)
#endif




void userInfo::Print() const{
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
