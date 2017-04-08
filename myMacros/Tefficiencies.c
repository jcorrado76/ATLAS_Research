{
	#include <string>
	#include <iostream>
	#include <cstdlib>

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
	Float_t cutValue2 = 1.0;
	//Float_t cutValue2 = 62.0;
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

	teff_name1 = "metl1";
	teff_name2 = "metcell";
	teff_name3 = "metmht";
	teff_name4 = "mettopocl";
	teff_name5 = "mettopoclps";
	teff_name6 = "mettopoclpuc";

	TString ylabel = "Efficiency";
	TString xlabel1 = "metoffrecal";
	teff_title1 = teff_name1 + ";" + xlabel1 + ";" + ylabel + ";";
	teff_title2 = teff_name2 + ";" + xlabel1 + ";" + ylabel + ";";
	teff_title3 = teff_name3 + ";" + xlabel1 + ";" + ylabel + ";";
	teff_title4 = teff_name4 + ";" + xlabel1 + ";" + ylabel + ";";
	teff_title5 = teff_name5 + ";" + xlabel1 + ";" + ylabel + ";";
	teff_title6 = teff_name6 + ";" + xlabel1 + ";" + ylabel + ";";

	TString xlabel2 = "MET Offrecal Muon";

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

	Float_t mexoffrecal, meyoffrecal, mexoffrecalMuon, meyoffrecalMuon, metoffrecal, metoffrecalmuon;

	

	Int_t passmuon , passcleancuts , recalbroke;
	int nentries = tree->GetEntries();

	std::cout << "Creating TEfficiencies..." << std::endl;

	tree->SetBranchAddress("passmu24med", &passmuon);
	tree->SetBranchAddress("passcleancuts", &passcleancuts);
	tree->SetBranchAddress("recalbroke", &recalbroke);

	tree->SetBranchAddress("mexoffrecal", &mexoffrecal);
	tree->SetBranchAddress("meyoffrecal", &meyoffrecal);
	tree->SetBranchAddress("metoffrecal", &metoffrecal);
	tree->SetBranchAddress("mexoffrecalmuon", &mexoffrecalMuon);
	tree->SetBranchAddress("meyoffrecalmuon", &meyoffrecalMuon);
	tree->SetBranchAddress("metoffrecalmuon", &metoffrecalmuon);


	TH2F* metl1 = new TH2F("metl1","metl1",nbins,metMin,metMax, nbins, metMin, metMax);
	TH2F* metcell = new TH2F("metcell","metcell", nbins, metMin, metMax, nbins, metMin, metMax);
	TH2F* metmht = new TH2F("metmht","metmht", nbins, metMin, metMax, nbins, metMin, metMax);
	TH2F* mettopocl = new TH2F("mettopocl","mettopocl", nbins, metMin, metMax, nbins, metMin, metMax);
	TH2F* mettopoclps = new TH2F("mettopoclps","mettopoclps", nbins, metMin, metMax, nbins, metMin, metMax);
	TH2F* mettopoclpuc = new TH2F("mettopoclpuc","mettopoclpuc", nbins, metMin, metMax, nbins, metMin, metMax);
	TH2F* offrecal = new TH2F("offrecal","offrecal", nbins, metMin, metMax, nbins, metMin, metMax);

	for (Long64_t j = 0; j < nentries; j++)
	{
		Float_t mexnomu = mexoffrecal - mexoffrecalMuon;
		Float_t meynomu = meyoffrecal - meyoffrecalMuon;

		Float_t metnomu = sqrt((mexnomu*mexnomu) + (meynomu*meynomu)); //calculate correct offline value (no mu MET)
		tree->GetEntry(j);
		bool pass;
		if (passmuon > 0.1  )
		{
			if (passed_hist_met1 > cutValue1)
			{
				pass = true;
			}
			else {
				pass = false;
			}
			//teff1->Fill((passed_hist_met1 > cutValue1), metoffrecal);
			teff1->Fill(pass, metoffrecal);
			teff2->Fill((passed_hist_met2 > cutValue2), metoffrecal);
			teff3->Fill((passed_hist_met3 > cutValue3), metoffrecal);
			teff4->Fill((passed_hist_met4 > cutValue4), metoffrecal);
			teff5->Fill((passed_hist_met5 > cutValue5), metoffrecal);
			teff6->Fill((passed_hist_met6 > cutValue6), metoffrecal);

			teff11->Fill((passed_hist_met1 > cutValue1), metnomu);
			teff22->Fill((passed_hist_met2 > cutValue2), metnomu);
			teff33->Fill((passed_hist_met3 > cutValue3), metnomu);
			teff44->Fill((passed_hist_met4 > cutValue4), metnomu);
			teff55->Fill((passed_hist_met5 > cutValue5), metnomu);
			teff66->Fill((passed_hist_met6 > cutValue6), metnomu);
		
			metl1->Fill(metoffrecal,passed_hist_met1);
			metcell->Fill(metoffrecal,passed_hist_met2);
			metmht->Fill(metoffrecal,passed_hist_met3);
			mettopocl->Fill(metoffrecal,passed_hist_met4);
			mettopoclps->Fill(metoffrecal,passed_hist_met5);
			mettopoclpuc->Fill(metoffrecal,passed_hist_met6);
			offrecal->Fill(metoffrecal,metoffrecal);
		}
	}


	//DRAWING===========================================================================
	TCanvas* c1 = new TCanvas("TEfficiencies",title = "TEfficiencies");
	c1->Divide(2);
	c1->cd(1);
	TLegend* leg1 = new TLegend(0.25, 0.5, 0.15, 0.15);
	leg1->SetFillColor(kWhite);
	leg1->SetFillStyle(1001);
	leg1->SetNColumns(2);
	leg1->AddEntry(teff1, alg1, "L");
	leg1->AddEntry(teff2, alg2, "L");
	leg1->AddEntry(teff3, alg3, "L");
	leg1->AddEntry(teff4, alg4, "L");
	leg1->AddEntry(teff5, alg5, "L");
	leg1->AddEntry(teff6, alg6, "L");
	leg1->SetTextSize(0.05);
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
	leg2->SetNColumns(2);
	leg2->AddEntry(teff11, alg1, "L");
	leg2->AddEntry(teff22, alg2, "L");
	leg2->AddEntry(teff33, alg3, "L");
	leg2->AddEntry(teff44, alg4, "L");
	leg2->AddEntry(teff55, alg5, "L");
	leg2->AddEntry(teff66, alg6, "L");
	leg2->SetTextSize(0.05);
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
//--------------------------------------------------------------------
	TCanvas* metl1Scatter = new TCanvas("metl1", title = "metl1");
	metl1->Draw();
	TCanvas* metcellScatter = new TCanvas("metcell", title = "metcell");
	metcell->Draw();
	TCanvas* metmhtScatter = new TCanvas("metmht", title = "metmht");
	metmht->Draw();
	TCanvas* mettopoclScatter = new TCanvas("mettopocl", title = "mettopocl");
	mettopocl->Draw();
	TCanvas* mettopoclpsScatter = new TCanvas("mettopoclps", title = "mettopoclps");
	mettopoclps->Draw();
	TCanvas* mettopoclpucScatter = new TCanvas("mettopoclpuc", title = "mettopoclpuc");
	mettopoclpuc->Draw();
	TCanvas* offrecalScatter = new TCanvas("offrecal", title = "offrecal");
	offrecal->Draw();


	TCanvas* scatter[12] = { metl1Scatter ,metcellScatter ,metmhtScatter ,mettopoclScatter ,mettopoclpsScatter ,mettopoclpucScatter ,offrecalScatter};

	//TString path = "../pictures/tefficiencies/Tefficiencies.pdf";
	TString path = "../pictures/ScatterTest.pdf";
	TString scatter("");
	TCanvas* scatterCanv = new TCanvas(scatter, "");
	scatterCanv.Print(path + "[");
	for (int m = 0; m < 12; m++)
	{
		scatter[m]->Draw();
		scatterCanv->Print(path);
	}
	scatterCanv.Print(path + "]");





	TEfficiency* efficiencies[12] = { teff1 ,teff2 ,teff3 ,teff4 ,teff5 ,teff6 ,teff11,teff22,teff33,teff44,teff55,teff66 };
	
	
	ifstream inFile;
	TString path = "../pictures/tefficiencies/Tefficiencies.pdf";
	inFile.open(path);

	char response,response2;
	if (!inFile.fail()) // if it doesn't fail, the file exists
	{
		std::cout << "A file by that path already exists.\n" 
			<< "Do you want to continue and overwrite it\n"
			<< " with the new data (y or n): ";

		std::cin >> response;

		if (std::tolower(response) == 'n')
		{
			std::cout << "The existing file will not be overwritten."
				<< "Do you want to append copy number to file namme?"
			std::cin >> response2;
			if (std::tolower(response2) == 'y')
			{
				char appendage;
				std::cout << "Enter string to append:\n"
				std::cin >> appendage;
				path = path + appendage;
				std::cout << "New path successfully generated" << std::endl;
			}
			else
			{
				std::cout << "Exiting" << std::endl;
				std::exit(1);
			}
		}
	}

	
	TString canvname("");
	TCanvas* teffCanv = new TCanvas(canvname, "");
	teffCanv.Print(path+"[");
	for (int m = 0; m < 12; m++)
	{	
		efficiencies[m]->Draw();
		teffCanv->Print(path);
	}
	teffCanv.Print(path + "]");
}
