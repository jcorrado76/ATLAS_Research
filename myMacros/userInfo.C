#include "userInfo.h"
#include <iostream>

void userInfo::Print() const
{
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
