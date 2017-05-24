Float_t sameFracGetCombinedFrac(TString& algA, TString& algB)
{
//this program finds the point on the equifraction line extending from the origin in alg fraction space, where
//height above point is 10^(-4)
// this program will bisect to determine the fraction both algs need to keep in order to keep 10^(-4) combined

std::cout << "Will return the combined frac to yield 2 thresholds for the algorithms to keep 10^(-4) zero bias events combined
such that they keep the same fraction individually" << std::endl;

  TString fileName = "../myData/ZeroBias2016new.13Runs.root";
  TFile * 2016Data = TFile::Open(fileName, "READ");
  Int_t nentries = tree->GetEntries();
  Int_t nbins = 100;
	Double_t metMin = 0.0;
	Double_t metMax = 250.0;
  Int_t passrndm, numRndm = 0;
  Float_t algAMET,algBMET;
  Float_t algAMETx1thresh,algBMETx1thresh;
  Float_t algAMETx2thresh,algBMETx2thresh;
  Float_t algAMETx3thresh,algBMETx3thresh;
  Float_t CONDITION = 1.0*10**(-4.0);
  TString xlabel = "MET [GeV]";
  TString yaxis = "Events";
  Int_t counter1 = 0;
  Int_t counter2 = 0;
  Int_t counter3 = 0;


std::cout << "nentries: " << nentries << std::endl;

  tree->SetBranchAddress(algA,&algAMET);
  tree->SetBranchAddress(algB,&algBMET);
  tree->SetBranchAddress("passrndm",&passrndm);

  Int_t numRndm =0;
  for (Long64_t k = 0; k < nentries; k++)
  {
    tree->GetEntry(k);
    if (passrndm > 0.1)
    {
      numRndm++;
    }
  }

std::cout << "numCombined to keep: " << numRndm * CONDITION << std::endl;

  Float_t lwrbnd = CONDITION;
  Float_t uprbnd = 0.005;
  Float_t eps = 0.00025;
  //guess a value of B thresh, then run bisection until converge on thresh such that at fixed thresh of A,
  //using together keeps total 10^(-4)

  Float_t acthresh,bcthresh;

  std::cout << "Entering bisection to determine individual fractions" << std::endl;
  std::cout << "Lower Bound: " << lwrbnd << std::endl;
  std::cout << "Midpoint: " << (lwrbnd+uprbnd)/2. << std::endl;
  std::cout << "Upper Bound: " << uprbnd << std::endl;
  std::cout << "Epsilon: " << eps << std::endl;
  Int_t j = 0 ;
  Int_t imax = 30;
  Float_t x1,x3; //thresholds of individual algorithms
  Float_t f1,f2,f3 = 0; //number of events kept
  x1 = lwrbnd;
  x3 = uprbnd;
  Float_t initialGuess = ( x1 + x3 ) / 2.0;
  Float_t currentWidth = x3-x1;

  //determine how many events kept using the determined thresholds
  std::cout << "Determining the number of events kept at the endpoints of the interval and at midpoint..." << std::endl;

  TH1F *algAMETHist = new TH1F(algA, algA, nbins, metMin, metMax);
  TH1F *algBMETHist = new TH1F(algB, algB, nbins, metMin, metMax);

  //initialize histograms for right cumulative sum
  TH1F *algAMETtarget = new TH1F("cumu1", "cumu", nbins, metMin, metMax);
  TH1F *algBMETtarget = new TH1F("cumu2", "cumu", nbins, metMin, metMax);

  //generate the cumulative right tail sum hist
    for (Long64_t k = 0; k < nentries; k++)
    {
      tree->GetEntry(k);
      if (passrndm > 0.1)
      {
        algAMETHist->Fill(algAMET);
        algBMETHist->Fill(algBMET);
      }
    }

    std::cout << "numRndm: " << numRndm << std::endl;
    Float_t numKeepx1 = numRndm * x1;
    std::cout << "numKeepx1: " << numKeepx1 << std::endl;
    Float_t numKeepx2 = numRndm * initialGuess;
    std::cout << "numKeepx2: " << numKeepx2 << std::endl;
    Float_t numKeepx3 = numRndm * x3;
    std::cout << "numKeepx3: " << numKeepx3 << std::endl;

//Determine thresholds
    for (Int_t t = nbins; t >= 0; t--) //AX1 Thresh
    {
      Float_t summ1 = 0;

      for (Int_t i = t; i <= nbins; i++)
      {
        summ1 += algAMETHist->GetBinContent(i);
      }
      algAMETtarget->SetBinContent(t, summ1);
    }
    for (Int_t t = nbins; t >= 0; t--)
    {
      if ((abs(algAMETtarget->GetBinContent(t) - (numKeepx1) > 0) != (abs(algAMETtarget->GetBinContent(t + 1) - (numKeepx1)) > 0)))
      {
        algAMETx1thresh = algAMETtarget->GetBinCenter(t);
      }
    }
    for (Int_t t = nbins; t >= 0; t--) //BX1 Thresh
    {
      summ1 = 0;

      for (Int_t i = t; i <= nbins; i++)
      {
        summ1 += algBMETHist->GetBinContent(i);
      }
      algBMETtarget->SetBinContent(t, summ1);
    }
    for (Int_t t = nbins; t >= 0; t--)
    {
      if ((abs(algBMETtarget->GetBinContent(t) - (numKeepx1) > 0) != (abs(algBMETtarget->GetBinContent(t + 1) - (numKeepx1)) > 0)))
      {
        algBMETx1thresh = algBMETtarget->GetBinCenter(t);
      }
    }
    //=======================================================================================
    for (Int_t t = nbins; t >= 0; t--) //AX2 Thresh
    {
      if ((abs(algAMETtarget->GetBinContent(t) - (numKeepx2) > 0) != (abs(algAMETtarget->GetBinContent(t + 1) - (numKeepx2)) > 0)))
      {
        algAMETx2thresh = algAMETtarget->GetBinCenter(t);
      }
    }
    for (Int_t t = nbins; t >= 0; t--) //BX2 Thresh
    {
      if ((abs(algBMETtarget->GetBinContent(t) - (numKeepx2) > 0) != (abs(algBMETtarget->GetBinContent(t + 1) - (numKeepx2)) > 0)))
      {
        algBMETx2thresh = algBMETtarget->GetBinCenter(t);
      }
    }
    //======================================================================================
    for (Int_t t = nbins; t >= 0; t--) //AX3 Thresh
    {
      if ((abs(algAMETtarget->GetBinContent(t) - (numKeepx3) > 0) != (abs(algAMETtarget->GetBinContent(t + 1) - (numKeepx3)) > 0)))
      {
        algAMETx3thresh = algAMETtarget->GetBinCenter(t);
      }
    }
    for (Int_t t = nbins; t >= 0; t--) //BX3 Thresh
    {
      if ((abs(algBMETtarget->GetBinContent(t) - (numKeepx3) > 0) != (abs(algBMETtarget->GetBinContent(t + 1) - (numKeepx3)) > 0)))
      {
        algBMETx3thresh = algBMETtarget->GetBinCenter(t);
      }
    }
    //=============================================================================================
    for (Int_t i  = 0 ; i < nentries ;i++) //determine events kept at each threshold
    {
      tree->GetEntry(i);
      if ((passrndm > 0.1) && (algAMET > algAMETx1thresh) && (algBMET > algBMETx1thresh))
      {
        counter1++;
      }
      if ((passrndm > 0.1) && (algAMET > algAMETx2thresh) && (algBMET > algBMETx2thresh))
      {
        counter2++;
      }
      if ((passrndm > 0.1) && (algAMET > algAMETx3thresh) && (algBMET > algBMETx3thresh))
      {
        counter3++;
      }
    }

    std::cout << "At x1 = " << x1 << " Combined alg kept: " << counter1 << " events" << std::endl;
    f1 = (Float_t) counter1 / (Float_t) numRndm;
    std::cout << "f1: " << f1 << std::endl;

    std::cout << "At x2 = " << initialGuess << " Combined alg kept: " << counter2 << " events" << std::endl;
    f2 = (Float_t) counter2 / (Float_t) numRndm;
    std::cout << "f2: " << f2 << std::endl;

    std::cout << "At x3 = " << x3 << " Combined alg kept: " << counter3 << " events" << std::endl;
    f3 = (Float_t) counter3 / (Float_t) numRndm;
    std::cout << "f3: " << f3 << std::endl;

  for ( j = 1 ; j <= imax ; j++)
  {
    std::cout << "Current width of interval: " << currentWidth << std::endl;
    if (currentWidth < eps)
    {
      std::cout << "\nA root at x = " <<  initialGuess << " was found within epsilon "
           << "in " << j << " iterations" << std::endl;
      std::cout << "The number of combined events kept is  " << f2*numRndm << std::endl;
      std::cout << "The fraction of combined events kept is  " << f2 << std::endl;
      return(0);
    }
    std::cout << "Inside iteration number: " << j << std::endl;
    if ( (f1-CONDITION)*(f2-CONDITION) < 0 ) //root is in left half of interval
    {
      std::cout << "Root is to the left of " << initialGuess << std::endl;
      currentWidth = (initialGuess - x1) / 2.0;
      f3 = f2;
      x3 = initialGuess;
    }
    else //root is in right half of  interval
    {
      std::cout << "Root is to the right of " << initialGuess << std::endl;
      currentWidth = (x3 - initialGuess) / 2.0;
      f1 = f2;
      x1 = initialGuess;
    }

    std::cout << "Current width of interval: " << currentWidth << std::endl;

    if (currentWidth < eps)
    {
      std::cout << "\nA root at x = " <<  initialGuess << " was found within epsilon "
           << "in " << j << " iterations" << std::endl;
      std::cout << "The number of combined events kept is  " << f2*numRndm << std::endl;
      std::cout << "The fraction of combined events kept is  " << f2 << std::endl;
      return(0);
    }
    else
    {
      std::cout << "No root found, continuing bisection... " << std::endl;
      std::cout << "Fraction of combined events kept at individual frac, " << initialGuess << ": " << f2 << std::endl;
      initialGuess = ( x1 + x3 ) / 2.0;
      cout << "New Guess: " << initialGuess << endl;
      k = 0;

      numKeepx2 = numRndm * initialGuess;

        for (Int_t t = nbins; t >= 0; t--)
        {
          if ((abs(algAMETtarget->GetBinContent(t) - (numKeepx2) > 0) != (abs(algAMETtarget->GetBinContent(t + 1) - (numKeepx2)) > 0)))
          {
            algAMETx2thresh = algAMETtarget->GetBinCenter(t);
          }
        }

        for (Int_t t = nbins; t >= 0; t--)
        {
          if ((abs(algBMETtarget->GetBinContent(t) - (numKeepx2) > 0) != (abs(algBMETtarget->GetBinContent(t + 1) - (numKeepx2)) > 0)))
          {
            algBMETx2thresh = algBMETtarget->GetBinCenter(t);
          }
        }

        std::cout << "Alg A Thresh: " << algAMETx2thresh << std::endl;
        std::cout << "Alg B Thresh: " << algBMETx2thresh << std::endl;

        counter2 = 0;

        for (Int_t i  = 0 ; i < nentries ;i++)
        {
          tree->GetEntry(i);
          if ((passrndm > 0.1) && (algAMET > algAMETx2thresh) && (algBMET > algBMETx2thresh))
          {
            counter2++;
          }
        }

        std::cout << "Combined alg kept: " << counter2 << " events" << std::endl;
        f2 = (Float_t) counter2 / (Float_t) numRndm;
        std::cout << "f2: " << f2 << std::endl;

    }
    std::cout << "Fraction of combined events kept at " << initialGuess << ": " << f2 << std::endl;
  }

return(f2);
}
