TEfficiency calcTeff(TString& alg, Float_t cutValue)
{
	TString fileName = "../myData/ExpressMuons2016.12runs.root";
	int nbins = 60;
	Double_t metMin = 0.0;
	Double_t metMax = 200.0;
	TString reference_hist_name = "metoffrecal";
	TString reference_hist_title = "METOFFRECAL";
	TString passed_hist_name = alg;
	TString passed_hist_title = alg;
	TString teff_name, teff_title;
	TString xaxis = "MET [GeV]";
	TString yaxis = "Events";
	teff_name = "TEfficiency for " + alg + " versus Offline MET";
	teff_title = teff_name + "; Offline MET; Ratio of Passed to Offline MET";
	TString reference_hist_full_param = (reference_hist_title + " HIST;" + xaxis + ";" + yaxis);
	TString passed_hist_full_param1 = (passed_hist_title + Form(" > %.2f", cutValue) + " HIST; " + xaxis + ";" + yaxis);
	TFile * 2016Data = TFile::Open(fileName, "READ");
	Float_t passed_hist_met, reference_hist_met;
	int passrndmVal, passmuon;
	tree->SetBranchAddress(passed_hist_name, &passed_hist_met);
	tree->SetBranchAddress(reference_hist_name, &reference_hist_met);
	tree->SetBranchAddress("passrndm", &passrndmVal);
	tree->SetBranchAddress("passmu24med", &passmuon);
	int nentries = tree->GetEntries();
	//Initial TH1F object
	TH1F *cut = new TH1F(passed_hist_name, passed_hist_full_param1, nbins, metMin, metMax);

	//Initialize TEfficiency Object
	TEfficiency *teff = new TEfficiency(teff_name, teff_title, nbins, metMin, metMax);



	std::cout << "filling histogram using muon data" << std::endl;
	for (Long64_t j = 0; j < nentries; j++)
	{
		//get the first entry; after adding, get next entry
		tree->GetEntry(j);
		if (passmuon == 1)
		{
			//If the passed_hist_met is above a certain value, add the reference_hist_met from the corresponding entry 
			teff->Fill((passed_hist_met > cutValue), reference_hist_met);
		}
	}
	teff->Draw();
	return teff;
}