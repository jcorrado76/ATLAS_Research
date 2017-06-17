#include <string>
#include <cmath>
#include <math.h>
#include "TMath.h"
#include "TH1.h"
#include "TFile.h"
#include "TString.h"
#include "TTree.h"
#include "TROOT.h"
#include <iostream>


Float_t determineThresh( const TString& all = "y", const Float_t frac = (1.e-4), Float_t metl1thresh = 0.0, const TString& dataFile = "ZeroBias2016R307195R311481Runs56.root")
{
	//FUNCTION PROTOTYPES
	TH1F* computeTarget(TH1F*,TH1F*,Int_t);
	Float_t computeThresh(TH1F*,Float_t,Int_t);
	gROOT->ProcessLine("gROOT->Reset();");
	cout << "Entering determineThresh.c" << std::endl;
	TString fileName = "../myData/" + dataFile;
	std::cout << "DATAFILE: " << fileName << std::endl;
	TFile *myFile = TFile::Open(fileName, "READ");
	TTree *tree = (TTree*)myFile->Get("tree");
	Int_t nentries = tree->GetEntries();
	Int_t nbins = 400;
	Int_t numRndm = 0;
	Int_t passrndm;
	Double_t metMin = 0.0;
	Double_t metMax = 500.0;
	Float_t metl1, metcell, metmht, mettopocl, mettopoclps, mettopoclpuc, metoffrecal,indeterminate,
	metcellthresh, metmhtthresh, mettopoclthresh, mettopoclpsthresh, mettopoclpucthresh,
	indeterminatethresh,rightHandSum;
	TString xlabel = "MET [GeV]";
	TString yaxis = "Events";
	tree->SetBranchAddress("passrndm", &passrndm);
	std::cout << "FRACTION: " << frac << std::endl;
	std::cout << "NENTRIES: " << nentries << std::endl;

	if (all == "y")
	{
		TH1F *metl1Hist         = new TH1F("metl1", "metl1", nbins, metMin, metMax);;
		TH1F *metcellHist       = new TH1F("metcell", "metcell", nbins, metMin, metMax);
		TH1F *metmhtHist        = new TH1F("metmht", "metmht", nbins, metMin, metMax);
		TH1F *mettopoclHist     = new TH1F("mettopocl", "mettopocl", nbins, metMin, metMax);
		TH1F *mettopoclpsHist   = new TH1F("mettopoclps", "mettopoclps", nbins, metMin, metMax);
		TH1F *mettopoclpucHist  = new TH1F("mettopoclpuc", "mettopoclpuc", nbins, metMin, metMax);
		TH1F *metl1target         = new TH1F("cumu1", "cumu", nbins, metMin, metMax);;
		TH1F *metcelltarget       = new TH1F("cumu2", "cumu", nbins, metMin, metMax);
		TH1F *metmhttarget        = new TH1F("cumu3", "cumu", nbins, metMin, metMax);
		TH1F *mettopocltarget     = new TH1F("cumu4", "cumu", nbins, metMin, metMax);
		TH1F *mettopoclpstarget   = new TH1F("cumu5", "cumu", nbins, metMin, metMax);
		TH1F *mettopoclpuctarget  = new TH1F("cumu6", "cumu", nbins, metMin, metMax);
		tree->SetBranchAddress("metl1", &metl1);
		tree->SetBranchAddress("metcell", &metcell);
		tree->SetBranchAddress("metmht", &metmht);
		tree->SetBranchAddress("mettopocl", &mettopocl);
		tree->SetBranchAddress("mettopoclps", &mettopoclps);
		tree->SetBranchAddress("mettopoclpuc", &mettopoclpuc);
		tree->SetBranchAddress("metoffrecal", &metoffrecal);
		std::cout << "ALL ALGORITHMS SELECTED..." << std::endl;
		for (Int_t k = 0; k < nentries; k++)
		{
			tree->GetEntry(k);
			if (passrndm > 0.1)
			{
				numRndm++;
				metl1Hist->Fill(metl1);
				metcellHist->Fill(metcell);
				metmhtHist->Fill(metmht);
				mettopoclHist->Fill(mettopocl);
				mettopoclpsHist->Fill(mettopoclps);
				mettopoclpucHist->Fill(mettopoclpuc);
			}
		}
	
		Float_t numKeep = numRndm * frac;
	
		computeTarget(metl1Hist,metl1target,nbins);
		metl1thresh = computeThresh(metl1target, numKeep, nbins);
	
		computeTarget(metcellHist,metcelltarget,nbins);
		metcellthresh = computeThresh(metcelltarget, numKeep, nbins);
	
		computeTarget(metmhtHist,metmhttarget,nbins);
		metmhtthresh = computeThresh(metmhttarget, numKeep, nbins);
	
		computeTarget(mettopoclHist,mettopocltarget,nbins);
		mettopoclthresh = computeThresh(mettopocltarget, numKeep, nbins);
	
		computeTarget(mettopoclpsHist,mettopoclpstarget,nbins);
		mettopoclpsthresh = computeThresh(mettopoclpstarget, numKeep, nbins);
	
		computeTarget(mettopoclpucHist,mettopoclpuctarget,nbins);
		mettopoclpucthresh = computeThresh(mettopoclpuctarget, numKeep, nbins);
	
		std::cout << "METL1 THRESHOLD: " << metl1thresh << std::endl;
		std::cout << "METCELL THRESHOLD: " << metcellthresh << std::endl;
		std::cout << "METMHT THRESHOLD: " << metmhtthresh << std::endl;
		std::cout << "METTOPOCL THRESHOLD: " << mettopoclthresh << std::endl;
		std::cout << "METTOPOCLPS THRESHOLD: " << mettopoclpsthresh << std::endl;
		std::cout << "METTOPOCLPUC THRESHOLD: " << mettopoclpucthresh << std::endl;
	}

	if (all != "y") //only compute thresh for one alg
	{
		TH1F *indeterminateHist = new TH1F(all, all, nbins, metMin, metMax);
		TH1F *indeterminatetarget = new TH1F("cumu7", "cumu", nbins, metMin, metMax);
		tree->SetBranchAddress(all,&indeterminate);
		tree->SetBranchAddress("metl1",&metl1);
		std::cout << all << " SELECTED..." << std::endl;
		std::cout << "Computing number to keep after cutting on metl1 at thresh: " << metl1thresh << std::endl;
		for (Int_t k = 0; k < nentries; k++)
		{
			tree->GetEntry(k);
			if ((passrndm > 0.1) && (metl1 >= metl1thresh))
			{
				numRndm++;
				indeterminateHist->Fill(indeterminate);
			}
		}

		computeTarget(indeterminateHist,indeterminatetarget,nbins);
		Float_t numKeep = numRndm * frac;

		indeterminatethresh = computeThresh(indeterminatetarget, numKeep, nbins);
		std::cout << all << " THRESHOLD: " << indeterminatethresh << std::endl;
	}
	std::cout << "Number of events that should have been kept: " << frac * numRndm << std::endl;
	std::cout << "Checking how many events are kept by the alg at the determined threshold..." << std::endl;
	int counter=0;
	for (int l = 0 ; l < nentries ; l++)
	{
		tree->GetEntry(l);
		if ((passrndm > 0.5) && ((indeterminate >= ( indeterminatethresh - ( ( metMax - metMin ) / ( 2 * nbins ))))))//count the event if its geq left edge of bin (we use center for thresh)
		{
			counter++;
		}
	}
	myFile->Close();
	std::cout << "Number of events counted above threshold: " << counter << std::endl;
	return(indeterminatethresh);
}


//HELPER FUNCTIONS
TH1F* computeTarget(TH1F* hist , TH1F* target, Int_t nbins)
{
	for (Int_t t = nbins; t >= 0; t--)
	{
		Float_t rightHandSum = hist->Integral(t,nbins); //compute t'th target bin
		target->SetBinContent(t, rightHandSum);
	}
	return(target);
}

Float_t computeThresh(TH1F* target, Float_t numKeep, Int_t nbins)
{
	Float_t thresh;
	for (Int_t t = nbins; t >= 0; t--)
	{
		if ((target->GetBinContent(t) - (numKeep) > 0) != (target->GetBinContent(t + 1) - (numKeep) > 0))
		{
			thresh = target->GetBinCenter(t);
		}
	}
	return(thresh);
}
























