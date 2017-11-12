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
	Float_t lwrbnd1 = 100.;
	Float_t lwrbnd2 = 120.;
	Float_t lwrbnd3 = 150.;

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
	TString passed_hist_full_param1 = (passed_hist_title + Form(" > %.2f",lwrbnd1) + " HIST; " + xaxis + ";" + yaxis);
	TString passed_hist_full_param2 = (passed_hist_title + Form(" > %.2f",lwrbnd2) + " HIST; " + xaxis + ";" + yaxis);
	TString passed_hist_full_param3 = (passed_hist_title + Form(" > %.2f",lwrbnd3) + " HIST; " + xaxis + ";" + yaxis);



	//========================================================================================================================
	//TEfficiency Labels
	TString teff_name, teff_title1, teff_title2, teff_title3;
	teff_name = passed_hist_name + " vs " + reference_hist_name;
	teff_title1 = passed_hist_title + " / " + reference_hist_title + " , " + Form(" > %.2f", lwrbnd1) + " Efficiency" + ";" + xaxis + ";" + " Efficiency";
	teff_title2 = passed_hist_title + " / " + reference_hist_title + " , " + Form(" > %.2f", lwrbnd2) + " Efficiency" + ";" + xaxis + ";" + " Efficiency";
	teff_title3 = passed_hist_title + " / " + reference_hist_title + " , " + Form(" > %.2f", lwrbnd3) + " Efficiency" + ";" + xaxis + ";" + " Efficiency";


	//Scatter Plot Lavels 
	scatterPlot_title = passed_hist_title + " vs " + reference_hist_title + " Scatter Plot" + ";" + reference_hist_title + ";" + passed_hist_title;
	TString scatterxLabel, scatteryLabel;
	scatterxLabel = reference_hist_title + " [GeV]";
	scatteryLabel = passed_hist_title + " [GeV]";

	//Open ROOT file 
	TFile * 2016Data = TFile::Open(fileName, "READ");
	

	//containers for 1st entry of met 
	Float_t passed_hist_met, reference_hist_met;

	//Get addresses of variables
	tree->SetBranchAddress(passed_hist_name, &passed_hist_met);
	tree->SetBranchAddress(reference_hist_name, &reference_hist_met);

	//Initial TH1F objects
	TH1F *cut1 = new TH1F(passed_hist_name, passed_hist_full_param1, nbins, metMin, metMax);
	TH1F *cut2 = new TH1F(passed_hist_name, passed_hist_full_param2, nbins, metMin, metMax);
	TH1F *cut3 = new TH1F(passed_hist_name, passed_hist_full_param3, nbins, metMin, metMax);

	//Initialize TEfficiency Objects 
	TEfficiency *teff1 = new TEfficiency(teff_name, teff_title1, nbins, metMin, metMax);
	TEfficiency *teff2 = new TEfficiency(teff_name, teff_title2, nbins, metMin, metMax);
	TEfficiency *teff3 = new TEfficiency(teff_name, teff_title3, nbins, metMin, metMax);

	//Fill hist and effiency with entries
	bool pass = false;
	//# of entries
	int nentries = tree->GetEntries();
	for (Long64_t i = 0; i < nentries; i++)
	{
		tree->GetEntry(i);
		//If the passed_hist_met is above a certain value, add the reference_hist_met from the corresponding entry 
		if (passed_hist_met > lwrbnd3)
		{
			pass = true;
			cut3->Fill(passed_hist_met);
			teff3->Fill(pass, reference_hist_met);
		}
		if (passed_hist_met > lwrbnd2)
		{
			pass = true;
			cut2->Fill(passed_hist_met);
			teff2->Fill(pass, reference_hist_met);
		}
		if (passed_hist_met > lwrbnd1)
		{
			pass = true;
			cut1->Fill(passed_hist_met);
			teff1->Fill(pass, reference_hist_met);
		}

		

	}

	//Make new canvas
	TCanvas *plotCanvas = new TCanvas();
	plotCanvas->Divide(2, 3);

	//Plot histograms with different cuts 
	plotCanvas->cd(1);
	cut1->Draw();
	plotCanvas->cd(2);
	teff1->Draw();
	plotCanvas->cd(3);
	cut2->Draw();
	plotCanvas->cd(4);
	teff2->Draw();
	plotCanvas->cd(5);
	cut3->Draw();
	plotCanvas->cd(6);
	teff3->Draw();
	


	/*
	//Drawing n graphs
	TGraph *g[N];
	Double_t x[N] = { 0,1,2,3,4,5,6 };
	Double_t y[N] = { 1,2,3,4,5,6,4 };
	TMultiGraph *mg = new TMultiGraph();
	for (int i = 0; i<N; i++) 
	{
	g[i] = new TGraph(N, x, y);
	y[i] = y[i] + 1;
	mg->Add(g[i]);
	}
	mg->Draw("AL");
	===================================================================================================*/
}

