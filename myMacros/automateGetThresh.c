Int_t automateGetThresh(TString& algA = "metcell", TString& algB = "metmht" , Float_t frac = 0.003105)
{
  /*
  Given a fraction of algAMET to keep individually, determines the fraction of algBMET in order to keep 10^(-4)
  This will generate a single point on the PPF for 10^(-4)
  */


  //fraction so algAMET and algBMET together keep 1-^-4
  TString fileName = "../myData/ZeroBias2016new.13Runs.root";
  TFile * 2016Data = TFile::Open(fileName, "READ");
  Int_t nentries = tree->GetEntries();
  Int_t nbins = 60;
	Double_t metMin = 0.0;
	Double_t metMax = 500.0;
  Int_t passrndm, numRndm = 0;
  Float_t algAMET,algBMET;
  std::cout << "Number of entries in the tree: " << nentries << std::endl;
  Float_t CONDITION = 10.0**(-4.0);
  tree->SetBranchAddress(algA,&algAMET);
  tree->SetBranchAddress(algB,&algBMET);
  tree->SetBranchAddress("passrndm",&passrndm);

  TH1F* combinedAlgHist = new TH1F("Combined Hist" , "Combined Hist"  , nbins, metMin, metMax);
  TH1F* algAHist = new TH1F("algAMET", "algAMET", nbins, metMin, metMax);
  TH1F* algBHist = new TH1F("algBMET", "algBMET", nbins, metMin, metMax);
  TH1F *algAtarget = new TH1F("cumu2", "cumu", nbins, metMin, metMax); //used to generate cumulative right tail sums
  TH1F *algBtarget = new TH1F("cumu3", "cumu", nbins, metMin, metMax); //used to generate cumulative right tail sums

  //fill with passrndm
  for (Int_t i = 0 ; i < nentries ; i++)
  {
    tree->GetEntry(i);
    if (passrndm > 0.1)
    {
      numRndm++;
      algAHist->Fill(algAMET);
			algBHist->Fill(algBMET);
    }
  }
  Float_t combinedNumbToKeep = CONDITION * numRndm;
  std::cout << "Number of events that passed rndm: " << numRndm << std::endl;
  std::cout << "10^(-4) times the  number of events that pased rndm: " << combinedNumbToKeep << std::endl;
  Float_t numbAToKeep = (Float_t) numRndm * frac; // determine how many events the specified fraction for A corresponds to
  Float_t numbBToKeep = (CONDITION * numRndm) - numbAToKeep; //determine how many events are left for B
  std::cout << "Target number of events for A to keep individually: " << numbAToKeep << std::endl;
  //=============================================================================
  //determine threshold to keep 10^(-4) events for just algorithm A
  for (int t = nbins; t >= 0; t--)
  {
    Float_t summ2 = 0;

    for (int i = t; i <= nbins; i++)
    {
      summ2 += algAHist->GetBinContent(i);
    }
    algAtarget->SetBinContent(t, summ2);
  }
  for (int t = nbins; t >= 0; t--)
  {
    if ((abs(algAtarget->GetBinContent(t) - (numbAToKeep) > 0) != (abs(algAtarget->GetBinContent(t + 1) - (numbAToKeep)) > 0)))
    {
      Float_t algAthresh = algAtarget->GetBinCenter(t);
    }
  }
  std::cout << "Threshold for " + algA + ": " << algAthresh << std::endl;

  //=================================================================================
  Float_t lwrbnd = 0.0;
  Float_t uprbnd = 150.0;
  Float_t eps = 25.0;
  //guess a value of B thresh, then run bisection until converge on thresh such that at fixed thresh of A,
  //using together keeps total 10^(-4)

  std::cout << "Entering bisection" << std::endl;

  Int_t j = 0 ;
  Int_t imax = 30;
  Float_t x1,x2,x3;
  Float_t f1,f2,f3 = 0;
  Float_t currentWidth;
  x1 = lwrbnd;
  x3 = uprbnd;
  x2 = ( x1 + x3 ) / 2.0;

//determine how many events kept using the determined thresholds
std::cout << "Determining the number of events kept at the endpoints of the interval and at midpoint..." << std::endl;

  for (Int_t k = 0 ; k < nentries; k++)
  {
    tree->GetEntry(k);
    //determine # events kept  at lwrbnd on thresh
    if ((passrndm > 0.1) && (algBMET > x1) && (algAMET > algAthresh))
    {
      f1++;
    }
    //determine # events kept at midpoint of threshes
    if ((passrndm > 0.1) && (algBMET > x2) && (algAMET > algAthresh))
    {
      f2++;
    }
    //determine # events kept at uprbnd on thresh
    if ((passrndm > 0.1) && (algBMET > x3) && (algAMET > algAthresh))
    {
      f3++;
    }
  }

std::cout << "Number of events kept with B thresh at " << x1 << ": " << f1 << std::endl;
std::cout << "Number of events kept with B thresh at " << x2 << ": " << f2 << std::endl;
std::cout << "Number of events kept with B thresh at " << x3 << ": " << f3 << std::endl;

for ( j = 1 ; j <= imax ; j++)
{
  std::cout << "Inside iteration number: " << j << std::endl;
  if ( (f1-combinedNumbToKeep)*(f2-combinedNumbToKeep) < 0 ) //root is in left half of interval
  {
    currentWidth = (x2 - x1) / 2.0;
    f3 = f2;
    x3 = x2;
  }

  else //root is in right half of  interval
  {
    currentWidth = (x3 - x2) / 2.0;
    f1 = f2;
    x1 = x2;
  }

  if (currentWidth < eps)
  {
    cout << "\nA root at x = " <<  x2 << " was found within epsilon "
         << "in " << j << " iterations" << endl;
    cout << "The number of combined events kept is  " << f2 << endl;

    return(0);
  }

std::cout << "Number of events kept at B threshold of " << x2 << ": " << f2 << std::endl;
x2 = ( x1 + x3 ) / 2.0;
k = 0;
f2 = 0;

  for (k = 0 ; k < nentries; k++)
  {
    if ((passrndm > 0.1) && (algBMET > x2) && (algAMET > algAthresh))
    {
      f2++;
    }
  }
}


return(0);
}
