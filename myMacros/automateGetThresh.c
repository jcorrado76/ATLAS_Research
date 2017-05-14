Int_t automateGetThresh(Float_t frac = 0.003105)
{
  /*
  This program takes in a certain fraction for two algorithms to keep individually, and then computes what fraction of events
  is kept when both of the algorithms are used at those thresholds
  */


  //fraction so metcell and metmht together keep 1-^-4
  TString fileName = "../myData/ZeroBias2016new.13Runs.root";
  TFile * 2016Data = TFile::Open(fileName, "READ");
  Int_t nentries = tree->GetEntries();
  Int_t nbins = 60;
	Double_t metMin = 0.0;
	Double_t metMax = 500.0;
  Int_t passrndm, numRndm = 0;
  Float_t metcell,metmht;
  std::cout << "Number of entries in the tree: " << nentries << std::endl;

  tree->SetBranchAddress("metcell",&metcell);
  tree->SetBranchAddress("metmht",&metmht);
  tree->SetBranchAddress("passrndm",&passrndm);

  TH1F* combinedAlgHist = new TH1F("Combined Hist" , "Combined Hist"  , nbins, metMin, metMax);
  TH1F* metcellHist = new TH1F("metcell", "metcell", nbins, metMin, metMax);
  TH1F* metmhtHist = new TH1F("metmht", "metmht", nbins, metMin, metMax);
  TH1F *metcelltarget = new TH1F("cumu2", "cumu", nbins, metMin, metMax); //used to generate cumulative right tail sums
  TH1F *metmhttarget = new TH1F("cumu3", "cumu", nbins, metMin, metMax); //used to generate cumulative right tail sums

  //fill with passrndm
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

  Float_t numbToKeep = numRndm * frac // how many events is 10^(-4) of passrndm
  //=============================================================================
  //determine threshold to keep 10^(-4) events for just algorithm A
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
  //determine threshold to keep 10^(-4) events for just algorithm B
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
  //all this does is print determine how many events are kept from combined algorithm and prints it
  std::cout << "Determining Ratio Kept from Combined Algorithm..." << std::endl;
  Int_t countC,countA,countB = 0 ;
  for (Int_t k = 0 ; k < nentries; k++)
  {
    tree->GetEntry(k);
    if ((passrndm > 0.1) && (metmht > metmhtthresh) && (metcell > metcellthresh))
    {
      countC++;
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
  std::cout << "Number of events kept after combined alg: " << countC << std::endl;
  Float_t fractionC = (Float_t) countC / (Float_t) numRndm;
  Float_t fractionA = (Float_t) countA / (Float_t) numRndm;
  Float_t fractionB = (Float_t) countB / (Float_t) numRndm;
  std::cout << "Fraction of Events kept after combined alg: " << fractionC << std::endl;
  std::cout << "Fraction of Events kept after alg A: " << fractionA << std::endl;
  std::cout << "Fraction of Events kept after alg B: " << fractionB << std::endl;

return(0);
}
