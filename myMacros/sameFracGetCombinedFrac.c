Int_t sameFracGetCombinedFrac(TString& algA, TString& algB)
{
  /*
  This program generates the line that goes from the origin. It is the equiFraction kept line.
  The combined fraction kept is not constant, just the relationship between the fractions kept individually
  */
  //fraction so metcell and metmht together keep 10^-4
  //Float_t firstFrac = 0.003105;

  Float_t frac = 0.003105; // keeping this fraction for metcell and mht individually keeps 10^(-4) when combined
  TString fileName = "../myData/ZeroBias2016new.13Runs.root";
  TFile * 2016Data = TFile::Open(fileName, "READ");
  Int_t nentries = tree->GetEntries();
  Int_t nbins = 200;
	Double_t metMin = 0.0;
	Double_t metMax = 500.0;
  Int_t passrndm, numRndm = 0;
  Float_t algAMET,algBMET;
  std::cout << "Number of entries in the tree: " << nentries << std::endl;

  tree->SetBranchAddress(algA,&algAMET);
  tree->SetBranchAddress(algB,&algBMET);
  tree->SetBranchAddress("passrndm",&passrndm);

  TH1F *combinedAlgHist = new TH1F("Combined Hist" , "Combined Hist"  , nbins, metMin, metMax);
  TH1F *metcellHist = new TH1F("metcell", "metcell", nbins, metMin, metMax);
  TH1F *metmhtHist = new TH1F("metmht", "metmht", nbins, metMin, metMax);
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

  Float_t numbToKeep = (Float_t) (numRndm*frac); // how many events is the coresponding fraction of passrndm
  Float_t AthreshArray[20];
  Float_t BthreshArray[20];
  Float_t combinedFracArray[20];

  for (Int_t j = 0 ; j < 20 ; j++)
  {
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
        if ((abs(metcelltarget->GetBinContent(t) - (numbToKeep) > 0) != (abs(metcelltarget->GetBinContent(t + 1) - (numbToKeep)) > 0)))
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
        if ((abs(metmhttarget->GetBinContent(t) - (numbToKeep) > 0) != (abs(metmhttarget->GetBinContent(t + 1) - (numbToKeep)) > 0)))
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
      std::cout << "Current index of iteration: " << j << std::endl;
      AthreshArray[j] = metcellthresh;
      BthreshArray[j] = metmhtthresh;
      combinedFracArray[j] = fractionC;
      numbToKeep = numbToKeep + 10; //this starts at 10^(-4) and works toward origin by decreasing threshold to increase number kept on each iteration
}

return(0);
}
