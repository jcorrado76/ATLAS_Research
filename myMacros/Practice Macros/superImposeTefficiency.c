{
	std::cout << "Displays tefficiency curves for all algorithms on muon data using zero bias threshold" << std::endl;
	TString fileName = "../myData/ExpressMuons2016.12runs.root";
	TFile * 2016Data = TFile::Open(fileName, "READ");
	int nbins = 60;
	Double_t metMin = 0.0;
	Double_t metMax = 400.0;

	TString teff_name1, teff_title1;
	TString teff_name2, teff_title2;
	TString teff_name3, teff_title3;
	TString teff_name4, teff_title4;
	TString teff_name5, teff_title5;
	TString teff_name6, teff_title6;
	TString xaxis = "MET [GeV]";
	TString yaxis = "Events";


	Float_t cutValue1 = 0.0;
	Float_t cutValue2 = 0.0;
	Float_t cutValue3 = 0.0;
	Float_t cutValue4 = 0.0;
	Float_t cutValue5 = 0.0;
	Float_t cutValue6 = 0.0;
	TString alg1, alg2, alg3, alg4, alg5, alg6;
	//this needs to go in the loop and be updated for each tefficiency
	TString alg1 = "metl1";
	TString alg2 = "metcell";
	TString alg3 = "metmht";
	TString alg4 = "mettopocl";
	TString alg5 = "mettopoclps";
	TString alg6 = "mettopoclpuc";
	TString passed_hist_title1 = alg1;
	TString passed_hist_title2 = alg2;
	TString passed_hist_title3 = alg3;
	TString passed_hist_title4 = alg4;
	TString passed_hist_title5 = alg5;
	TString passed_hist_title6 = alg6;
	TString passed_hist_full_param1 = (passed_hist_title1 + Form(" > %.2f", cutValue1) + " HIST; " + xaxis + ";" + yaxis);
	TString passed_hist_full_param2 = (passed_hist_title2 + Form(" > %.2f", cutValue2) + " HIST; " + xaxis + ";" + yaxis);
	TString passed_hist_full_param3 = (passed_hist_title3 + Form(" > %.2f", cutValue3) + " HIST; " + xaxis + ";" + yaxis);
	TString passed_hist_full_param4 = (passed_hist_title4 + Form(" > %.2f", cutValue4) + " HIST; " + xaxis + ";" + yaxis);
	TString passed_hist_full_param5 = (passed_hist_title5 + Form(" > %.2f", cutValue5) + " HIST; " + xaxis + ";" + yaxis);
	TString passed_hist_full_param6 = (passed_hist_title6 + Form(" > %.2f", cutValue6) + " HIST; " + xaxis + ";" + yaxis);
	teff_name1 = "TEfficiency for " + alg1 + " versus Offline MET";
	teff_name2 = "TEfficiency for " + alg2 + " versus Offline MET";
	teff_name3 = "TEfficiency for " + alg3 + " versus Offline MET";
	teff_name4 = "TEfficiency for " + alg4 + " versus Offline MET";
	teff_name5 = "TEfficiency for " + alg5 + " versus Offline MET";
	teff_name6 = "TEfficiency for " + alg6 + " versus Offline MET";
	teff_title1 = teff_name1 + "; Offline MET; Ratio of Passed to Offline MET";
	teff_title2 = teff_name2 + "; Offline MET; Ratio of Passed to Offline MET";
	teff_title3 = teff_name3 + "; Offline MET; Ratio of Passed to Offline MET";
	teff_title4 = teff_name4 + "; Offline MET; Ratio of Passed to Offline MET";
	teff_title5 = teff_name5 + "; Offline MET; Ratio of Passed to Offline MET";
	teff_title6 = teff_name6 + "; Offline MET; Ratio of Passed to Offline MET";

	TEfficiency* teff1 = new TEfficiency(teff_name1, teff_title1, nbins, metMin, metMax);
	TEfficiency* teff2 = new TEfficiency(teff_name2, teff_title2, nbins, metMin, metMax);
	TEfficiency* teff3 = new TEfficiency(teff_name3, teff_title3, nbins, metMin, metMax);
	TEfficiency* teff4 = new TEfficiency(teff_name4, teff_title4, nbins, metMin, metMax);
	TEfficiency* teff5 = new TEfficiency(teff_name5, teff_title5, nbins, metMin, metMax);
	TEfficiency* teff6 = new TEfficiency(teff_name6, teff_title6, nbins, metMin, metMax);


	Float_t passed_hist_met1;
	Float_t passed_hist_met2;
	Float_t passed_hist_met3;
	Float_t passed_hist_met4;
	Float_t passed_hist_met5;
	Float_t passed_hist_met6;
	tree->SetBranchAddress(alg1, &passed_hist_met1);
	tree->SetBranchAddress(alg2, &passed_hist_met2);
	tree->SetBranchAddress(alg3, &passed_hist_met3);
	tree->SetBranchAddress(alg4, &passed_hist_met4);
	tree->SetBranchAddress(alg5, &passed_hist_met5);
	tree->SetBranchAddress(alg6, &passed_hist_met6);


	TString mexoffrecalName = "mexoffrecal";
	TString meyoffrecalName = "meyoffrecal";
	TString mexofflineName = "mexoffrecalmuon";
	TString meyofflineName = "meyoffrecalmuon";

	Float_t mexoffrecal, meyoffrecal, mexofflineMuon, meyofflineMuon;

	tree->SetBranchAddress(mexoffrecalName, &mexoffrecal);
	tree->SetBranchAddress(meyoffrecalName, &meyoffrecal);
	tree->SetBranchAddress(mexofflineName, &mexofflineMuon);
	tree->SetBranchAddress(meyofflineName, &meyofflineMuon);
	//metx off - metx mu



	//need to replace this with the METNoMu
	//need to define all the variables for METNoMu and compute it inside the loop
	TString reference_hist_name = "metoffrecal";
	TString reference_hist_full_param = (reference_hist_name + " HIST;" + xaxis + ";" + yaxis);


	int passrndmVal, passmuon;
	int nentries = tree->GetEntries();
	Float_t offrecal;
	tree->SetBranchAddress("passmu24med", &passmuon);
	tree->SetBranchAddress("passrndm", &passrndmVal);
	tree->SetBranchAddress(reference_hist_name, &offrecal);
	std::cout << "Creating TEfficiencies..." << std::endl;
	for (Long64_t j = 0; j < nentries; j++)
	{
		Float_t metnomux = mexoffrecal - mexofflineMuon;
		Float_t metnomuy = meyoffrecal - meyofflineMuon;
		Float_t referenceVal = sqrt(((metnomux) * (metnomux)) +((metnomuy)*(metnomuy)));
		tree->GetEntry(j);
		if (passmuon == 1)
		{
			teff1->Fill((passed_hist_met1 > cutValue1), referenceVal);
			teff2->Fill((passed_hist_met2 > cutValue2), referenceVal);
			teff3->Fill((passed_hist_met3 > cutValue3), referenceVal);
			teff4->Fill((passed_hist_met4 > cutValue4), referenceVal);
			teff5->Fill((passed_hist_met5 > cutValue5), referenceVal);
			teff6->Fill((passed_hist_met6 > cutValue6), referenceVal);
		}
	}

	teff1->Draw();
	teff2->Draw();
	teff3->Draw();
	teff4->Draw();
	teff5->Draw();
	teff6->Draw();

}
