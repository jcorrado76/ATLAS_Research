int plotACut(TString& alg, double bound, TString& data = "zerobias"){
	//ROOT FileName
	if (data == "zerobias")
	{
		TString fileName = "../myData/ZeroBias2016.13Runs.root";
	}
	else if (data == "muon")
	{
		TString fileName = "../myData/ExpressMuons2016.12runs.root";
	}
	

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
	int passrndmVal,passmuon;

	//Get addresses of variables
	tree->SetBranchAddress(passed_hist_name, &passed_hist_met);
	tree->SetBranchAddress(reference_hist_name, &reference_hist_met);
	tree->SetBranchAddress("passrndm", &passrndmVal);
	tree->SetBranchAddress("passmu24med", &passmuon);
	//Initial TH1F object
	TH1F *cut = new TH1F(passed_hist_name, passed_hist_full_param1, nbins, metMin, metMax);

	//Initialize TEfficiency Object
	TEfficiency *teff = new TEfficiency(teff_name, teff_title, nbins, metMin, metMax);

	int nentries = tree->GetEntries();

	//fill the cut hist and teff hist 
	if (data == "zerobias")
	{
		std::cout << "filling histogram using zerobias data" << std::endl;
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
				teff->Fill((passed_hist_met > cutValue), reference_hist_met);
			}
		}
	}
	if (data == "muon")
	{
		std::cout << "filling histogram using muon data" << std::endl;
		for (Long64_t j = 0; j < nentries; j++)
		{
			//get the first entry; after adding, get next entry
			tree->GetEntry(j);
			if (passmuon == 1)
			{
				//If the passed_hist_met is above a certain value, add the reference_hist_met from the corresponding entry 
				if (passed_hist_met > cutValue)
				{
					cut->Fill(passed_hist_met);
				}
				teff->Fill((passed_hist_met > cutValue), reference_hist_met);
			}
		}
	}

	TCanvas *c = new TCanvas;
	c->Divide(1, 2);
	c->cd(1);
	cut->Draw();
	c->cd(2);
	teff->Draw();
	TString cutVal = Form("%f", cutValue);
	if (data == "zerobias")
	{	

		std::cout << "Number of entries from zerobias data kept using a " + cutVal +  "GeV cut and passrndm flag: " << cut->GetEntries() << std::endl;
	}
	if (data == "muon")
	{
		std::cout << "Number of entries from muon data kept using a " + cutVal + "GeV cut and passmu24med flag: " << cut->GetEntries() << std::endl;
	}
	
	return 0;
}
