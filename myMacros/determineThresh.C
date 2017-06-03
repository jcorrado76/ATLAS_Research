Float_t determineThresh(TString& all = "y", Float_t frac = (1.e-4))
{
	gROOT->ProcessLine("gROOT->Reset();");
	using namespace std;
	TString fileName = "../myData/ZeroBias2016new.13Runs.root";
	std::cout << "Entering determineThresh.c for " << all << std::endl;
	std::cout << "Determining thresholds using data: " << fileName << std::endl;
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
	TH1F *metl1Hist         = new TH1F("metl1", "metl1", nbins, metMin, metMax);;
	TH1F *metcellHist       = new TH1F("metcell", "metcell", nbins, metMin, metMax);
	TH1F *metmhtHist        = new TH1F("metmht", "metmht", nbins, metMin, metMax);
	TH1F *mettopoclHist     = new TH1F("mettopocl", "mettopocl", nbins, metMin, metMax);
	TH1F *mettopoclpsHist   = new TH1F("mettopoclps", "mettopoclps", nbins, metMin, metMax);
	TH1F *mettopoclpucHist  = new TH1F("mettopoclpuc", "mettopoclpuc", nbins, metMin, metMax);
	TH1F *indeterminateHist = new TH1F(all, all, nbins, metMin, metMax);
	TString xlabel = "MET [GeV]";
	TString yaxis = "Events";
	tree->SetBranchAddress("metl1", &metl1);
	tree->SetBranchAddress("metcell", &metcell);
	tree->SetBranchAddress("metmht", &metmht);
	tree->SetBranchAddress("mettopocl", &mettopocl);
	tree->SetBranchAddress("mettopoclps", &mettopoclps);
	tree->SetBranchAddress("mettopoclpuc", &mettopoclpuc);
	tree->SetBranchAddress("metoffrecal", &metoffrecal);
	tree->SetBranchAddress("passrndm", &passrndm);
	tree->SetBranchAddress(all,&indeterminate);
	TH1F *metl1target         = new TH1F("cumu1", "cumu", nbins, metMin, metMax);;
	TH1F *metcelltarget       = new TH1F("cumu2", "cumu", nbins, metMin, metMax);
	TH1F *metmhttarget        = new TH1F("cumu3", "cumu", nbins, metMin, metMax);
	TH1F *mettopocltarget     = new TH1F("cumu4", "cumu", nbins, metMin, metMax);
	TH1F *mettopoclpstarget   = new TH1F("cumu5", "cumu", nbins, metMin, metMax);
	TH1F *mettopoclpuctarget  = new TH1F("cumu6", "cumu", nbins, metMin, metMax);
	TH1F *indeterminatetarget = new TH1F("cumu7", "cumu", nbins, metMin, metMax);
	std::cout << "Determining threshold to keep " << frac << " events in zerobias data after passing rndm" << std::endl;
	std::cout << "Number of entries in the tree: " << nentries << std::endl;

	if (all == "y")
	{
		std::cout << "Determining thresholds for all algorithms..." << std::endl;
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
		

		for (Int_t t = nbins; t >= 0; t--)
		{
			Float_t summ2 = 0;

			for (Int_t i = t; i <= nbins; i++)
			{
				summ2 += metcellHist->GetBinContent(i);
			}
			metcelltarget->SetBinContent(t, summ2);
		}
		for (Int_t t = nbins; t >= 0; t--)
		{
			if ((abs(metcelltarget->GetBinContent(t) - (numKeep) > 0) != (abs(metcelltarget->GetBinContent(t + 1) - (numKeep)) > 0)))
			{
				metcellthresh = metcelltarget->GetBinCenter(t);
			}
		}
		for (Int_t t = nbins; t >= 0; t--)
		{
			Float_t summ3 = 0;

			for (Int_t i = t; i <= nbins; i++)
			{
				summ3 += metmhtHist->GetBinContent(i);
			}
			metmhttarget->SetBinContent(t, summ3);
		}
		for (Int_t t = nbins; t >= 0; t--)
		{
			if ((abs(metmhttarget->GetBinContent(t) - (numKeep) > 0) != (abs(metmhttarget->GetBinContent(t + 1) - (numKeep)) > 0)))
			{
				metmhtthresh = metmhttarget->GetBinCenter(t);
			}
		}
		for (Int_t t = nbins; t >= 0; t--)
		{
			Float_t summ4 = 0;

			for (Int_t i = t; i <= nbins; i++)
			{
				summ4 += mettopoclHist->GetBinContent(i);
			}
			mettopocltarget->SetBinContent(t, summ4);
		}
		for (Int_t t = nbins; t >= 0; t--)
		{
			if ((abs(mettopocltarget->GetBinContent(t) - (numKeep) > 0) != (abs(mettopocltarget->GetBinContent(t + 1) - (numKeep)) > 0)))
			{
				mettopoclthresh = mettopocltarget->GetBinCenter(t);
			}
		}
		for (Int_t t = nbins; t >= 0; t--)
		{
			Float_t summ5 = 0;

			for (Int_t i = t; i <= nbins; i++)
			{
				summ5 += mettopoclpsHist->GetBinContent(i);
			}
			mettopoclpstarget->SetBinContent(t, summ5);
		}
		for (Int_t t = nbins; t >= 0; t--)
		{
			if ((abs(mettopoclpstarget->GetBinContent(t) - (numKeep) > 0) != (abs(mettopoclpstarget->GetBinContent(t + 1) - (numKeep)) > 0)))
			{
				mettopoclpsthresh = mettopoclpstarget->GetBinCenter(t);
			}
		}
		for (Int_t t = nbins; t >= 0; t--)
		{
			Float_t summ6 = 0;

			for (Int_t i = t; i <= nbins; i++)
			{
				summ6 += mettopoclpucHist->GetBinContent(i);
			}
			mettopoclpuctarget->SetBinContent(t, summ6);
		}
		for (Int_t t = nbins; t >= 0; t--)
		{
			if ((abs(mettopoclpuctarget->GetBinContent(t) - (numKeep) > 0) != (abs(mettopoclpuctarget->GetBinContent(t + 1) - (numKeep)) > 0)))
			{
				mettopoclpucthresh = mettopoclpuctarget->GetBinCenter(t);
			}
		}
		std::cout << "Threshold for metl1: " << metl1thresh << std::endl;
		std::cout << "Threshold for metcell: " << metcellthresh << std::endl;
		std::cout << "Threshold for metmht: " << metmhtthresh << std::endl;
		std::cout << "Threshold for mettopocl: " << mettopoclthresh << std::endl;
		std::cout << "Threshold for mettopoclps: " << mettopoclpsthresh << std::endl;
		std::cout << "Threshold for mettopoclpuc: " << mettopoclpucthresh << std::endl;
	}

	if (all != "y") //only compute thresh for one alg
	{
		std::cout << "Determining threshold for " << all << "..." << std::endl;
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
		std::cout << "Threshold for " << all << ": " << indeterminatethresh << std::endl;
	}

std::cout << "num events: " << frac * numRndm << std::endl;
myFile.Close();
return(indeterminatethresh);
}

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
