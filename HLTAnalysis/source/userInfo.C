#include "userInfo.h"
#include <iostream>
#include "TObject.h"
#include "TString.h"

ClassImp(userInfo)

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
    passNoAlgFile = zerobiasFileName;
    muonFileName = muonFilename;
    actintCut = actinTCut;
    epsilon = epson;
    //event process initializations
    NumPassnoalgPassProcess1 = 0;
    NumMuonPassProcess1 = 0;

    NumPassnoalgProcess2AlgA = 0;
    NumPassnoalgProcess2AlgB = 0;
    NumPassnoalgProcess2AlgCombined = 0;

    NumMuonPassProcess2AlgA = 0;
    NumMuonPassProcess2AlgB = 0;
    NumMuonPassProcess2Combined = 0;

    //passnoalg thresholds are being used on muon algs as well
    //thresholds to separately keep trigger rate
    Float_t algAIndividThresh = 0;
    Float_t algBIndividThresh = 0;
    //thresholds such that combined keep trigger rate
    Float_t algACombinedThresh = 0;
    Float_t algBCombinedThresh = 0;
    algACombinedThresh = 0.0;
    algBCombinedThresh = 0.0;
    algAName = " [not entered yet] ";
    algBName = " [not entered yet] ";
    muonNentries = 0;
    passnoAlgNentries = 0;
    numMuonKeptCombined = 0;
    numMuonDenominator = 0;
    now = TDatime();
}

void userInfo::Print(Option_t *option) const{
    std::cout << "Printing the data members for the userInfo struct: \n" << std::endl;

    now.Print();
    std::cout << "Alg A Name: " << algAName << std::endl;
    std::cout << "Alg B Name: " << algBName << std::endl;
    std::cout << "nbins: " << nbins << std::endl;
    std::cout << "MetMin: " << metmin << std::endl;
    std::cout << "MetMax: " << metmax << std::endl;
    std::cout << "METL1 thresh used: " << metl1thresh << std::endl;
    std::cout << "Process 2 target frac: " << frac << std::endl;
    std::cout << "Passnoalg File: " << passNoAlgFile << std::endl;
    std::cout << "Muon File: " << muonFileName << std::endl;
    std::cout << "Number of passnoalg events that passed process1: " << NumPassnoalgPassProcess1 << std::endl;
    std::cout << "Numb passnoalg passed process2 for alg A: " << NumPassnoalgProcess2AlgA << std::endl;
    std::cout << "Numb passnoalg passed process2 for alg B: " << NumPassnoalgProcess2AlgB << std::endl;
    std::cout << "Numb passnoalg passed process2 for combined alg: " << NumPassnoalgProcess2AlgCombined << std::endl;

    std::cout << "Thresholds needed to keep trigger rate individually: " << std::endl;
    std::cout << "Individ Threshold needed on " + algAName + ": " << algAIndividThresh << std::endl;
    std::cout << "Individ Threshold needed on " + algBName + ": " << algBIndividThresh << std::endl;
    std::cout << "\nThresholds needed to keep the proper trigger rate when combined: " << std::endl;
    std::cout << "Combined Threshold needed on " + algAName + ": " << algACombinedThresh << std::endl;
    std::cout << "Combined Threshold needed on " + algBName + ": " << algBCombinedThresh << std::endl;
    std::cout << "Muon Nentries: " << muonNentries << std::endl;
    std::cout << "Passnoalg Nentries: " << passnoAlgNentries << std::endl;
    std::cout << "Number of entries kept using combined thresholds: " <<  numMuonKeptCombined << std::endl;
    std::cout << "Numb passed process 2 for " + algAName + " separately: "
    << NumMuonPassProcess2AlgA << std::endl;
    std::cout << "Numb passed process 2 for " + algBName + " separately: "
    << NumMuonPassProcess2AlgB << std::endl;
    std::cout << "Numb passed process 2 Combined: "
    << NumMuonPassProcess2Combined << std::endl;
    std::cout << "Nentries Efficiency Denominator: " << numMuonDenominator << std::endl;
    std::cout << "Epsilon tolerance on number events used for bisection: " << epsilon << std::endl;
    std::cout << "Actint cut: " << actintCut << "\n" << std::endl;

}
//getters
TString userInfo::get_passnoalgFileName() const { return(passNoAlgFile);}
TString userInfo::get_muonFileName() const { return(muonFileName);}
Int_t userInfo::getNbins() const { return(nbins); }
Float_t userInfo::getMetL1Thresh() const { return( metl1thresh); }
Float_t userInfo::getActintCut() const { return( actintCut);}
Float_t userInfo::getFrac() const { return (frac); }
Float_t userInfo::getMetMin() const {return (metmin);}
Float_t userInfo::getMetMax() const { return (metmax);}
Int_t userInfo::getEpsilon() const {return(epsilon);}
TDatime userInfo::getDate() const { now.Print();return(now);};
TString userInfo::getAlgAName() const { return (algAName);}
TString userInfo::getAlgBName() const { return (algBName);}
Int_t userInfo::getMuonNentries() const { return(muonNentries);}
Int_t userInfo::getThreshNentries() const { return (passnoAlgNentries) ; }


//setters
void userInfo::setAlgAName( const TString algA ) { algAName = algA; };
void userInfo::setAlgBName( const TString algB ) { algBName = algB; };
//set all process 1's, they're same across 3 algs for passnoalgs and muons, respectively
void userInfo::setNumPassNoAlgPassProcess1( const Float_t num ) {NumPassnoalgPassProcess1 = num;};
void userInfo::setNumMuonPassProcess1( const Float_t num ) {NumMuonPassProcess1 = num;};
//set passnoalgs process 2
void userInfo::setNumPassNoAlgPassProcess2AlgA( const Float_t num ) {NumPassnoalgProcess2AlgA = num;};
void userInfo::setNumPassNoAlgPassProcess2AlgB( const Float_t num ) {NumPassnoalgProcess2AlgB = num;};
void userInfo::setNumPassNoAlgPassProcess2Combined( const Float_t num ) {NumPassnoalgProcess2AlgCombined = num;};
//set muons process 2
void userInfo::setNumMuonPassProcess2AlgA( const Float_t num ) {NumMuonPassProcess2AlgA = num;};
void userInfo::setNumMuonPassProcess2AlgB( const Float_t num ) {NumMuonPassProcess2AlgB = num;};
void userInfo::setNumMuonPassProcess2Combined( const Float_t num ) {NumMuonPassProcess2Combined = num;};
//set thresholds
void userInfo::setAlgAIndividThresh( const Float_t thresh ) { algAIndividThresh = thresh; };
void userInfo::setAlgBIndividThresh( const Float_t thresh ) { algBIndividThresh = thresh; };
void userInfo::setAlgACombinedThresh( const Float_t thresh ) { algACombinedThresh = thresh; };
void userInfo::setAlgBCombinedThresh( const Float_t thresh ) { algBCombinedThresh = thresh; };
//set nentries
void userInfo::setMuonNentries( const Int_t num ) { muonNentries = num; };
void userInfo::set_PassnoalgNentries( const Int_t num ) { passnoAlgNentries = num; };
//set actual numb muon events kept process 2
void userInfo::setNumMuonKeptCombinedAtThresh( const Int_t num ) { numMuonKeptCombined = num; };
void userInfo::setNumTotal( const Int_t num ) { numMuonDenominator = num; };
void userInfo::setActintCut( const Float_t thresh ) { actintCut = thresh; };
void userInfo::setEpsilon( const Int_t epson ) { epsilon = epson; };
