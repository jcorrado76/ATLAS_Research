#include "TObject.h"

class userInfo : public TObject {
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
    void Print()
    {
        std::cout << "Alg A Name: " << algAName << std::endl;
        std::cout << "Alg B Name: " << algBName << std::endl;
        std::cout << "nbins: " << nbins << std::endl;
        std::cout << "MetMin: " << metmin << std::endl;
        std::cout << "MetMax: " << metmax << std::endl;
        std::cout << "METL1 thresh used: " << metl1thresh << std::endl;
        std::cout << "frac to keep: " << frac << std::endl;
        std::cout << "Zero Bias File Used: " << zbFileName << std::endl;
        std::cout << "Muon File Used: " << muonFilename << std::endl;
        std::cout << "Number of zerobias events that passed no alg and metl1: " << numzbRndm << std::endl;
        std::cout << "Threshold needed on A: " << algAThresh << std::endl;
        std::cout << "Threshold needed on B: " << algBThresh << std::endl;
        std::cout << "Muon Nentries: " << muonNentries << std::endl;
        std::cout << "ZeroBias Nentries: " << zbNentries << std::endl;
        std::cout << "Number of entries kept using combined thresholds: " <<  numMuonKeptCombined << std::endl;
        std::cout << "Number of entries that passed all muon cuts and " + algAName + " at Individ thresh: " << numMuonPassNumeratorAlgA << std::endl;
        std::cout << "Number of entries that passed all muon cuts and " + algBName + " at Individ thresh: " << numMuonPassNumeratorAlgB << std::endl;
        std::cout << "Number of entries that passed all muon cuts and both algs at Combined thresh: " << numMuonPassNumeratorAlgC << std::endl;
    }
};
