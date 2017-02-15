{
	/*
	Joseph Corrado plotEffiency.c
	Plots effiencies of various ATLAS algorithms versus the MET OFFLINE RECAL algorithm
	Plot cuts only bounded below
	*/

	//# ALGS
	int N = 7;
	//ALGS
	TString METalgArray[N] = { "metl1","metcell","metmht","mettopocl","mettopoclps","mettopoclpuc","passrndm" };
	TString SETalgArray[N] = {};

	//arbitrary cut values
	Float_t cutGuess = 80;

	//ROOT FileName
	TString fileName = "ZeroBias2016.13Runs.root";

	//Passed hist parameters
	TString passed_hist_name = "mettopocl";
	TString passed_hist_title = "METTOPOCL";

	//Reference hist parameters 
	TString reference_hist_name = "metoffrecal";
	TString reference_hist_title = "METOFFRECAL";

	//Histogram parameters
	int nbins = 250;
	Double_t metMin = 0.0;
	Double_t metMax = 100.0;

	//Histogram Axis labels 
	TString xaxis = "MET [GeV]";
	TString yaxis = "Events";

	//Reference Hist Labels
	TString reference_hist_full_param = (reference_hist_title + " HIST;" + xaxis + ";" + yaxis);

	//Calculate Full Hist Params
	TString passed_hist_full_param1 = (passed_hist_title + Form(" > %.2f", cutGuess) + " HIST; " + xaxis + ";" + yaxis);



	//========================================================================================================================
	//TEfficiency Labels
	TString teff_name, teff_title1, teff_title2, teff_title3;
	teff_name = passed_hist_name + " vs " + reference_hist_name;
	teff_title1 = passed_hist_title + " / " + reference_hist_title + " , " + Form(" > %.2f", cutGuess) + " Efficiency" + ";" + xaxis + ";" + " Efficiency";

	//Open ROOT file 
	TFile * 2016Data = TFile::Open(fileName, "READ");

	//containers for 1st entry of met 
	Float_t passed_hist_met, reference_hist_met;

	//Get addresses of variables
	tree->SetBranchAddress(reference_hist_name, &reference_hist_met);

	//Initial TH1F objects
	TH1F *cut = new TH1F(passed_hist_name, passed_hist_full_param1, nbins, metMin, metMax);


	//Initialize TEfficiency Objects 
	TEfficiency *teff = new TEfficiency(teff_name, teff_title1, nbins, metMin, metMax);

	//Fill hist and effiency with entries
	Int_t entries = 100;
	bool pass = false;
	//# of entries
	int nentries = tree->GetEntries();

	//for each algorithm
	for (Int_t i = 0; i < N; i++)
	{
		passed_hist_name = METalgArray[i];
		tree->SetBranchAddress(passed_hist_name, &passed_hist_met);
		//input all entries first time
		for (Int_t j = 0; j < nentries; j++)
		{
			tree->GetEntry(j);
			//If the passed_hist_met is above a certain value, add the reference_hist_met from the corresponding entry 
			if (passed_hist_met > cutGuess)
			{
				pass = true;
				cut->Fill(passed_hist_met);
				//teff->Fill(pass, reference_hist_met);
			}
		}
		//if cut size is too large, create new hist and try again 
		while (cut->GetSize() > (nentries * (0.0001)))
		{
			TH1F *cut = new TH1F(passed_hist_name + "hist", passed_hist_full_param1, nbins, metMin, metMax);
			for (j = 0; j < nentries; j++)
			{
				tree->GetEntry(j);
				//If the passed_hist_met is above a certain value, add the reference_hist_met from the corresponding entry 
				if (passed_hist_met > cutGuess)
				{
					pass = true;
					cut->Fill(passed_hist_met);
					//teff->Fill(pass, reference_hist_met);
				}
			}
			cutGuess++;
		}
		std::cout << passed_hist_name << "Cut to keep O(100) events: " << cutGuess << std::endl;
	}

}