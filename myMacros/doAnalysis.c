int plotACut(TString& alg, double cutValue, TString& signalFile) {
	//ROOT FileName
	TString fileName = "../myData/" + signalFile;

	//Passed hist parameters
	TString passed_hist_name = alg;
	TString passed_hist_title = alg;

	//Reference hist parameters 
	TString reference_hist_name = "metoffrecal";
	TString reference_hist_title = "METOFFRECAL";

	//Histogram parameters
	int nbins = 250;
	Double_t metMin = 0.0;
	Double_t metMax = 200.0;

	//Histogram Axis labels 
	TString xaxis = "MET [GeV]";
	TString yaxis = "Events";

	//Reference Hist Labels
	TString reference_hist_full_param = (reference_hist_title + " HIST;" + xaxis + ";" + yaxis);

	//Calculate Full Hist Params
	TString passed_hist_full_param1 = (passed_hist_title + Form(" > %.2f", cutValue) + " HIST; " + xaxis + ";" + yaxis);

	//Open ROOT file 
	TFile * 2016Data = TFile::Open(fileName, "READ");


	//variables take on values of alg
	Float_t passed_hist_met, reference_hist_met;
	int passrndmVal;

	//Get addresses of variables
	tree->SetBranchAddress(passed_hist_name, &passed_hist_met);
	tree->SetBranchAddress(reference_hist_name, &reference_hist_met);
	tree->SetBranchAddress("passrndm", &passrndmVal);

	//Initial TH1F object
	TH1F *cut = new TH1F(passed_hist_name, passed_hist_full_param1, nbins, metMin, metMax);

	int nentries = tree->GetEntries();

	std::cout << "Filling histogram" << std::endl;
	//fill the cut hist and teff hist 
	for (Long64_t j = 0; j < nentries; j++)
	{
		//get the first entry; after adding, get next entry
		tree->GetEntry(j);
		if (passrndmVal == 1)
		{
			//If the passed_hist_met is above a certain value, add the reference_hist_met from the corresponding entry 
			if (passed_hist_met > cutValue)
			{
				cut->Fill(passed_hist_met);
			}
		}
	}

	std::cout << "Number of muon events kept after cutting on passrndm and the zerobias threhold: " << cut->GetEntries() << std::endl;
	cut->Draw();
	return 0;
}
Double_t determineThresh(TString& alg) {
	//ROOT data FileName
	TString fileName = "../myData/ZeroBias2016.13Runs.root";
	//algorithm of interest name
	TString passed_hist_name = alg;
	TString passed_hist_title = alg;
	//Reference hist parameters 
	TString reference_hist_name = "metoffrecal";
	TString reference_hist_title = "METOFFRECAL";

	//Histogram parameters
	int nbins = 250;
	Double_t metMin = 0.0;
	Double_t metMax = 200.0;

	//Histogram Axis labels 
	TString xaxis = "MET [GeV]";
	TString yaxis = "Events";

	//Reference Hist Labels
	TString reference_hist_full_param = (reference_hist_title + " HIST;" + xaxis + ";" + yaxis);

	//Calculate Full Hist Params
	TString passed_hist_full_param1 = (passed_hist_title + " HIST; " + xaxis + ";" + yaxis);


	//Open ROOT file 
	TFile * 2016Data = TFile::Open(fileName, "READ");


	//variables take on values of alg
	Float_t passed_hist_met, reference_hist_met;

	Int_t passrndm;

	//Get addresses of variables
	tree->SetBranchAddress(passed_hist_name, &passed_hist_met);
	tree->SetBranchAddress(reference_hist_name, &reference_hist_met);
	tree->SetBranchAddress("passrndm", &passrndm);


	//Initial TH1F object
	TH1F *cut = new TH1F(passed_hist_name, passed_hist_full_param1, nbins, metMin, metMax);
	TH1F *target = new TH1F("cumu", "cumu", nbins, metMin, metMax);

	//# of entries
	int nentries = tree->GetEntries();

	//fill hist with passrndm events 
	for (Long64_t k = 0; k < nentries; k++)
	{
		//get the first entry; after adding, get next entry
		tree->GetEntry(k);
		//maintain passrndm is true 
		if (passrndm == 1)
		{
			cut->Fill(passed_hist_met);
		}
	}

	//number of entries after applying passrndm
	Int_t passrndmEntries = cut->GetEntries();
	Double_t  thresh;


	Float_t condition = (1e-4);
	Float_t keep = condition * passrndmEntries;

	//generate the cumulative right tail sum hist
	for (int t = nbins; t >= 0; t--)
	{
		Float_t summ = 0;

		for (int i = t; i <= nbins; i++)
		{
			summ += cut->GetBinContent(i);
		}
		target->SetBinContent(t, summ);
	}

	//find the thresh value to keep 
	for (int t = nbins; t >= 0; t--)
	{
		//std::cout << "Number of entries in bin" << t << " " << target->GetBinContent(t) << std::endl;
		if ((abs(target->GetBinContent(t) - (keep) > 0) != (abs(target->GetBinContent(t + 1) - (keep)) > 0)))
		{
			thresh = target->GetBinCenter(t);
		}
	}
	std::cout << "10^(-4) Entries after passrndm: " << keep << std::endl;
	std::cout << "The threshold for " << passed_hist_name << " to keep " << keep << " events is: " << thresh << std::endl;
	return thresh;
}
plotEfficiency(TString& alg, Double_t cut, TString& signalFile) 
{
	/*
	Joseph Corrado plotEffiency.c
	Plots effiencies of various ATLAS algorithms versus the MET OFFLINE RECAL algorithm
	*/


	//ROOT FileName
	TString fileName = "../myData/" + signalFile;

	//Open ROOT file 
	TFile * 2016Data = TFile::Open(fileName, "READ");

	//Passed hist parameters
	TString passed_hist_name = alg;
	TString passed_hist_title = alg;

	//Reference hist parameters 
	TString reference_hist_name = "metoffrecal";
	TString reference_hist_title = "METOFFRECAL";

	//Histogram parameters
	int nbins = 50;
	Double_t metMin = 0.0;
	Double_t metMax = 100.0;

	//Scatter Plot Parameters
	int nscatterBinsx = nbins;
	int nscatterBinsy = nbins;
	int scatterxmin = -5.0;
	int scatterxmax = 160.0;
	int scatterymin = -5.0;
	int scatterymax = 100.0;

	//Histogram Axis labels 
	TString xaxis = "MET [GeV]";
	TString yaxis = "Events";

	//========================================================================================================================
	//make these plots for all the algorithms in the array 



	//Calculate Full Hist Params
	TString passed_hist_full_param = (passed_hist_title + " HIST; " + xaxis + ";" + yaxis);
	TString reference_hist_full_param = (reference_hist_title + " HIST;" + xaxis + ";" + yaxis);

	//TEfficiency Labels
	TString teff_title;
	TString teff_name = passed_hist_name + " vs " + reference_hist_name;
	teff_title = passed_hist_title + " / " + reference_hist_title + " Efficiency" + ";" + xaxis + ";" + " Efficiency";

	//containers for 1st entry of met 
	Float_t passed_hist_met, reference_hist_met;


	//Get addresses of variables
	tree->SetBranchAddress(passed_hist_name, &passed_hist_met);
	tree->SetBranchAddress(reference_hist_name, &reference_hist_met);


	//Initialize TH1F objects
	TH1F *reference_hist = new TH1F(reference_hist_name, reference_hist_full_param, nbins, metMin, metMax);
	TH1F *passed_hist = new TH1F(passed_hist_name, passed_hist_full_param, nbins, metMin, metMax);

	//Initialize TEfficiency Object 
	TEfficiency *teff = new TEfficiency(teff_name, teff_title, nbins, metMin, metMax);

	int nentries = tree->GetEntries();
	for (Int_t i = 0; i < nentries; i++)
	{
		tree->GetEntry(i); 
		teff->Fill(passed_hist > cut, reference_hist_met);
	}
	TCanvas *plotCanvas = new TCanvas();
	teff->Draw();
	return(0);
}

int doAnalysis(TString& alg){
		//signal file to use
		TString signalFile = "ZeroBias2016.13Runs.root";
		//determine threshold from zero bias 
		Double_t zeroBiasThresh = determineThresh(alg);
		//plot a cut using threshold determined 
		plotACut(alg, zeroBiasThresh, signalFile);
		plotEfficiency(alg, zeroBiasThresh, signalFile);
	return(0);
}
