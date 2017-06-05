Float_t determineThresh(TString& all = "y", Float_t frac = (1.e-4),TString& dataFile = "ZeroBias2016new.13Runs.root")
{
	#include <string>
	gROOT->ProcessLine("gROOT->Reset();");
	using namespace std;
	std::cout << "Entering determineThresh.c" << std::endl;
	TString fileName = "../myData/" + dataFile;
	std::cout << "DATAFILE: " << fileName << std::endl;
	TFile *myFile = TFile::Open(fileName, "READ");
	Int_t nentries = tree->GetEntries();
	Int_t nbins = 400;
	Int_t numRndm = 0;
	Int_t passrndm;
	Double_t metMin = 0.0;
	Double_t metMax = 500.0;
	Float_t metl1, metcell, metmht, mettopocl, mettopoclps, mettopoclpuc, metoffrecal,indeterminate,
	metl1thresh, metcellthresh, metmhtthresh, mettopoclthresh, mettopoclpsthresh, mettopoclpucthresh,
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
/*
		std::ofstream log_file("DetermineThreshLog.txt", std::ios_base::out | std::ios_base::app );
		log_file << "Accessed: " << currentDateTime() << std::endl;
		log_file << "DATAFILE: " << fileName << "\tFRACTION: " << frac << std::endl;
		log_file << "NBINS: " << nbins << "NUMRNDM:" << numRndm << std::endl;
		log_file << "METL1 THRESH: " << metl1thresh << std::endl;
		log_file << "METCELL THRESH: " << metcellthresh << std::endl;
		log_file << "METMHT THRESH: "<< metmhtthresh << std::endl;
		log_file << "METTOPOCL THRESH: " << mettopoclthresh << std::endl;
		log_file << "METTOPOCLPS THRESH: " << mettopoclpsthresh << std::endl;
		log_file << "METTOPOCLPUC THRESH: " << mettopoclpucthresh << std::endl;
		log_file << "\n" << std::endl;*/
	}

	if (all != "y") //only compute thresh for one alg
	{
		TH1F *indeterminateHist = new TH1F(all, all, nbins, metMin, metMax);
		TH1F *indeterminatetarget = new TH1F("cumu7", "cumu", nbins, metMin, metMax);
		tree->SetBranchAddress(all,&indeterminate);
		std::cout << all << " SELECTED..." << std::endl;
		for (Int_t k = 0; k < nentries; k++)
		{
			tree->GetEntry(k);
			if (passrndm > 0.1)
			{
				numRndm++;
				indeterminateHist->Fill(indeterminate);
			}
		}
		computeTarget(indeterminateHist,indeterminatetarget,nbins);
		Float_t numKeep = numRndm * frac;
		indeterminatethresh = computeThresh(indeterminatetarget, numKeep, nbins);
		std::cout << all << " THRESHOLD: " << indeterminatethresh << std::endl;
/*
		std::ofstream log_file("DetermineThreshLog.txt", std::ios_base::out | std::ios_base::app );
		log_file << "Accessed: " << currentDateTime() << std::endl;
		log_file << "DATAFILE: " << fileName << "\tFRACTION: " << frac << std::endl;
		log_file << "NBINS: " << nbins << "NUMRNDM:" << numRndm << std::endl;
		log_file << "ALG: " << all << "THRESH: " << indeterminatethresh << std::endl;
		log_file << "\n" << std::endl;
*/
	}
	std::cout << "EVENTS KEPT: " << frac * numRndm << std::endl;
	myFile.Close();
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
		if ((abs(target->GetBinContent(t) - (numKeep) > 0) != (abs(target->GetBinContent(t + 1) - (numKeep)) > 0)))
		{
			thresh = target->GetBinCenter(t);
		}
	}
	return(thresh);
}
/*
std::string currentDateTime()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return buf;
}
*/
