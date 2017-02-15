int determineThresh(TString& alg, double initialGuess = 50.) {
	//ROOT FileName
	TString fileName = "../myData/ZeroBias2016.13Runs.root";

	TString nameArray[6] = { "metl1","metcell","metmht","mettopocl","mettopoclps","mettopoclpuc" };


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

	TString teff_name, teff_title;

	//Reference Hist Labels
	TString reference_hist_full_param = (reference_hist_title + " HIST;" + xaxis + ";" + yaxis);

	//Calculate Full Hist Params
	TString passed_hist_full_param1 = (passed_hist_title + Form(" > %.2f", initialGuess) + " HIST; " + xaxis + ";" + yaxis);
	

	//Open ROOT file 
	TFile * 2016Data = TFile::Open(fileName, "READ");


	//variables take on values of alg
	Float_t passed_hist_met, reference_hist_met;

	//Get addresses of variables
	tree->SetBranchAddress(passed_hist_name, &passed_hist_met);
	tree->SetBranchAddress(reference_hist_name, &reference_hist_met);

	//Initial TH1F object
	TH1F *cut = new TH1F(passed_hist_name, passed_hist_full_param1, nbins, metMin, metMax);



	//# of entries
	int nentries = tree->GetEntries();

	double condition = (10 * *(-4))*nentries;

	for (Long64_t j = 0; j < nentries; j++)
	{
		//get the first entry; after adding, get next entry
		tree->GetEntry(j);
		//If the passed_hist_met is above a certain value, add the reference_hist_met from the corresponding entry 
		if (passed_hist_met > initialGuess)
		{
			cut->Fill(passed_hist_met);
		}
	}

	int eventsKept  = cut->GetEntries();

	while (eventsKept < condition)
	{
		initialGuess = initialGuess +  2.0;
		for (Long64_t j = 0; j < nentries; j++)
		{
			//get the first entry; after adding, get next entry
			tree->GetEntry(j);
			//If the passed_hist_met is above a certain value, add the reference_hist_met from the corresponding entry 
			if (passed_hist_met > initialGuess)
			{
				cut->Fill(passed_hist_met);
			}
		}
		eventsKept = cut->GetEntries();
	}

	std::cout << "Cut to keep 10^(-4) events:  " << initialGuess << std::endl;

	

	cut->Draw();

	return 0;
}
