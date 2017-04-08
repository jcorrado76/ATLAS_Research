Double_t determineThresh() 
{
	/* determine zerobias thresholds for all algorithms*/
	TString fileName = "../myData/ZeroBias2016new.13Runs.root";
	TFile * 2016Data = TFile::Open(fileName, "READ");
	
	int nbins = 60;
	Double_t metMin = 0.0;
	Double_t metMax = 500.0;

	TH1F *metl1Hist = new TH1F("metl1", "metl1", nbins, metMin, metMax);
	TH1F *metcellHist = new TH1F("metcell", "metcell", nbins, metMin, metMax);
	TH1F *metmhtHist = new TH1F("metmht", "metmht", nbins, metMin, metMax);
	TH1F *mettopoclHist = new TH1F("mettopocl", "mettopocl", nbins, metMin, metMax);
	TH1F *mettopoclpsHist = new TH1F("mettopoclps", "mettopoclps", nbins, metMin, metMax);
	TH1F *mettopoclpucHist = new TH1F("mettopoclpuc", "mettopoclpuc", nbins, metMin, metMax);

	TString xlabel = "MET [GeV]";
	TString yaxis = "Events";

	Float_t metl1, metcell , metmht , mettopocl , mettopoclps , mettopoclpuc , metoffrecal;
	Int_t passrndm;

	tree->SetBranchAddress("metl1", &metl1);
	tree->SetBranchAddress("metcell", &metcell);
	tree->SetBranchAddress("metmht", &metmht);
	tree->SetBranchAddress("mettopocl", &mettopocl);
	tree->SetBranchAddress("mettopoclps", &mettopoclps);
	tree->SetBranchAddress("mettopoclpuc", &mettopoclpuc);
	tree->SetBranchAddress("metoffrecal", &metoffrecal);
	tree->SetBranchAddress("passrndm", &passrndm);

	TH1F *metl1target = new TH1F("cumu1", "cumu", nbins, metMin, metMax);
	TH1F *metcelltarget = new TH1F("cumu2", "cumu", nbins, metMin, metMax);
	TH1F *metmhttarget = new TH1F("cumu3", "cumu", nbins, metMin, metMax);
	TH1F *mettopocltarget = new TH1F("cumu4", "cumu", nbins, metMin, metMax);
	TH1F *mettopoclpstarget = new TH1F("cumu5", "cumu", nbins, metMin, metMax);
	TH1F *mettopoclpuctarget = new TH1F("cumu6", "cumu", nbins, metMin, metMax);

	int nentries = tree->GetEntries();
	for (Long64_t k = 0; k < nentries; k++)
	{
		tree->GetEntry(k);
		if (passrndm > 0.1)
		{
			metl1Hist->Fill(metl1);
			metcellHist->Fill(metcell);
			metmhtHist->Fill(metmht);
			mettopoclHist->Fill(mettopocl);
			mettopoclpsHist->Fill(mettopoclps);
			mettopoclpucHist->Fill(mettopoclpuc);
		}
	}

	Int_t metl1entries = metl1Hist->GetEntries();
	Int_t metcellentries = metcellHist->GetEntries();
	Int_t metmhtentries = metmhtHist->GetEntries();
	Int_t mettopoclentries = mettopoclHist->GetEntries();
	Int_t mettopoclpsentries = mettopoclpsHist->GetEntries();
	Int_t mettopoclpucentries = mettopoclpucHist->GetEntries();

	Float_t  metl1thresh , metcellthresh , metmhtthresh , mettopoclthresh , mettopoclpsthresh , mettopoclpucthresh;
	Float_t condition = (1e-4);

	Float_t metl1keep = condition * metl1entries;
	Float_t metcellkeep = condition * metcellentries;
	Float_t metmhtkeep = condition * metmhtentries;
	Float_t mettopoclkeep = condition * mettopoclentries;
	Float_t mettopoclpskeep = condition * mettopoclpsentries;
	Float_t mettopoclpuckeep = condition * mettopoclpucentries;

std::cout << "Determining threshold to keep 10e-4 events in zerobias data" << std::endl;
//generate the cumulative right tail sum hist
for (int t = nbins; t >= 0 ; t--)
{
	Float_t summ1 = 0;

	for (int i = t ; i <= nbins ; i++)
	{
		summ1 += metl1Hist->GetBinContent(i);
	}
	metl1target->SetBinContent(t, summ1 );
}
for (int t = nbins; t >=0 ; t--)
{
	if ((abs(metl1target->GetBinContent(t) - (metl1keep) > 0 )!= (abs(metl1target->GetBinContent(t+1) - (metl1keep)) > 0 )))
	{
		metl1thresh = metl1target->GetBinCenter(t);
	}
}
for (int t = nbins; t >= 0; t--)
{
	Float_t summ2 = 0;

	for (int i = t; i <= nbins; i++)
	{
		summ2 += metcellHist->GetBinContent(i);
	}
	metcelltarget->SetBinContent(t, summ2);
}
for (int t = nbins; t >= 0; t--)
{
	if ((abs(metcelltarget->GetBinContent(t) - (metcellkeep) > 0) != (abs(metcelltarget->GetBinContent(t + 1) - (metcellkeep)) > 0)))
	{
		metcellthresh = metcelltarget->GetBinCenter(t);
	}
}
for (int t = nbins; t >= 0; t--)
{
	Float_t summ3 = 0;

	for (int i = t; i <= nbins; i++)
	{
		summ3 += metmhtHist->GetBinContent(i);
	}
	metmhttarget->SetBinContent(t, summ3);
}
for (int t = nbins; t >= 0; t--)
{
	if ((abs(metmhttarget->GetBinContent(t) - (metmhtkeep) > 0) != (abs(metmhttarget->GetBinContent(t + 1) - (metmhtkeep)) > 0)))
	{
		metmhtthresh = metmhttarget->GetBinCenter(t);
	}
}
for (int t = nbins; t >= 0; t--)
{
	Float_t summ4 = 0;

	for (int i = t; i <= nbins; i++)
	{
		summ4 += mettopoclHist->GetBinContent(i);
	}
	mettopocltarget->SetBinContent(t, summ4);
}
for (int t = nbins; t >= 0; t--)
{
	if ((abs(mettopocltarget->GetBinContent(t) - (mettopoclkeep) > 0) != (abs(mettopocltarget->GetBinContent(t + 1) - (mettopoclkeep)) > 0)))
	{
		mettopoclthresh = mettopocltarget->GetBinCenter(t);
	}
}
for (int t = nbins; t >= 0; t--)
{
	Float_t summ5 = 0;

	for (int i = t; i <= nbins; i++)
	{
		summ5 += mettopoclpsHist->GetBinContent(i);
	}
	mettopoclpstarget->SetBinContent(t, summ5);
}
for (int t = nbins; t >= 0; t--)
{
	if ((abs(mettopoclpstarget->GetBinContent(t) - (mettopoclpskeep) > 0) != (abs(mettopoclpstarget->GetBinContent(t + 1) - (mettopoclpskeep)) > 0)))
	{
		mettopoclpsthresh = mettopoclpstarget->GetBinCenter(t);
	}
}
for (int t = nbins; t >= 0; t--)
{
	Float_t summ6 = 0;

	for (int i = t; i <= nbins; i++)
	{
		summ6 += mettopoclpucHist->GetBinContent(i);
	}
	mettopoclpuctarget->SetBinContent(t, summ6);
}
for (int t = nbins; t >= 0; t--)
{
	if ((abs(mettopoclpuctarget->GetBinContent(t) - (mettopoclpuckeep) > 0) != (abs(mettopoclpuctarget->GetBinContent(t + 1) - (mettopoclpuckeep)) > 0)))
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
