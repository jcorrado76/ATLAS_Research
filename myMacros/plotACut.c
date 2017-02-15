int plotACut(TString& alg, double bound){
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

	//cut value; GeV
	Float_t cutValue = bound;

	//Reference Hist Labels
	TString reference_hist_full_param = (reference_hist_title + " HIST;" + xaxis + ";" + yaxis);

	//Calculate Full Hist Params
	TString passed_hist_full_param1 = (passed_hist_title + Form(" > %.2f", cutValue) + " HIST; " + xaxis + ";" + yaxis);

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
	
	TF1 * myFit = new TF1("myFit", "gaus(0)", 50, 200);


	std::cout << "Number of entries " << nentries << std::endl;

	
	for (Long64_t j = 0; j < nentries; j++)
	{
		//get the first entry; after adding, get next entry
		tree->GetEntry(j);
		//If the passed_hist_met is above a certain value, add the reference_hist_met from the corresponding entry 
		if (passed_hist_met > cutValue)
		{

			cut->Fill(passed_hist_met);
			teff->Fill(true, reference_hist_met);
		}
	}
	//Int_t entriesPassed = cut->GetEntries();
	//Double_t ratioPassed = entriesPassed / nentries;
	//std::cout << "Ratio of events kept: " << ratioPassed << std::endl;
	//Double_t secParam = cut->GetMean();
	//Double_t thirParam = cut->GetRMS();
	//Double_t firstParam = 1 / (sqrt(2 * TMath::Pi()) * thirParam);
	//myFit = cut->Fit("gaus");

	//TCanvas *c = new TCanvas;
	////c->Divide(1, 2)
	////c->cd(1);
	////myFit->Draw();
	////c->cd(2);
	cut->Draw();

	
	
	//teff->Draw();
	return 0;
}
