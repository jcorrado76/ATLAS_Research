{
	//ROOT FileName
	TString fileName = "../myData/ZeroBias2016.13Runs.root";

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

	TString teff_name, teff_title;

	//cut value; GeV
	Float_t lwrbnd1 = 50.;

	//Reference Hist Labels
	TString reference_hist_full_param = (reference_hist_title + " HIST;" + xaxis + ";" + yaxis);

	//Calculate Full Hist Params
	TString passed_hist_full_param1 = (passed_hist_title + Form(" > %.2f", lwrbnd1) + " HIST; " + xaxis + ";" + yaxis);

	//Open ROOT file 
	TFile * 2016Data = TFile::Open(fileName, "READ");


	//variables take on values of alg
	Float_t passed_hist_met, reference_hist_met;

	//Get addresses of variables
	tree->SetBranchAddress(passed_hist_name, &passed_hist_met);
	tree->SetBranchAddress(reference_hist_name, &reference_hist_met);

	//Initial TH1F object
	TH1F *cut = new TH1F(passed_hist_name, passed_hist_full_param1, nbins, metMin, metMax);

	//Initialize TEfficiency Object
	TEfficiency *teff = new TEfficiency(teff_name, teff_title, nbins, metMin, metMax);

	//Fill hist and effiency with entries
	bool pass = false;
	//# of entries
	int nentries = tree->GetEntries();
	for (Long64_t i = 0; i < nentries; i++)
	{
		//get the first entry; after adding, get next entry
		tree->GetEntry(i);
		//If the passed_hist_met is above a certain value, add the reference_hist_met from the corresponding entry 
		if (passed_hist_met > lwrbnd1)
		{
			pass = true;
			cut->Fill(passed_hist_met);
			teff->Fill(pass, reference_hist_met);
		}
	}
	cut->Draw();
	//teff->Draw();
}
