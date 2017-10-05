#include "userInfo.h"
#include <iostream>



//TODO: import this file into threeEfficiencies, bisection, and

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
    eps = 25;
}


void userInfo::Print()
{
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
}


//}
