Int_t getThresh(Float_t frac = 0.003105)
{
  TString fileName = "../myData/ZeroBias2016new.13Runs.root";
  TFile * 2016Data = TFile::Open(fileName, "READ");
  Int_t nentries = tree->GetEntries();
  Int_t nbins = 60;
	Double_t metMin = 0.0;
	Double_t metMax = 500.0;
  std::cout <<"Fraction to Keep Individually: " << frac << std::endl;
  std::cout << "Number of entries in the tree: " << nentries << std::endl;

  Float_t fracA = frac;
  Float_t fracB = frac;

  Int_t passrndm, numRndm = 0;
  Float_t metcell,metmht;

  tree->SetBranchAddress("metcell",&metcell);
  tree->SetBranchAddress("metmht",&metmht);
  tree->SetBranchAddress("passrndm",&passrndm);

  TH1F* combinedAlgHist = new TH1F("Combined Hist" , "Combined Hist"  , nbins, metMin, metMax);
  TH1F* metcellHist = new TH1F("metcell", "metcell", nbins, metMin, metMax);
  TH1F* metmhtHist = new TH1F("metmht", "metmht", nbins, metMin, metMax);
  TH1F *metcelltarget = new TH1F("cumu2", "cumu", nbins, metMin, metMax);
  TH1F *metmhttarget = new TH1F("cumu3", "cumu", nbins, metMin, metMax);





  for (Int_t i = 0 ; i < nentries ; i++)
  {
    tree->GetEntry(i);
    if (passrndm > 0.1)
    {
      numRndm++;
      metcellHist->Fill(metcell);
			metmhtHist->Fill(metmht);
    }
  }


/*  Float_t epsilon = 5.0;
  Int_t count = 0;
  while ( count - 423 > epsilon ||  count - 423 < -epsilon)
  {*/
    std::cout << "Number of entries that pass rndm: " << numRndm << std::endl;
    Float_t numKeepA = numRndm * fracA;
    Float_t numKeepB = numRndm * fracB;
    //=============================================================================
    std::cout << "Determining threshold for metcell..." << std::endl;
    for (int t = nbins; t >= 0; t--)
    {
      Float_t summ2 = 0;

      for (int i = t; i <= nbins; i++)
      {
        summ2 += metcellHist->GetBinContent(i);
      }
      metcelltarget->SetBinContent(t, summ2);
    }
    for (int t = nbins; t >= 0; t--)
    {
      if ((abs(metcelltarget->GetBinContent(t) - (numKeepA) > 0) != (abs(metcelltarget->GetBinContent(t + 1) - (numKeepA)) > 0)))
      {
        Float_t metcellthresh = metcelltarget->GetBinCenter(t);
      }
    }
    std::cout << "Threshold for metcell: " << metcellthresh << std::endl;
    //===================================================================================
    std::cout << "Determining threshold for metmht..." << std::endl;
    for (Int_t t = nbins; t >= 0 ; t--)
    {
      Float_t summ3 = 0;

      for (int i = t; i <= nbins; i++)
      {
        summ3 += metmhtHist->GetBinContent(i);
      }
      metmhttarget->SetBinContent(t, summ3);
    }
    for (int t = nbins; t >= 0; t--)
    {
      if ((abs(metmhttarget->GetBinContent(t) - (numKeepB) > 0) != (abs(metmhttarget->GetBinContent(t + 1) - (numKeepB)) > 0)))
      {
        Float_t metmhtthresh = metmhttarget->GetBinCenter(t);
      }
    }
    std::cout << "Threshold for metmht: " << metmhtthresh << std::endl;
    //=================================================================================
    std::cout << "Determining Ratio Kept from Combined Algorithm..." << std::endl;

    Int_t count,countA,countB = 0 ;
    for (Int_t k = 0 ; k < nentries; k++)
    {
      tree->GetEntry(k);
      if ((passrndm > 0.1) && (metmht > metmhtthresh) && (metcell > metcellthresh))
      {
        count++;
      }
      if((passrndm > 0.1) && metcell > metcellthresh)
      {
        countA++;
      }
      if((passrndm > 0.1) && metmht>metmhtthresh)
      {
        countB++;
      }
    }
    std::cout << "Number of events kept after only metcell: " << countA << std::endl;
    std::cout << "Number of events kept after only metmht: " << countB << std::endl;
    std::cout << "Number of events kept after combined alg: " << count << std::endl;
    Float_t fraction = (Float_t) count / (Float_t) numRndm;
    std::cout << "Fraction of Events kept after combined alg: " << fraction << std::endl;
//}
  return(0);
}
