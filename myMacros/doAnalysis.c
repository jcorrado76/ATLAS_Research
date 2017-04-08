int doAnalysis(TString& alg) 
{
	/* This macro will determine the threshold for zerobias events to keep 10^(-4) events. Then it will apply
	that cut to muon new analysis data. Then it will calculated the efficiency of an algorithm using this cut,
	while filling tefficiency with offrecalnomu data. It will plot tefficiencies, histograms, histogram with cut, scatter and send 
	the graphs to desktop*/
	
	TString fileName = "../myData/ExpressMuons2016newanalysis.11runs.root";
	TFile * 2016Data = TFile::Open(fileName, "READ");

	Int_t nbins = 60;
	Double_t metMin = 0.0;
	Double_t metMax = 500.0;
	TString xlabel = "MET [GeV]";
	TString ylabel = "Events";

	TString teff_name = "TEfficiency for " + alg + " versus METNOMU";
	TString teff_title = teff_name + "; METNOMU; Ratio of Passed to Offline MET";
	TString algParam = alg + " HIST; MET [GeV] ; Events" ;

	//SET BRANCH ADDRESSES +==============================================================================
	Float_t algMet, offrecal_met, offrecal_mex, offrecal_mey, offrecalmuon_mex, offrecalmuon_mey;
	Int_t passmuonFlag, cleanCutsFlag, recalBrokeFlag;
	tree->SetBranchAddress("passmu24med", &passmuonFlag); // get first pass moun flag 
	tree->SetBranchAddress("passcleancuts", &cleanCutsFlag); // get cleancuts flag
	tree->SetBranchAddress("recalbroke", &recalBrokeFlag); // get recalbroke flag
	tree->SetBranchAddress("metoffrecal", &offrecal_met);
	tree->SetBranchAddress("mexoffrecal", &offrecal_mex);
	tree->SetBranchAddress("meyoffrecal", &offrecal_mey);
	tree->SetBranchAddress("mexoffrecalmuon", &offrecalmuon_mex);
	tree->SetBranchAddress("meyoffrecalmuon", &offrecalmuon_mey);
	tree->SetBranchAddress(alg, &algMet); // get first alg met 



	//INITIALIZE ALL HISTOGRAMS+==============================================================================
	TH1F *cut = new TH1F(alg, algParam, nbins, metMin, metMax);
	TH1F *intHist = new TH1F("Integration Hist", algParam, nbins, metMin, metMax);
	TH1F *rightCumuSum = new TH1F("cumu", "cumu", nbins, metMin, metMax);
	TEfficiency *teff = new TEfficiency(alg + " Tefficiency", alg + " TEfficiency", nbins, metMin, metMax);
	TH2F *scatter = new TH2F(alg+" Scatter Plot", alg+" Scatter Plot", nbins, metMin, metMax, nbins, metMin, metMax);

	int nentries = tree->GetEntries();

	// DETERMINE THRESH +====================================================
	//generate the cumulative right tail sum hist
	Float_t  thresh;
	Float_t condition = (1.e-4);

	/* this nentries is the total amount of entries. do I use this value, or do I have to use the number of entries that pass muon???
	If I have to use the amount of entries that passed muon, I'll have to run the big loop twice; once to determine thresh, and then again
	to make cut and tefficiency using the determined thresh as the cutvalue*/

	//Determine the number of entries that pass muon flag 
	std::cout << "Calculating amount of entries that pass muon flag" << std::endl;

	for (Int_t i = 0; i < nentries; i++)
	{
		tree->GetEntry(i);
		if (passmuonFlag > 0.1)
		{
			intHist->Fill(algMet);
		}
	}

	std::cout << "The amount of entries in the tree that pass the muon flag: " << intHist->GetEntries() << std::endl;

	Float_t keep = condition * intHist->GetEntries();

	std::cout << "Keeping 10e-4 entries of those that pass muon flag corresponds to: " << keep << " entries" << std::endl;

	for (Int_t t = nbins; t >= 0.; t--)
	{
		Float_t summ = 0;

		for (int i = t; i <= nbins; i++)
		{
			summ += intHist->GetBinContent(i);
		}
		rightCumuSum->SetBinContent(t, summ);
	}

	std::cout << "Determining threshold to keep 10e-4 events from muon data that passed muon flag" << std::endl;

	for (int t = nbins; t >= 0.; t--)
	{
		if ((abs(rightCumuSum->GetBinContent(t) - (keep) > 0.) != (abs(rightCumuSum->GetBinContent(t + 1.) - (keep)) > 0.)))
		{
			thresh = rightCumuSum->GetBinCenter(t);
		}
	}
	//+====================================================================================

	std::cout << "Threshold to keep 10e-4 events " << thresh << std::endl;

	TString cutAlgHistoParam = (alg + Form(" > %.2f", thresh) + " HIST; " + xlabel + ";" + ylabel);

	//BIG LOOP +============================================================
	for (Int_t k = 0; k < nentries; k++)
	{
		tree->GetEntry(k);
		if (passmuonFlag > 0.1 && cleanCutsFlag > 0.1 && recalBrokeFlag < 0.1)
		{
			if (algMet > thresh)
			{
				cut->Fill(algMet); //fill cut hist;
			}
			Float_t metnomu = sqrt(((offrecal_mex - offrecalmuon_mex) * (offrecal_mex - offrecalmuon_mex)) +
				((offrecal_mey - offrecalmuon_mey)*(offrecal_mey - offrecalmuon_mey))); //compute metnomu
			teff->Fill((algMet > thresh), metnomu); // fill tefficiency
			scatter->Fill(algMet, metnomu); //fill scatter plot
		}
	}
	//+============================================================================

	TCanvas* plots = new TCanvas();
	plots->Divide(3);

	plots->cd(1);
	teff->Draw();

	plots->cd(2);
	scatter->Draw();

	plots->cd(3);
	cut->Draw();
	
}
