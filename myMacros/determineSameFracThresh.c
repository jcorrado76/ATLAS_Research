Int_t determineSameFracThresh(TString& algA, TString algB, Float_t frac = (1.e-4))
{
  /*
  returns the 2 different thresholds for each of the 2 algorithms to keep the same fraction individually
  */


	using namespace std;
	/* determine zerobias thresholds for all algorithms*/
	TString fileName = "../myData/ZeroBias2016new.13Runs.root";
	std::cout << "Determining thresholds using data: " << fileName << std::endl;
	TFile *myFile = TFile::Open(fileName, "READ");

	Int_t nbins = 100;
	Double_t metMin = 0.0;
	Double_t metMax = 500.0;

	//initialize cut histograms to pass muon flag on to see how many events it keeps
	TH1F *indeterminate1Hist = new TH1F(algA, algA, nbins, metMin, metMax);
  TH1F *indeterminate2Hist = new TH1F(algB, algB, nbins, metMin, metMax);

	TString xlabel = "MET [GeV]";
	TString yaxis = "Events";
	Float_t indeterminate1,indeterminate2;
	Int_t passrndm;

	tree->SetBranchAddress("passrndm", &passrndm);
	tree->SetBranchAddress(algA,&indeterminate1);
  tree->SetBranchAddress(algB,&indeterminate2);

	//initialize histograms for right cumulative sum
	TH1F *indeterminate1target = new TH1F("cumu1", "cumu", nbins, metMin, metMax);
  TH1F *indeterminate2target = new TH1F("cumu2", "cumu", nbins, metMin, metMax);

	//fill cut histograms (only pass rndm)
	Int_t nentries = tree->GetEntries();
	std::cout << "nentries: " << nentries << std::endl;
	Float_t  indeterminate1thresh,indeterminate2thresh;


	//generate the cumulative right tail sum hist
		std::cout << "Determining individual thresholds for " << algA << " and " << algB << " to keep " << frac << " events..." << std::endl;
		Int_t numRndm =0;
		for (Long64_t k = 0; k < nentries; k++)
		{
			tree->GetEntry(k);
			if (passrndm > 0.1)
			{
				numRndm++;
				indeterminate1Hist->Fill(indeterminate1);
        indeterminate2Hist->Fill(indeterminate2);
			}
		}

    Float_t numKeep = numRndm * frac;

    std::cout << "numRndm: " << numRndm << std::endl;
    std::cout << "numKeep: " << numKeep << std::endl;



		for (Int_t t = nbins; t >= 0; t--)
		{
			Float_t summ1 = 0;

			for (Int_t i = t; i <= nbins; i++)
			{
				summ1 += indeterminate1Hist->GetBinContent(i);
			}
			indeterminate1target->SetBinContent(t, summ1);
		}
		for (Int_t t = nbins; t >= 0; t--)
		{
			if ((abs(indeterminate1target->GetBinContent(t) - (numKeep) > 0) != (abs(indeterminate1target->GetBinContent(t + 1) - (numKeep)) > 0)))
			{
				indeterminate1thresh = indeterminate1target->GetBinCenter(t);
			}
		}
//=========================================================================================================
    for (Int_t t = nbins; t >= 0; t--)
    {
      summ1 = 0;

      for (Int_t i = t; i <= nbins; i++)
      {
        summ1 += indeterminate2Hist->GetBinContent(i);
      }
      indeterminate2target->SetBinContent(t, summ1);
    }
    for (Int_t t = nbins; t >= 0; t--)
    {
      if ((abs(indeterminate2target->GetBinContent(t) - (numKeep) > 0) != (abs(indeterminate2target->GetBinContent(t + 1) - (numKeep)) > 0)))
      {
        indeterminate2thresh = indeterminate2target->GetBinCenter(t);
      }
    }
//========================================================================================

		std::cout << "Threshold for " << algA << ": " << indeterminate1thresh << std::endl;
    std::cout << "Threshold for " << algB << ": " << indeterminate2thresh << std::endl;

myFile.Close();

return(0);

}
