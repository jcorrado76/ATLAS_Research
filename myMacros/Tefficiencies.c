{
	std::cout << "Displays tefficiency curves for all algorithms on muon data using zero bias threshold" << std::endl;
	//TString fileName = "../myData/ExpressMuons2016newanalysis.11runs.root";
	TString fileName = "../myData/ExpressMuons2016newanalysis.11runs.root";
	TFile * 2016Data = TFile::Open(fileName, "READ");
	int nbins = 60;
	Double_t metMin = 0.0;
	Double_t metMax = 700.0;
	
	TString teff_name1, teff_title1;
	TString teff_name2, teff_title2;
	TString teff_name3, teff_title3;
	TString teff_name4, teff_title4;
	TString teff_name5, teff_title5;
	TString teff_name6, teff_title6;
	TString xaxis = "MET [GeV]";
	TString yaxis = "Events";

	//these are zero bias thresholds 
	Float_t cutValue1 = 45.0;
	Float_t cutValue2 = 62.0;
	Float_t cutValue3 = 128.0;
	Float_t cutValue4 = 132.0;
	Float_t cutValue5 = 118.0;
	Float_t cutValue6 = 113.0;
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

	TString name = "TEfficiencies of Algorithms";
	teff_name1 = name;
	teff_name2 = name;
	teff_name3 = name;
	teff_name4 = name;
	teff_name5 = name;
	teff_name6 = name;

	TString ylabel = "Efficiency";
	TString xlabel1 = "metoffrecal";
	teff_title1 = teff_name1 + ";" + xlabel1 + ";" + ylabel + ";";
	teff_title2 = teff_name2 + ";" + xlabel1 + ";" + ylabel + ";";
	teff_title3 = teff_name3 + ";" + xlabel1 + ";" + ylabel + ";";
	teff_title4 = teff_name4 + ";" + xlabel1 + ";" + ylabel + ";";
	teff_title5 = teff_name5 + ";" + xlabel1 + ";" + ylabel + ";";
	teff_title6 = teff_name6 + ";" + xlabel1 + ";" + ylabel + ";";

	TString xlabel2 = "MET No Mu";
	
	teff_title11 = teff_name1 + ";" + xlabel2 + ";" + ylabel + ";";
	teff_title22 = teff_name2 + ";" + xlabel2 + ";" + ylabel + ";";
	teff_title33 = teff_name3 + ";" + xlabel2 + ";" + ylabel + ";";
	teff_title44 = teff_name4 + ";" + xlabel2 + ";" + ylabel + ";";
	teff_title55 = teff_name5 + ";" + xlabel2 + ";" + ylabel + ";";
	teff_title66 = teff_name6 + ";" + xlabel2 + ";" + ylabel + ";";

	

	TEfficiency* teff1 = new TEfficiency(teff_name1, teff_title1, nbins, metMin, metMax);
	TEfficiency* teff2 = new TEfficiency(teff_name2, teff_title2, nbins, metMin, metMax);
	TEfficiency* teff3 = new TEfficiency(teff_name3, teff_title3, nbins, metMin, metMax);
	TEfficiency* teff4 = new TEfficiency(teff_name4, teff_title4, nbins, metMin, metMax);
	TEfficiency* teff5 = new TEfficiency(teff_name5, teff_title5, nbins, metMin, metMax);
	TEfficiency* teff6 = new TEfficiency(teff_name6, teff_title6, nbins, metMin, metMax);

	TEfficiency* teff11 = new TEfficiency(teff_name1, teff_title11, nbins, metMin, metMax);
	TEfficiency* teff22 = new TEfficiency(teff_name2, teff_title22, nbins, metMin, metMax);
	TEfficiency* teff33 = new TEfficiency(teff_name3, teff_title33, nbins, metMin, metMax);
	TEfficiency* teff44 = new TEfficiency(teff_name4, teff_title44, nbins, metMin, metMax);
	TEfficiency* teff55 = new TEfficiency(teff_name5, teff_title55, nbins, metMin, metMax);
	TEfficiency* teff66 = new TEfficiency(teff_name6, teff_title66, nbins, metMin, metMax);


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

	int passmuon;
	int nentries = tree->GetEntries();
	Float_t offrecal;
	tree->SetBranchAddress("passmu24med", &passmuon);
	tree->SetBranchAddress("metoffrecal", &offrecal);

	std::cout << "Creating TEfficiencies..." << std::endl;


	for (Long64_t j = 0; j < nentries; j++)
	{
		Float_t mexnomu = mexoffrecal - mexofflineMuon;
		Float_t meynomu = meyoffrecal - meyofflineMuon;
		Float_t metnomu = TMath::Power((TMath::Power(mexnomu, 2.0) + TMath::Power(meynomu, 2.0)),0.5); //calculate correct offline value (no mu MET)
		tree->GetEntry(j);

		if (passmuon == 1)
		{
			teff1->Fill((passed_hist_met1 > cutValue1), offrecal);
			teff2->Fill((passed_hist_met2 > cutValue2), offrecal);
			teff3->Fill((passed_hist_met3 > cutValue3), offrecal);
			teff4->Fill((passed_hist_met4 > cutValue4), offrecal);
			teff5->Fill((passed_hist_met5 > cutValue5), offrecal);
			teff6->Fill((passed_hist_met6 > cutValue6), offrecal);

			teff11->Fill((passed_hist_met1 > cutValue1), metnomu);
			teff22->Fill((passed_hist_met2 > cutValue2), metnomu);
			teff33->Fill((passed_hist_met3 > cutValue3), metnomu);
			teff44->Fill((passed_hist_met4 > cutValue4), metnomu);
			teff55->Fill((passed_hist_met5 > cutValue5), metnomu);
			teff66->Fill((passed_hist_met6 > cutValue6), metnomu);
		}
	}

	TCanvas* c1 = new TCanvas("TEfficiencies","TEfficiencies");
	c1->Divide(2);
	c1->cd(1);
	TLegend* leg1 = new TLegend(0.25, 0.5, 0.15, 0.15);
	leg1->SetFillColor(kWhite);
	leg1->SetFillStyle(1001);
	leg1->AddEntry(teff1, alg1, "L");
	leg1->AddEntry(teff2, alg2, "L");
	leg1->AddEntry(teff3, alg3, "L");
	leg1->AddEntry(teff4, alg4, "L");
	leg1->AddEntry(teff5, alg5, "L");
	leg1->AddEntry(teff6, alg6, "L");

	teff1->Draw();
	teff2->SetLineColor(kBlue);
	teff2->Draw("same");
	teff3->SetLineColor(kRed);
	teff3->Draw("same");
	teff4->SetLineColor(kGreen);
	teff4->Draw("same");
	teff5->SetLineColor(kViolet);
	teff5->Draw("same");
	teff6->SetLineColor(kOrange);
	teff6->Draw("same");
	leg1->Draw("same");


	c1->cd(2);
	TLegend* leg2 = new TLegend(0.25, 0.5, 0.15, 0.15);
	TLegend* leg = new TLegend(0.25, 0.5, 0.15, 0.15);
	leg2->SetFillColor(kWhite);
	leg2->SetFillStyle(1001);
	leg2->AddEntry(teff11, alg1, "L");
	leg2->AddEntry(teff22, alg2, "L");
	leg2->AddEntry(teff33, alg3, "L");
	leg2->AddEntry(teff44, alg4, "L");
	leg2->AddEntry(teff55, alg5, "L");
	leg2->AddEntry(teff66, alg6, "L");

	teff11->Draw();
	teff22->SetLineColor(kBlue);
	teff22->Draw("same");
	teff33->SetLineColor(kRed);
	teff33->Draw("same");
	teff44->SetLineColor(kGreen);
	teff44->Draw("same");
	teff55->SetLineColor(kViolet);
	teff55->Draw("same");
	teff66->SetLineColor(kOrange);
	teff66->Draw("same");
	leg2->Draw("same");
	
	TEfficiency* efficiencies[12] = { teff1 ,teff2 ,teff3 ,teff4 ,teff5 ,teff6 ,teff11,teff22,teff33,teff44,teff55,teff66 };


	TString singleFileName = "Single_File";
	TString fileExt = ".pdf";
	TString targetDirectory("../pictures/");

	TString fullPath(targetDirectory + singleFileName + fileExt);

	myCanv->Print(fullPath + "[");
	for (int m = 0; m < 12; m++)
	{
		//generate canvas name each iteration
		sprintf(canvname, "canv%d", m);
		//reassign canvas to new name
		myCanv = new TCanvas(canvname, "");
		//put the fit onto the new canvas
		efficiencies[i]->Draw();
		//write the new canvas to file 
		myCanv->Print(fullPath);
	}
	//close the file ;suppress printing
	myCanv->Print(fullPath + "]");



	c1->Draw();

	
}
