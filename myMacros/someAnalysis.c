Int_t someAnalysis()
{
  TString fileName = "../myData/ZeroBias2016new.13Runs.root";
  TFile * 2016Data = TFile::Open(fileName, "READ");
  Int_t nentries = tree->GetEntries();
  Int_t nbins = 60;
	Double_t metMin = 0.0;
	Double_t metMax = 500.0;
  std::cout << "Number of entries in the tree: " << nentries << std::endl;

  Int_t passRndm, numRndm = 0;
  Float_t metcell;

  tree->SetBranchAddress("metcell",&metcell);
  tree->SetBranchAddress("passrndm",&passRndm);
  TH1F * myHist = new TH1F("myHist", "myHist", nbins, metMin, metMax);

  for (Int_t i = 0; i < nentries; i++)
  {
    tree->GetEntry(i);
    if (passRndm > 0.1)
    {
      numRndm++;
      myHist->Fill(metcell);
    }
  }

  Float_t ratio = (Float_t) numRndm / (Float_t) nentries;

  std::cout << "Number of passrndm entries: " << numRndm << std::endl;
  std::cout << "Ratio of passrndm to nentries: " << ratio << std::endl;
  myHist->Draw();
  /*
  std::cout<< "Mean of hist: " <<   myHist->GetMean() << std::endl;
  std::cout << "Variance of Hist: " << myHist->GetRMS() << std::endl;

  Double_t thresh = ROOT::Math::normal_quantile_c(1.e-4,2.743105904);
  std::cout << "Tentative threshold: " << thresh + 12.9278 << std::endl;
  */

}
