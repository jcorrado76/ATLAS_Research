Int_t threeEfficiencies(TString& algA , TString& algB)
{
  /*
  Makes TEFFICIENCY Plots ONCE
  TEFFICIENCY ALG A AT 10^(-4)
  TEFFICIENCY ALG b AT 10^(-4)
  TEFFICIENCY ALG c AT 10^(-4)
  */

gROOT->ProcessLine("gROOT->Reset();");
TString muonFilename = "ExpressMuons2016newanalysis.11runs.root";
TString myFileName = "ZeroBias2016new.13Runs.root";
Float_t frac = (Float_t) 1e-4;
TString path = "../myData/"+muonFilename;
TFile * muonFile = TFile::Open(path, "READ");
TTree* myMuonTree = NULL;
muonFile->GetObject("tree",myMuonTree);

std::cout << "Data being used to compute algorithm efficiency: " << path << std::endl;
Int_t muonNentries = myMuonTree->GetEntries();
Int_t muonNbins = 50;
Int_t nbins = 400;
Double_t muonMetMin = 0.0;
Double_t muonMetMax = 250.0;
Int_t passrndm, numPassMuon,passmuon,cleanCutsFlag,recalBrokeFlag;
Float_t algAMET,algBMET,metoffrecal,offrecal_met,offrecal_mex,offrecal_mey,offrecalmuon_mex,offrecalmuon_mey,acthresh,bcthresh;

myMuonTree->SetBranchAddress("passmu24med", &passmuon);
myMuonTree->SetBranchAddress("passcleancuts", &cleanCutsFlag);
myMuonTree->SetBranchAddress("recalbroke", &recalBrokeFlag);
myMuonTree->SetBranchAddress("metoffrecal", &offrecal_met);
myMuonTree->SetBranchAddress("mexoffrecal", &offrecal_mex);
myMuonTree->SetBranchAddress("meyoffrecal", &offrecal_mey);
myMuonTree->SetBranchAddress("mexoffrecalmuon", &offrecalmuon_mex);
myMuonTree->SetBranchAddress("meyoffrecalmuon", &offrecalmuon_mey);

std::cout << "MuonNentries: " << muonNentries << std::endl;

  TString path = "../myData/"+ myFileName;
  TFile * myData = TFile::Open(path, "READ");
  TTree* myTree = NULL;
  myData->GetObject("tree",myTree);
  Int_t nentries = myTree->GetEntries();

  Int_t numRndm = 0;
  Int_t counter1 = 0;
  Int_t counter2 = 0;
  Int_t counter3 = 0;
	Double_t metMin = 0.0;
	Double_t metMax = 250.0;

  Float_t algAMETx1thresh,algBMETx1thresh;
  Float_t algAMETx2thresh,algBMETx2thresh;
  Float_t algAMETx3thresh,algBMETx3thresh;
  Float_t CONDITION = 1.0*10**(-4.0);
  TString xlabel = "MET [GeV]";
  TString yaxis = "Events";
  myTree->SetBranchAddress("passrndm", &passrndm); // get pass rndm flag
  myTree->SetBranchAddress(algA,&algAMET);
  myTree->SetBranchAddress(algB,&algBMET);
  TH1F *algAMETHist = new TH1F(algA, algA, nbins, metMin, metMax);
  TH1F *algBMETHist = new TH1F(algB, algB, nbins, metMin, metMax);
  TH1F *algAMETtarget = new TH1F("cumu1", "cumu", nbins, metMin, metMax);
  TH1F *algBMETtarget = new TH1F("cumu2", "cumu", nbins, metMin, metMax);

  gROOT->ProcessLine(".L determineThresh.c");
  TString argc;
  argc = ".x determineThresh.c(\"" + algA + "\"," + Form("%.7f",CONDITION) + ",\"" + myFileName + "\")";
  Float_t algAThresh = (Float_t) gROOT->ProcessLine(argc);
  argc = ".x determineThresh.c(\"" + algB + "\"," + Form("%.7f",CONDITION) + ",\"" + myFileName + "\")";
  Float_t algBThresh = (Float_t) gROOT->ProcessLine(argc);

  std::cout << "Returned to threeEfficiencies.c" << std::endl;
  std::cout << "algAThresh: " << algAThresh << std::endl;
  std::cout << "algBThresh: " << algBThresh << std::endl;

  Int_t numRndm =0 ;
  for (Int_t k = 0; k < nentries; k++) //determine numRndm and fill histograms
  {
    myTree->GetEntry(k);
    if (passrndm > 0.1)
    {
      numRndm++;
      algAMETHist->Fill(algAMET);
      algBMETHist->Fill(algBMET);
    }
  }

  std::cout << "numRndm " << numRndm << std::endl;
  std::cout << "CONDITION " << CONDITION << std::endl;
  std::cout << "numCombined to keep: " << numRndm * CONDITION << std::endl;
  Float_t lwrbnd = CONDITION;
  Float_t uprbnd = 0.005;
  Float_t eps = 25.0;

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
  Float_t firstGuess = initialGuess;
  Float_t numKeepx1 = numRndm * x1;
  Float_t numKeepx2 = numRndm * initialGuess;
  Float_t numKeepx3 = numRndm * x3;

  computeTarget(algAMETHist,algAMETtarget,nbins);
  computeTarget(algBMETHist,algBMETtarget,nbins);

  algAMETx1thresh = computeThresh(algAMETtarget, numKeepx1, nbins);
  algBMETx1thresh = computeThresh(algBMETtarget, numKeepx1, nbins);
  algAMETx2thresh = computeThresh(algAMETtarget, numKeepx2, nbins);
  algBMETx2thresh = computeThresh(algBMETtarget, numKeepx2, nbins);
  algAMETx3thresh = computeThresh(algAMETtarget, numKeepx3, nbins);
  algBMETx3thresh = computeThresh(algBMETtarget, numKeepx3, nbins);

  for (Int_t i  = 0 ; i < nentries ;i++) //determine events kept at each guess
  {
    myTree->GetEntry(i);
    if (passrndm > 0.5)
    {
      if ((algAMET > algAMETx1thresh) && (algBMET > algBMETx1thresh))
      {
        counter1++;
      }
      if ((algAMET > algAMETx2thresh) && (algBMET > algBMETx2thresh))
      {
        counter2++;
      }
      if ((algAMET > algAMETx3thresh) && (algBMET > algBMETx3thresh))
      {
        counter3++;
      }
    }
  }

  std::cout << "At x1 = " << x1 << " counter1: " << counter1 << " events" << std::endl;
  f1 = (Float_t) counter1 / (Float_t) numRndm;
  std::cout << "f1: " << f1 << std::endl;

  std::cout << "At x2 = " << initialGuess << " counter2: " << counter2 << " events" << std::endl;
  f2 = (Float_t) counter2 / (Float_t) numRndm;
  std::cout << "f2: " << f2 << std::endl;

Float_t firstOutput = f2;
Float_t initialNumbEvents = counter2;

  std::cout << "At x3 = " << x3 << " counter3: " << counter3 << " events" << std::endl;
  f3 = (Float_t) counter3 / (Float_t) numRndm;
  std::cout << "f3: " << f3 << std::endl;

  Float_t inputArray[100];
  Float_t outputArray[100];
  Float_t numEventsArray[100];
  Float_t thresholdAarray[100];
  Float_t thresholdBarray[100];
inputArray[0] = x1;
inputArray[1] = initialGuess;
inputArray[2] = x3;
outputArray[0] = f1;
outputArray[1] = f2;
outputArray[2] = f3;
numEventsArray[0] = counter1;
numEventsArray[1] = counter2;
numEventsArray[2] = counter3;
thresholdAarray[0] = algAMETx1thresh;
thresholdAarray[1] = algAMETx2thresh;
thresholdAarray[2] = algAMETx3thresh;
thresholdBarray[0] = algBMETx1thresh;
thresholdBarray[1] = algBMETx2thresh;
thresholdBarray[2] = algBMETx3thresh;

  while ( (abs( numRndm * CONDITION - counter2) > eps)  && ( j <= imax ) )
  {
    j++;
    std::cout << "Inside iteration number: " << j << std::endl;
    if ( (f1-CONDITION)*(f2-CONDITION) < 0 ) //root is in left half of interval
    {
      std::cout << "Root is to the left of " << initialGuess << std::endl;
      f3 = f2;
      x3 = initialGuess;
    }
    else //root is in right half of  interval
    {
      std::cout << "Root is to the right of " << initialGuess << std::endl;
      f1 = f2;
      x1 = initialGuess;
    }
    initialGuess = ( x1 + x3 ) / 2.0;
    inputArray[j+2] = initialGuess;
    std::cout << "New Guess: " << initialGuess << std::endl;
    numKeepx2 = numRndm * initialGuess;
    algAMETx2thresh = computeThresh(algAMETtarget, numKeepx2, nbins);
    algBMETx2thresh = computeThresh(algBMETtarget, numKeepx2, nbins);
    thresholdAarray[j+2] = algAMETx2thresh;
    thresholdBarray[j+2] = algBMETx2thresh;

    counter2 = 0;
    for (Int_t i  = 0 ; i < nentries ;i++)
    {
      myTree->GetEntry(i);
      if ((passrndm > 0.1) && (algAMET > algAMETx2thresh) && (algBMET > algBMETx2thresh))
      {
        counter2++;
      }
    }
    std::cout << algA << " Thresh: " << algAMETx2thresh << std::endl;
    std::cout << algB << " Thresh: " << algBMETx2thresh << std::endl;
    std::cout << "Counter2: " << counter2 << std::endl;
    f2 = (Float_t) counter2 / (Float_t) numRndm;
    std::cout << "f2: " << f2 << std::endl;
    std::cout << "Condition: " << abs(numRndm * CONDITION - counter2) << " > " << eps << std::endl;
    outputArray[j+2] = f2;
  }
  if (abs(counter2-(numRndm*CONDITION)) < eps)
  {
    std::cout << "\nA root at x = " <<  initialGuess << " was found to within " + eps + " events"
              << "in " << j << " iterations" << std::endl;
    std::cout << "The number of combined events kept is  " << f2 * numRndm << std::endl;
    std::cout << "The fraction of combined events kept is  " << f2 << std::endl;
  }
  else{
    std::cout << "No root found; max iterations exceeded" << std::endl;
  }

acthresh = algAMETx2thresh;
bcthresh = algBMETx2thresh;

TString cstring = "TEfficiency using " + algA + " at thresh " + Form(" %.2f", acthresh) + " and " + algB +
" at thresh " + Form(" %.2f", bcthresh);
TString astring = algA + " TEfficiency at thresh of " + Form(" %.2f", algAThresh);
TString bstring = algB + " TEfficiency at thresh of " + Form(" %.2f", algBThresh);

TEfficiency* Ateff  = new TEfficiency(astring , "Efficiency", muonNbins, muonMetMin, muonMetMax);
TEfficiency* Bteff  = new TEfficiency(bstring , "Efficiency", muonNbins, muonMetMin, muonMetMax);
TEfficiency* Cteff  = new TEfficiency(cstring,  "Efficiency", muonNbins, muonMetMin, muonMetMax);

myMuonTree->SetBranchAddress(algA,&algAMET);
myMuonTree->SetBranchAddress(algB,&algBMET);
for (Int_t l = 0 ; l < nentries ; l++)
{
    myMuonTree->GetEntry(l);
    //CLEANCUTS AND RECALBROKE
    if (passmuon > 0.1 && cleanCutsFlag > 0.1 && recalBrokeFlag < 0.1)
    {
        Float_t metnomu = sqrt(((offrecal_mex - offrecalmuon_mex) * (offrecal_mex - offrecalmuon_mex)) +
        ((offrecal_mey - offrecalmuon_mey)*(offrecal_mey - offrecalmuon_mey))); //compute metnomu
        Ateff->Fill(algAMET > algAThresh, metnomu);
        Bteff->Fill(algBMET > algBThresh, metnomu);
        Cteff->Fill(((algAMET > acthresh) && (algBMET > bcthresh) ), metnomu);
    }
}

std::cout << "Running an external check macro to verify number of events kept at fraction
determined by the bisection algorithm..." << std::endl;
std::cout << "ENTERING determineCombinedEventsKept.c" <<std::endl;
gROOT->ProcessLine(".L determineCombinedEventsKept.c");
TString argc;
argc = ".x determineCombinedEventsKept.c(\"" + algA + "\","+Form("%.7f",acthresh)+",\""+algB+"\","+Form("%.7f",bcthresh)+",\""
        +myFileName+ "\")";
Float_t eventsCombined = (Float_t) gROOT->ProcessLine(argc);

TCanvas* c1 = new TCanvas("Efficiency Canvas", "Efficiency Canvas");
Ateff->Draw();
Ateff->SetLineColor(kBlue);
Bteff->Draw("same");
Bteff->SetLineColor(kGreen);
Cteff->Draw("same");
Cteff->SetLineColor(kRed);
TLegend *legend = new TLegend(.1,.7,.48,.9);
legend->AddEntry(Ateff, astring);
legend->AddEntry(Bteff, bstring);
legend->AddEntry(Cteff, cstring);
legend->Draw();
TString path = "./TEfficienciesPics/_" + algA + "_and_" + algB + "_efficiencies.pdf";
c1.Print(path);

logfileName = "./TEfficienciesPics/_" + algA + "_and_" + algB + "_efficiencies.txt"

ofstream logFile;
logFile.open(logfileName);
logFile << "Algorithms: " << algA << "\t" << algB  << std::endl;;
logFile << "ZEROBIAS DATAFILE: " << myFileName << std::endl;
logFile << "Zerboias Nentries: " << nentries << std::endl;
logFile << "MUON DATAFILE: " << muonFilename << std::endl;
logFile << "Muon nentries: " << muonNentries << std::endl;
logFIle << "Nbins: " << nbins << "\t METMIN: " << metMin << "\t METMAX: " << metMax << std::endl;
logFile << "Fraction to keep for bisection: " << frac << std::endl;
logFile << "Threshold for " + algA + " to keep fraction by itself: " << algAThresh << std::endl;
logFile << "Threshold for " + algB + " to keep fraction by itself: " << algBThresh << std::endl;
logFile << "Epsilon tolerance for bisection accuracy: " << eps << std::endl;
logFile << "Bisection Information: " << std::endl;
logFile << "Iteration: " << "Individual Fraction: \t" << "Output Combined Fraction Kept \t" << "Number Events Kept \t" <<
<< "Threshold for " + algA + '\t' << "Threshold for " + algB +'\t' << std::endl;
logFile << "x1" << x1 << f1 << counter1 << std::endl;
logFile << "x3" << x3 << f3 << counter3 << std::endl;
logFile << "x2" << firstGuess << firstOutput << initialNumbEvents << std::endl;
for (int m = 1; m < j+3 ; m++)
{
  logFile << Form("I%d",m) << inputArray[m+2] << outputArray[m+2] << numEventsArray[m+2] <<
  <<thresholdAarray[m+2] << thresholdBarray[m+2] << std::endl;
}

logFile << "Number of combined events determined by verification macro 'determineCombinedEventsKept.c': " << eventsCombined << std::endl;

logFile.close();





return(0);
}

//HELPER FUNCTIONS
TH1F* computeTarget(TH1F* hist , TH1F* target, Int_t nbins)
{
	for (Int_t t = nbins; t >= 0; t--)
	{
		Float_t rightHandSum = hist->Integral(t,nbins); //compute t'th target bin
		target->SetBinContent(t, rightHandSum);
	}
	return(target);
}

Float_t computeThresh(TH1F* target, Float_t numKeep, Int_t nbins)
{
	Float_t thresh;
	for (Int_t t = nbins; t >= 0; t--)
	{
		if ((abs(target->GetBinContent(t) - (numKeep) > 0) != (abs(target->GetBinContent(t + 1) - (numKeep)) > 0)))
		{
			thresh = target->GetBinCenter(t);
		}
	}
	return(thresh);
}
