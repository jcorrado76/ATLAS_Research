Int_t plotEfficiency(TString& algName, Double_t cut,TString& signalFile = "ExpressMuons2016newanalysis.11runs.root")
{

	/*
	Joseph Corrado plotEffiency.c
	Plots effiencies of various ATLAS algorithms versus the MET OFFLINE RECAL algorithm
	*/

	TString fileName = "../myData/" + signalFile;
	TFile * 2016Data = TFile::Open(fileName, "READ");

	Int_t nbins = 100;
	Double_t metMin = 0.0;
	Double_t metMax = 500.0;

//========================================================================================================================
		TString teff_name = algName + " vs metoffrecal";
		teff_title = teff_name + " Efficiency ; GeV ; Efficiency";

		Float_t algorithmMET, offrecal_met, offrecal_mex, offrecal_mey, offrecalmuon_mex, offrecalmuon_mey,metoffrecal;
		Int_t passrndm,passmuon,cleanCutsFlag, recalBrokeFlag;

		tree->SetBranchAddress(algName, &algorithmMET);
		tree->SetBranchAddress("metoffrecal", &metoffrecal);
		tree->SetBranchAddress("passrndm", &passrndm);
		tree->SetBranchAddress("passmu24med", &passmuon);
		tree->SetBranchAddress("passcleancuts", &cleanCutsFlag); // get cleancuts flag
		tree->SetBranchAddress("recalbroke", &recalBrokeFlag); // get recalbroke flag
		tree->SetBranchAddress("metoffrecal", &offrecal_met);
		tree->SetBranchAddress("mexoffrecal", &offrecal_mex);
		tree->SetBranchAddress("meyoffrecal", &offrecal_mey);
		tree->SetBranchAddress("mexoffrecalmuon", &offrecalmuon_mex);
		tree->SetBranchAddress("meyoffrecalmuon", &offrecalmuon_mey);

		TH1F *algHist     = new TH1F(algName,algName, nbins, metMin, metMax);
		TEfficiency *teff = new TEfficiency(teff_name, teff_title, nbins, metMin, metMax);
		Int_t nentries    = tree->GetEntries();

		for (Int_t i = 0; i < nentries; i++)
		{
			tree->GetEntry(i);
			if ( passmuon > 0.1 )
			{
				Float_t metnomu = sqrt(((offrecal_mex - offrecalmuon_mex) * (offrecal_mex - offrecalmuon_mex)) +
					((offrecal_mey - offrecalmuon_mey)*(offrecal_mey - offrecalmuon_mey))); //compute metnomu

				algHist->Fill(algorithmMET);
				teff->Fill(algorithmMET > cut, metnomu);
			}
		}

		TCanvas *c1 = new TCanvas("TEfficiency Canvas", "TEfficiency Canvas");
		c1->Divide(2);

		c1->cd(1);
		teff->Draw();

		c1->cd(2);
		algHist->Draw();

		c1->Draw();

		return(0);
	}
