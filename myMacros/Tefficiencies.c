{
	TString fileName = "../myData/ExpressMuons2016newanalysis.11runs.root";
	TFile * 2016Data = TFile::Open(fileName, "READ");
	int nbins = 60;
	Double_t metMin = 0.0;
	Double_t metMax = 700.0;
	
	TString xaxis = "MET [GeV]";
	TString yaxis = "Events";

	//these are zero bias thresholds WITHOUT RNDM
	Float_t metl1thresh = 45.0;
	Float_t metcellthresh = 62.0;
	Float_t metmhtthresh = 128.0;
	Float_t mettopoclthresh = 132.0;
	Float_t mettopoclpsthresh = 118.0;
	Float_t mettopoclpucthresh = 113.0;

	TString metl1HistoParam = ("metl1" + Form(" > %.2f", metl1thresh) + " HIST; " + xaxis + ";" + yaxis);
	TString metcellHistoParam = ("metcell" + Form(" > %.2f", metcellthresh) + " HIST; " + xaxis + ";" + yaxis);
	TString metmhtHistoParam = ("metmht" + Form(" > %.2f", metmhtthresh) + " HIST; " + xaxis + ";" + yaxis);
	TString mettopoclHistoParam = ("mettopocl" + Form(" > %.2f", mettopoclthresh) + " HIST; " + xaxis + ";" + yaxis);
	TString mettopoclpsHistoParam = ("mettopoclps" + Form(" > %.2f", mettopoclpsthresh) + " HIST; " + xaxis + ";" + yaxis);
	TString mettopoclpucHistoParam = ("mettopoclpuc" + Form(" > %.2f", mettopoclpucthresh) + " HIST; " + xaxis + ";" + yaxis);

	TEfficiency* metl1_teff = new TEfficiency("metl1", "MetL1; MetNoMu;Efficiency;", nbins, metMin, metMax);
	TEfficiency* metcell_teff = new TEfficiency("metcell", "MetCell; MetNoMu;Efficiency;", nbins, metMin, metMax);
	TEfficiency* metmht_teff = new TEfficiency("metmht", "MetMht; MetNoMu;Efficiency;", nbins, metMin, metMax);
	TEfficiency* mettopocl_teff = new TEfficiency("mettopocl", "Mettopocl; MetNoMu;Efficiency;", nbins, metMin, metMax);
	TEfficiency* mettopoclps_teff = new TEfficiency("mettopoclps", "Mettopoclps; MetNoMu;Efficiency;", nbins, metMin, metMax);
	TEfficiency* mettopoclpuc_teff = new TEfficiency("mettopoclpuc", "Mettopoclpuc; MetNoMu;Efficiency;", nbins, metMin, metMax);

	TH2F* metl1 = new TH2F("metl1", "metl1", nbins, metMin, metMax, nbins, metMin, metMax);
	TH2F* metcell = new TH2F("metcell", "metcell", nbins, metMin, metMax, nbins, metMin, metMax);
	TH2F* metmht = new TH2F("metmht", "metmht", nbins, metMin, metMax, nbins, metMin, metMax);
	TH2F* mettopocl = new TH2F("mettopocl", "mettopocl", nbins, metMin, metMax, nbins, metMin, metMax);
	TH2F* mettopoclps = new TH2F("mettopoclps", "mettopoclps", nbins, metMin, metMax, nbins, metMin, metMax);
	TH2F* mettopoclpuc = new TH2F("mettopoclpuc", "mettopoclpuc", nbins, metMin, metMax, nbins, metMin, metMax);
	TH2F* offrecal = new TH2F("offrecal", "offrecal", nbins, metMin, metMax, nbins, metMin, metMax);

	Float_t metl1_met;
	Float_t metcell_met;
	Float_t metmht_met;
	Float_t mettopocl_met;
	Float_t mettopoclps_met;
	Float_t mettopoclpuc_met;
	tree->SetBranchAddress("metl1", &metl1_met);
	tree->SetBranchAddress("metcell", &metcell_met);
	tree->SetBranchAddress("metmht", &metmht_met);
	tree->SetBranchAddress("mettopocl", &mettopocl_met);
	tree->SetBranchAddress("mettopoclps", &mettopoclps_met);
	tree->SetBranchAddress("mettopoclpuc", &mettopoclpuc_met);

	Float_t offrecal_mex, offrecal_mey, offrecalmuon_mex, offrecalmuon_mey;

	Int_t passmuon , passcleancuts , recalbroke;
	int nentries = tree->GetEntries();

	std::cout << "Creating TEfficiencies..." << std::endl;

	tree->SetBranchAddress("passmu24med", &passmuon);
	tree->SetBranchAddress("passcleancuts", &passcleancuts);
	tree->SetBranchAddress("recalbroke", &recalbroke);

	tree->SetBranchAddress("mexoffrecal", &offrecal_mex);
	tree->SetBranchAddress("meyoffrecal", &offrecal_mey);
	tree->SetBranchAddress("mexoffrecalmuon", &offrecalmuon_mex);
	tree->SetBranchAddress("meyoffrecalmuon", &offrecalmuon_mey);

	for (Long64_t j = 0; j < nentries; j++)
	{
		tree->GetEntry(j);
		if (passmuon > 0.1  )
		{
			Float_t metnomu = sqrt(((offrecal_mex - offrecalmuon_mex) * (offrecal_mex - offrecalmuon_mex)) +
				((offrecal_mey - offrecalmuon_mey)*(offrecal_mey - offrecalmuon_mey))); //compute metnomu

			metl1_teff->Fill((metl1_met > metl1thresh), metnomu);
			metcell_teff->Fill((metcell_met > metcellthresh), metnomu);
			metmht_teff->Fill((metmht_met > metmhtthresh), metnomu);
			mettopocl_teff->Fill((mettopocl_met > mettopoclthresh), metnomu);
			mettopoclps_teff->Fill((mettopoclps_met > mettopoclpsthresh), metnomu);
			mettopoclpuc_teff->Fill((mettopoclpuc_met > mettopoclpucthresh), metnomu);
		

			//SCATTER PLOTS ARE VERSUS OFFRECAL, NOT METNOMU
			metl1->Fill(metoffrecal,metl1_met);
			metcell->Fill(metoffrecal,metcell_met);
			metmht->Fill(metoffrecal,metmht_met);
			mettopocl->Fill(metoffrecal,mettopocl_met);
			mettopoclps->Fill(metoffrecal,mettopoclps_met);
			mettopoclpuc->Fill(metoffrecal,mettopoclpuc_met);
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
	leg1->AddEntry(metl1_teff, "metl1", "L");
	leg1->AddEntry(metcell_teff, "metcell", "L");
	leg1->AddEntry(metmht_teff, "metmht", "L");
	leg1->AddEntry(mettopocl_teff, "mettopocl", "L");
	leg1->AddEntry(mettopoclps_teff, "mettopoclps", "L");
	leg1->AddEntry(mettopoclpuc_teff, "mettopoclpuc", "L");
	leg1->SetTextSize(0.05);
	metl1_teff->Draw();
	metcell_teff->SetLineColor(kBlue);
	metcell_teff->Draw("same");
	metmht_teff->SetLineColor(kRed);
	metmht_teff->Draw("same");
	mettopocl_teff->SetLineColor(kGreen);
	mettopocl_teff->Draw("same");
	mettopoclps_teff->SetLineColor(kViolet);
	mettopoclps_teff->Draw("same");
	mettopoclpuc_teff->SetLineColor(kOrange);
	mettopoclpuc_teff->Draw("same");
	leg1->Draw("same");
	c1->cd(2);
	TLegend* leg2 = new TLegend(0.25, 0.5, 0.15, 0.15);
	TLegend* leg = new TLegend(0.25, 0.5, 0.15, 0.15);
	leg2->SetFillColor(kWhite);
	leg2->SetFillStyle(1001);
	leg2->SetNColumns(2);
	leg2->AddEntry(metl1_teff, "metl1", "L");
	leg2->AddEntry(metcell_teff2, "metcell", "L");
	leg2->AddEntry(metmht_teff3, "metmht", "L");
	leg2->AddEntry(mettopocl_teff4, "mettopocl", "L");
	leg2->AddEntry(mettopoclps_teff5, "mettopoclps", "L");
	leg2->AddEntry(mettopoclpuc_teff6, "mettopoclpuc", "L");
	leg2->SetTextSize(0.05);
	metl1_teff->Draw();
	metcell_teff2->SetLineColor(kBlue);
	metcell_teff2->Draw("same");
	metmht_teff3->SetLineColor(kRed);
	metmht_teff3->Draw("same");
	mettopocl_teff4->SetLineColor(kGreen);
	mettopocl_teff4->Draw("same");
	mettopoclps_teff5->SetLineColor(kViolet);
	mettopoclps_teff5->Draw("same");
	mettopoclpuc_teff6->SetLineColor(kOrange);
	mettopoclpuc_teff6->Draw("same");
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





	TEfficiency* efficiencies[12] = { metl1_teff ,metcell_teff ,metmht_teff ,mettopocl_teff ,mettopoclps_teff ,mettopoclpuc_teff ,metl1_teff,metcell_teff2,metmht_teff3,mettopocl_teff4,mettopoclps_teff5,mettopoclpuc_teff6 };
	
	
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
