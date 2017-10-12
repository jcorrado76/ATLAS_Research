#include <iostream>
#include "TObject.h"
#include "TString.h"
#include "userInfo.h"


//#if !defined(__CLING__)
ClassImp(userInfo)
//#endif

#ifdef __CLING__
#pragma link C++ userInfo userInfo.h+;
#endif


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
Int_t epson = 25;

//default constructor
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
    epsilon = epson;
    numzbRndm = 0;
    algAThresh = 0.0;
    algBThresh = 0.0;
    numMuonPassNumeratorAlgA = 0;
    numMuonPassNumeratorAlgB = 0;
    algAName = " [not entered yet] ";
    algBName = " [not entered yet] ";
    muonNentries = 0;
    zbNentries = 0;
    numMuonKeptCombined = 0;
    numMuonPassNumeratorAlgA = 0;
    numMuonPassNumeratorAlgB = 0;
    numMuonPassNumeratorAlgC = 0;
    numMuonDenominator = 0;
}
//alternative constructor to initialize with the algorithm names
userInfo::userInfo( TString algA , TString algB)
{
    nbins = Nbins;
    metmin = metMin;
    metmax = metMax;
    metl1thresh = metl1Thresh;
    frac = Frac;
    zbFileName = zerobiasFileName;
    muonFileName = muonFilename;
    actintCut = actinTCut;
    epsilon = epson;
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

void userInfo::Print(Option_t *option) const{
    std::cout << "Printing the data members for the userInfo struct: \n" << std::endl;
    std::cout << "Alg A Name: " << algAName << std::endl;
    std::cout << "Alg B Name: " << algBName << std::endl;
    std::cout << "nbins: " << nbins << std::endl;
    std::cout << "MetMin: " << metmin << std::endl;
    std::cout << "MetMax: " << metmax << std::endl;
    std::cout << "METL1 thresh used: " << metl1thresh << std::endl;
    std::cout << "frac to keep: " << frac << std::endl;
    //TODO: we aren't using zero bias files
    std::cout << "Zero Bias File Used: " << zbFileName << std::endl;
    std::cout << "Muon File Used: " << muonFileName << std::endl;
    std::cout << "Number of zerobias events that passed no alg and metl1: " << numzbRndm << std::endl;
    std::cout << "\nThresholds needed to keep the proper trigger rate when combined: " << std::endl;
    //TODO: should clarify language between thresholds to keep trigger rate individually and then combined
    //      also should display the thresholds needed to keep individually, and then thresholds for combined
    std::cout << "Threshold needed on " + algAName + ": " << algAThresh << std::endl;
    std::cout << "Threshold needed on " + algBName + ": " << algBThresh << std::endl;
    std::cout << "Muon Nentries: " << muonNentries << std::endl;
    std::cout << "ZeroBias Nentries: " << zbNentries << std::endl;
    std::cout << "Number of entries kept using combined thresholds: " <<  numMuonKeptCombined << std::endl;
    std::cout << "Number of entries that passed all muon cuts and " + algAName + " at Individ thresh: " << numMuonPassNumeratorAlgA << std::endl;
    std::cout << "Number of entries that passed all muon cuts and " + algBName + " at Individ thresh: " << numMuonPassNumeratorAlgB << std::endl;
    std::cout << "Number of entries that passed all muon cuts and both algs at Combined thresh: " << numMuonPassNumeratorAlgC << std::endl;
    std::cout << "Number entries that passed all muon cuts without alg: " << numMuonDenominator << std::endl;
    std::cout << "Epsilon tolerance on number events used for bisection: " << epsilon << std::endl;
    std::cout << "Actint cut: " << actintCut << "\n" << std::endl;
}
//getters
TString userInfo::get_zbFileName() const { return(zbFileName);}
TString userInfo::get_muonFileName() const { return(muonFileName);}
Int_t userInfo::getNbins() const { return(nbins); }
Float_t userInfo::getMetL1Thresh() const { return( metl1thresh); }
Float_t userInfo::getActintCut() const { return( actintCut);}
Float_t userInfo::getFrac() const { return (frac); }
Float_t userInfo::getMetMin() const {return (metmin);}
Float_t userInfo::getMetMax() const { return (metmax);}
Int_t userInfo::getEpsilon() const {return(epsilon);}
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
void userInfo::setEpsilon( const Int_t epson ) { epsilon = epson; };
