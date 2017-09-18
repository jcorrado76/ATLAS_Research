#include "TMath.h"
#include "TH1.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TEfficiency.h"
#include "TLegend.h"
#include <iostream>
#include <fstream>
#include "TROOT.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TF1.h"

Float_t computeThresh(TH1F* target, Float_t numberEventsToKeep)
{
    Int_t nbin = 0;
    target->GetBinWithContent( numberEventsToKeep , nbin , 0 , -1 , 20000 ); //if firstx<=0{firstx=1}; if lastx<firstx{lastx=fXaxis.GetNbinsX()};
    Float_t thresh = (target->GetXaxis())->GetBinCenter(nbin);
    return(thresh);
}


Float_t determineZeroBiasThresh( const TString& alg, const Float_t frac = 0.00590,
const TString& zeroBiasFileName = "PhysicsMain.All.noalgXEtriggers.2016.f731f758._m1659m1710.48Runs")
{

    TString zeroBiasPath = "../myData/" + zeroBiasFileName;
    //display inputs
    std::cout << "DETERMINETHRESH.C" << std::endl;
    std::cout << "ZERO BIAS DATAFILE: " << zeroBiasPath << std::endl;
    std::cout << "ALG: " << alg << std::endl;
    std::cout << "L1 THRESH: " << myConstants::metl1thresh << std::endl;

    //get zeorbias tree
	TFile *zeroBiasFile = TFile::Open(zeroBiasPath, "READ");
	TTree *zeroBiasTree = (TTree*)(zeroBiasFile->Get("tree"));

    //intialize useful parameters
    Float_t numberEventsToKeep = 5762.0;
	Int_t zerobiasNentries = zeroBiasTree->GetEntries();
	Int_t nbins = myConstants::nbins;
	Double_t metMin = myConstants::metMin;
	Double_t metMax = myConstants::metMax;
    Float_t metl1thresh = myConstants::metl1thresh;
	Float_t metl1, metcell, metmht, mettopocl, mettopoclps, mettopoclpuc, indeterminate,
	metcellthresh, metmhtthresh, mettopoclthresh, mettopoclpsthresh, mettopoclpucthresh,rightHandSum;
    Int_t passnoalgL1XE10 , passnoalgL1XE30 , passnoalgL1XE40 , passnoalgL1XE45 ;
    TH1F *indeterminateHist = new TH1F(alg, alg, nbins, metMin, metMax);

    //set branch address for zb variables
	zeroBiasTree->SetBranchAddress(alg,&indeterminate);
	zeroBiasTree->SetBranchAddress("metl1",&metl1);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE10",&passnoalgL1XE10);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE30",&passnoalgL1XE30);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE40",&passnoalgL1XE40);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE45",&passnoalgL1XE45);

    for (Int_t k = 0; k < zerobiasNentries; k++)
	{
		zeroBiasTree->GetEntry(k);
		if (( ( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 || passnoalgL1XE40 > 0.5 ||
            passnoalgL1XE45 > 0.5 ) && ( metl1 > metl1thresh ) ))
		{
			indeterminateHist->Fill(indeterminate);
		}

    }
	std::cout << "FRACTION: " << frac << std::endl;
	std::cout << "ZEROBIAS NENTRIES: " << zerobiasNentries << std::endl;

    TH1F *indeterminatetarget = (TH1F*) indeterminateHist->GetCumulative(kFALSE);
	Float_t indeterminateThresh = computeThresh(indeterminatetarget, numberEventsToKeep);
	std::cout << alg << " THRESHOLD: " << indeterminateThresh << std::endl;
	std::cout << "Number of events that should have been kept: " << numberEventsToKeep << std::endl;
	std::cout << "Checking how many events are kept by the alg at the determined threshold..." << std::endl;
	Int_t counter=0;
	for (Int_t l = 0 ; l < zerobiasNentries ; l++)
	{
		zeroBiasTree->GetEntry(l);
		if (( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 || passnoalgL1XE40 > 0.5 ||
            passnoalgL1XE45 > 0.5 ) && (indeterminate > indeterminateThresh) && (metl1 > metl1thresh))
		{
			counter++;
		}
	}
	zeroBiasFile->Close();
	std::cout << "Number of events counted above threshold: " << counter << "\n" << std::endl;
	return(indeterminateThresh);
}
