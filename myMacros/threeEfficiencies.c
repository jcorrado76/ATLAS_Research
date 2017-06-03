Int_t threeEfficiencies(TString& algA , TString& algB)
{
  /*
  Makes TEFFICIENCY Plots ONCE
  TEFFICIENCY ALG A AT 10^(-4)
  TEFFICIENCY ALG b AT 10^(-4)
  TEFFICIENCY ALG c AT 10^(-4)
  */
TString fileName = "ExpressMuons2016newanalysis.11runs.root";
Float_t frac = (Float_t) 10.0**(-4.0);
TString path = "../myData/"+fileName;
TFile * muonFile = TFile::Open(path, "READ");
TTree* myMuonTree = NULL;
muonFile->GetObject("tree",myMuonTree);

std::cout << "Data being used to compute algorithm efficiency: " << path << std::endl;
Int_t nentries = myMuonTree->GetEntries();
Int_t muonNbins = 50;
Double_t muonMetMin = 0.0;
Double_t muonMetMax = 250.0;
Int_t passrndm, numPassMuon,passmuon,cleanCutsFlag,recalBrokeFlag;
Float_t algAMET,algBMET,metoffrecal,offrecal_met,offrecal_mex,offrecal_mey,offrecalmuon_mex,offrecalmuon_mey,acthresh,bcthresh;

myMuonTree->SetBranchAddress("passmu24med", &passmuon); // get first pass moun flag
myMuonTree->SetBranchAddress("passcleancuts", &cleanCutsFlag); // get cleancuts flag
myMuonTree->SetBranchAddress("recalbroke", &recalBrokeFlag); // get recalbroke flag
myMuonTree->SetBranchAddress("metoffrecal", &offrecal_met);
myMuonTree->SetBranchAddress("mexoffrecal", &offrecal_mex);
myMuonTree->SetBranchAddress("meyoffrecal", &offrecal_mey);
myMuonTree->SetBranchAddress("mexoffrecalmuon", &offrecalmuon_mex);
myMuonTree->SetBranchAddress("meyoffrecalmuon", &offrecalmuon_mey);


gROOT->ProcessLine(".L determineThresh.c");
TString argc;
argc = ".x determineThresh.c(\"" + algA + "\")";
Float_t algAThresh = (Float_t) gROOT->ProcessLine(argc);
argc = ".x determineThresh.c(\"" + algB + "\")";
Float_t algBThresh = (Float_t) gROOT->ProcessLine(argc);

/*
gSystem->CompileMacro("determineThresh.C");
TString argc;
argc = ".x determineThresh.c(\"" + algA + "\")";
Float_t algAThresh = (Float_t) gROOT->ProcessLine(argc);
argc = ".x determineThresh.c(\"" + algB + "\")";
Float_t algBThresh = (Float_t) gROOT->ProcessLine(argc);
*/



std::cout << "Returned to threeEfficiencies.c" << std::endl;
std::cout << "algAThresh: " << algAThresh << std::endl;
std::cout << "algBThresh: " << algBThresh << std::endl;
//===============================================================================================
std::cout << "Will return the combined frac to yield 2 thresholds for the algorithms to keep 10^(-4) zero bias events combined
such that they keep the same fraction individually" << std::endl;

//having troule opening this second file and using it

  TString myfileName = "../myData/ZeroBias2016new.13Runs.root";
  TFile * myData = TFile::Open(myfileName, "READ");
  TTree* myTree = NULL;
  myData->GetObject("tree",myTree);
  Int_t nentries = myTree->GetEntries();
  Int_t nbins = 400;

	Double_t metMin = 0.0;
	Double_t metMax = 250.0;

  myTree->SetBranchAddress("passrndm", &passrndm); // get pass rndm flag
  myTree->SetBranchAddress(algA,&algAMET);
  myTree->SetBranchAddress(algB,&algBMET);
  //passrndm keeps coming up as zero after I loop through all nentries
  Int_t numRndm = 0;
  Float_t algAMETx1thresh,algBMETx1thresh;
  Float_t algAMETx2thresh,algBMETx2thresh;
  Float_t algAMETx3thresh,algBMETx3thresh;
  Float_t CONDITION = 1.0*10**(-4.0);
  TString xlabel = "MET [GeV]";
  TString yaxis = "Events";
  Int_t counter1 = 0;
  Int_t counter2 = 0;
  Int_t counter3 = 0;

  TH1F *algAMETHist = new TH1F(algA, algA, nbins, metMin, metMax);
  TH1F *algBMETHist = new TH1F(algB, algB, nbins, metMin, metMax);
  TH1F *algAMETtarget = new TH1F("cumu1", "cumu", nbins, metMin, metMax);
  TH1F *algBMETtarget = new TH1F("cumu2", "cumu", nbins, metMin, metMax);

  Int_t numRndm =0 ;
  for (Long64_t k = 0; k < nentries; k++)
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

  Float_t numKeepx1 = numRndm * x1;
  Float_t numKeepx2 = numRndm * initialGuess;
  Float_t numKeepx3 = numRndm * x3;

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
    myTree->GetEntry(i);

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

  while ((counter2 - (numRndm*CONDITION)>eps) && (j <= imax))
  {
    if (counter2-(numRndm*CONDITION) < eps)
    {
      std::cout << "\nA root at x = " <<  initialGuess << " was found within epsilon "
           << "in " << j << " iterations" << std::endl;
      std::cout << "The number of combined events kept is  " << f2*numRndm << std::endl;
      std::cout << "The fraction of combined events kept is  " << f2 << std::endl;
      break;
    }
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

    if (counter2-(numRndm*CONDITION) < eps)
    {
      std::cout << "\nA root at x = " <<  initialGuess << " was found within epsilon "
           << "in " << j << " iterations" << std::endl;
      std::cout << "The number of combined events kept is  " << f2*numRndm << std::endl;
      std::cout << "The fraction of combined events kept is  " << f2 << std::endl;
      break;
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

      std::cout << algA << " Thresh: " << algAMETx2thresh << std::endl;
      std::cout << algB << " Thresh: " << algBMETx2thresh << std::endl;

      counter2 = 0;

      for (Int_t i  = 0 ; i < nentries ;i++)
      {
        myTree->GetEntry(i);
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


//===================================================================================================================
std::cout << "Threshold to keep 10^(-4) events for " << algA << ": " << algAThresh << std::endl;
std::cout << "Threshold to keep 10^(-4) events for " << algB << ": " << algBThresh << std::endl;

acthresh = algAMETx2thresh;
bcthresh = algBMETx2thresh;

TString cstring = "TEfficiency using " + algA + " at thresh " + Form(" %.2f", acthresh) + " and " + algB +
" at thresh " + Form(" %.2f", bcthresh);
TString astring = algA + " TEfficiency at thresh of " + Form(" %.2f", algAThresh);
TString bstring = algB + " TEfficiency at thresh of " + Form(" %.2f", algBThresh);

TEfficiency* Ateff  = new TEfficiency(astring , "Efficiency", muonNbins, muonMetMin, muonMetMax);
TEfficiency* Bteff  = new TEfficiency(bstring , "Efficiency", muonNbins, muonMetMin, muonMetMax);
TEfficiency* Cteff  = new TEfficiency(cstring,  "Efficiency", muonNbins, muonMetMin, muonMetMax);

//DRAW TEFFICIENCIES USING THE MUON DATA
myTree->SetBranchAddress(algA,&algAMET);
myTree->SetBranchAddress(algB,&algBMET);

for (Int_t j = 0 ; j < nentries ; j++)
{
    myMuonTree->GetEntry(j);
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

TString path = "./TEfficienciesPics/" + algA + "and" + algB + "efficiencies.pdf";

c1.Print(path);

return(0);



}
