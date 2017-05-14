int doAnalysis(TString& alg, Float_t thresh)
{
	/*  This macro will apply the cut to muon new analysis data. Then it will calculated the efficiency of an algorithm using this cut,
	while filling tefficiency with offrecalnomu data. It will plot tefficiencies, histograms, histogram with cut, scatter and send
	the graphs to desktop*/

	TString fileName = "../myData/ExpressMuons2016newanalysis.11runs.root";
	TFile * 2016Data = TFile::Open(fileName, "READ");

	Int_t nentries = tree->GetEntries();

	Int_t nbins = 60;
	Double_t metMin = 0.0;
	Double_t metMax = 500.0;
	TString xlabel = "MET [GeV]";
	TString ylabel = "Events";

	TString teff_name = "TEfficiency for " + alg + " versus METNOMU";
	TString teff_title = teff_name + "; METNOMU; Ratio of Passed to METNOMU";
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
	TEfficiency *teff = new TEfficiency(alg + " Tefficiency", alg + " TEfficiency", nbins, metMin, metMax);
	TH2F *scatter = new TH2F(alg+" Scatter Plot", alg+" Scatter Plot", nbins, metMin, metMax, nbins, metMin, metMax);

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
