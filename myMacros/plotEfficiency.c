int plotEfficiency(TString& alg, Double_t cut,TString& signalFile = "ExpressMuons2016newanalysis.11runs.root"){

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
		Float_t passed_hist_met, metoffrecal;


		//Get addresses of variables
		tree->SetBranchAddress(passed_hist_name, &passed_hist_met);
		tree->SetBranchAddress("metoffrecal", &metoffrecal);


		//Initialize TH1F objects
		TH1F *reference_hist = new TH1F(reference_hist_name, reference_hist_full_param, nbins, metMin, metMax);
		TH1F *passed_hist = new TH1F(passed_hist_name, passed_hist_full_param, nbins, metMin, metMax);

		//Initialize TEfficiency Object 
		TEfficiency *teff = new TEfficiency(teff_name, teff_title, nbins, metMin, metMax);

		//# of entries
		int nentries = tree->GetEntries();
		for (Int_t i = 0; i < nentries; i++)
		{
			tree->GetEntry(i);
			//Fill TEfficiency 
			teff->Fill(passed_hist > cut, metoffrecal);
		}

		//Divide canvas into pads
		TCanvas *plotCanvas = new TCanvas();
		teff->Draw();
		return(0);
	}

