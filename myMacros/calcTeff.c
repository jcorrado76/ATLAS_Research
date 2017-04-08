int calcTeff(TString& algString, Float_t cutValue)
{
	TString fileName = "../myData/ExpressMuons2016newanalysis.11runs.root";
	TFile * 2016Data = TFile::Open(fileName, "READ");

	int nbins = 60;
	Double_t metMin = 0.0;
	Double_t metMax = 200.0;
	TString metoffrecal = "metoffrecal";
	TString alg = algString;
	TString teff_name, teff_title;
	TString xaxis = "MET [GeV]";
	TString yaxis = "Events";
	teff_name = "TEfficiency for " + alg + " versus METNOMU";
	teff_title = teff_name + "; METNOMU; Ratio of Passed to Offline MET";
	TString passed_hist_full_param1 = (alg + Form(" > %.2f", cutValue) + " HIST; " + xaxis + ";" + yaxis);
	//===============================================================================================================================
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
	TEfficiency *teff = new TEfficiency(teff_name, teff_title, nbins, metMin, metMax); // initialize tefficiency object 
	std::cout << "Calculating Efficiency" << std::endl; // ghost print
	int nentries = tree->GetEntries(); //get numb entries
	for (Long64_t j = 0; j < nentries; j++)
	{
		tree->GetEntry(j); //get first entry of tree
		if ( passmuonFlag > 0.1 && cleanCutsFlag > 0.1 && recalBrokeFlag < 0.1 )
		{
			//compute metnomu
			Float_t metnomu = sqrt( ( (offrecal_mex - offrecalmuon_mex) * (offrecal_mex - offrecalmuon_mex) ) + 
			((offrecal_mey - offrecalmuon_mey)*(offrecal_mey - offrecalmuon_mey)));
			teff->Fill( ( algMet > cutValue ) , metnomu );
		}
	}
	TCanvas* TEfficiency = new TCanvas("TEfficiency","TEfficiency");
	teff->Draw();
	return(1);
}