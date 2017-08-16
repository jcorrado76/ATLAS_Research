#include "TMath.h"
#include "TH1.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TEfficiency.h"
#include "TLegend.h"
#include <iostream>
#include <fstream>
#include "TROOT.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TF1.h"

namespace myConstants
{
    Int_t nbins = 1200;
    Int_t muonNbins = 200;
    Float_t metMin = 0;
    Float_t metMax = 300;
    Float_t muonMetMin = metMin;
    Float_t muonMetMax = 300;
    Float_t metl1thresh = 50.0;

}



Int_t threeEfficiencies( const TString& algA , const TString& algB,
        const Float_t frac = 0.00590, const TString folder = "",
        const TString& zerobiasFileName = "PhysicsMain.All.noalgXEtriggers.2016.f731f758._m1659m1710.48Runs.root",
        const TString& muonFilename = "PhysicsMain2016.Muons.noalgL1XE45R3073065R311481Runs9B.root")
{

    Float_t determineZeroBiasThresh( const TString&, const Float_t, const TString&);
    Float_t computeThresh(TH1F*,Float_t);
    Float_t determineMuonEventsKeptCombined( const TString&, const Float_t, const TString&,
        const Float_t,const TString& );

    gROOT->ProcessLine("gROOT->Time();");

    TString muonFilePath = "../myData/"+muonFilename;
    TFile * muonFile = TFile::Open(muonFilePath, "READ");
    TTree* myMuonTree = (TTree*)muonFile->Get("tree");
    std::cout << "Muon Data being used to compute algorithm efficiency: " << muonFilePath << std::endl;
    Int_t muonNentries = myMuonTree->GetEntries();
    Int_t muonNbins = myConstants::muonNbins;
    Int_t nbins = myConstants::nbins;
    Double_t muonMetMin = myConstants::muonMetMin;
    Double_t muonMetMax = myConstants::muonMetMax;
    Int_t numZeroBiasRndm = 0; Int_t counter1 = 0; Int_t counter2 = 0; Int_t counter3 = 0;

    Double_t metMin = myConstants::metMin; Double_t metMax = myConstants::metMax;

    Int_t passRndm, numPassMuon,passmuon,passmuvarmed,cleanCutsFlag,recalBrokeFlag;
    Float_t algAMET,algBMET,offrecal_met,offrecal_mex,offrecal_mey,offrecalmuon_mex,
            offrecalmuon_mey, acthresh,bcthresh,metl1,metcell,metrefmuon,mexrefmuon,meyrefmuon;
    Int_t passnoalgL1XE10,passnoalgL1XE30,passnoalgL1XE40,passnoalgL1XE45;

    myMuonTree->SetBranchAddress("passmu26med", &passmuon);
    myMuonTree->SetBranchAddress("passmu26varmed", &passmuvarmed);
    myMuonTree->SetBranchAddress("passcleancuts", &cleanCutsFlag);
    myMuonTree->SetBranchAddress("recalbroke", &recalBrokeFlag);
    myMuonTree->SetBranchAddress("metoffrecal", &offrecal_met);
    myMuonTree->SetBranchAddress("mexoffrecal", &offrecal_mex);
    myMuonTree->SetBranchAddress("meyoffrecal", &offrecal_mey);
    myMuonTree->SetBranchAddress("mexoffrecalmuon", &offrecalmuon_mex);
    myMuonTree->SetBranchAddress("meyoffrecalmuon", &offrecalmuon_mey);
    myMuonTree->SetBranchAddress("metrefmuon", &metrefmuon);
    myMuonTree->SetBranchAddress("mexrefmuon", &mexrefmuon);
    myMuonTree->SetBranchAddress("meyrefmuon", &meyrefmuon);


    std::cout << "MuonNentries: " << muonNentries << "\n" << std::endl;

    TString zerobiasFilePath = "../myData/"+ zerobiasFileName;
    TFile * zeroBiasFile = TFile::Open(zerobiasFilePath, "READ");
    TTree* zeroBiasTree = (TTree*)zeroBiasFile->Get("tree");
    Int_t zerobiasNentries = zeroBiasTree->GetEntries();


    Float_t algAMETx1thresh,algBMETx1thresh;
    Float_t algAMETx2thresh,algBMETx2thresh;
    Float_t algAMETx3thresh,algBMETx3thresh;
    TString xlabel = "MET [GeV]";
    TString yaxis = "Events";
    zeroBiasTree->SetBranchAddress("passrndm", &passRndm); // get pass rndm flag
    zeroBiasTree->SetBranchAddress(algA,&algAMET);
    zeroBiasTree->SetBranchAddress(algB,&algBMET);
    zeroBiasTree->SetBranchAddress("metl1",&metl1);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE10",&passnoalgL1XE10);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE30",&passnoalgL1XE30);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE40",&passnoalgL1XE40);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE45",&passnoalgL1XE45);
    TH1F *algAMETHist = new TH1F("algA", "algA", nbins, metMin, metMax);
    TH1F *algBMETHist = new TH1F("algB", "algB", nbins, metMin, metMax);


//IN DETERMINE THRESH I COMPUTE THRESHOLD AFTER ALSO CUTTING ON METL1 TO MAKE HISTOGRAMS
    Float_t algAThresh = determineZeroBiasThresh(algA,frac,zerobiasFileName);
    Float_t algBThresh = determineZeroBiasThresh(algB,frac,zerobiasFileName);

//FINISHED COMPUTING INDIVIDUAL THRESHOLDS; NOW DO THEM TOGETHER
    std::cout << "Returned to threeEfficiencies.C" << std::endl;
    std::cout << "algAThresh: " << algAThresh << std::endl;
    std::cout << "algBThresh: " << algBThresh << std::endl;
    std::cout << "Using METL1THRESH: " << myConstants::metl1thresh << std::endl;

    numZeroBiasRndm = 0 ;
    std::cout << "algA==algB? " << (algA==algB) << std::endl;
    if (algA == algB)
    {
    	for (Int_t k = 0; k < zerobiasNentries; k++)
    	{
    	    zeroBiasTree->GetEntry(k);
    	    if (metl1 > 50.0 && ( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 ||
            passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5  ) )
    	    {
        		algAMET = algBMET;
        		algAMETHist->Fill(algAMET);
        		algBMETHist->Fill(algBMET);
                numZeroBiasRndm++;
    	    }
    	}
    }
    else
    {
    	for (Int_t k = 0; k < zerobiasNentries; k++) //determine numZeroBiasRndm and fill histograms
    	{
    	    zeroBiasTree->GetEntry(k);
    	    if (metl1 > 50.0 && ( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 ||
            passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5  ))
    	    {
        		algAMETHist->Fill(algAMET);
        		algBMETHist->Fill(algBMET);
                numZeroBiasRndm++;
    	    }
    	}
    }
    std::cout << "numZeroBiasRndm: " << numZeroBiasRndm << std::endl;
    std::cout << "frac " << frac << std::endl;
    std::cout << "numCombined to keep: " << numZeroBiasRndm * frac << std::endl;
    Float_t lwrbnd = 0.5*frac;
    Float_t uprbnd = 0.13;
    Float_t eps = 25.0;

    std::cout << "Entering bisection to determine individual fractions" << std::endl;
    std::cout << "Lower Bound: " << lwrbnd << std::endl;
    std::cout << "Midpoint: " << (lwrbnd+uprbnd)/2. << std::endl;
    std::cout << "Upper Bound: " << uprbnd << std::endl;
    std::cout << "Epsilon: " << eps << std::endl;
    Float_t x1,x3; //thresholds of individual algorithms
    Float_t f1,f2,f3 = 0; //number of events kept
    x1 = lwrbnd;
    x3 = uprbnd;
    Float_t initialGuess = ( x1 + x3 ) / 2.0;
    Float_t firstGuess = initialGuess;
    Float_t numKeepx1 = numZeroBiasRndm * x1;
    Float_t numKeepx2 = numZeroBiasRndm * initialGuess;
    Float_t numKeepx3 = numZeroBiasRndm * x3;

    TH1F *algAMETtarget = (TH1F*) algAMETHist->GetCumulative(kFALSE);
    TH1F *algBMETtarget = (TH1F*) algBMETHist->GetCumulative(kFALSE);
    algAMETtarget->SetName(algAMETtarget->GetName() + (const TString)"A");
    algBMETtarget->SetName(algBMETtarget->GetName() + (const TString)"B");

    algAMETx1thresh = computeThresh(algAMETtarget, numKeepx1);
    algBMETx1thresh = computeThresh(algBMETtarget, numKeepx1);
    algAMETx2thresh = computeThresh(algAMETtarget, numKeepx2);
    algBMETx2thresh = computeThresh(algBMETtarget, numKeepx2);
    algAMETx3thresh = computeThresh(algAMETtarget, numKeepx3);
    algBMETx3thresh = computeThresh(algBMETtarget, numKeepx3);

    std::cout << "algAx1Thresh: " << algAMETx1thresh << std::endl;
    std::cout << "algBx1Thresh: " << algBMETx1thresh << std::endl;
    std::cout << "metl1thresh : " << myConstants::metl1thresh << std::endl;
    if (algA==algB)
    {
        for (Int_t i  = 0 ; i < zerobiasNentries ;i++) //determine events kept at each guess
        {
            zeroBiasTree->GetEntry(i);
            //if (passRndm > 0.5)
            //{
                algAMET = algBMET;
                if ((algBMET > algBMETx1thresh) && ( metl1 > myConstants::metl1thresh ) && ( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 ||
                passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5  ))
                {
                    counter1++;
                }
                if ((algBMET > algBMETx2thresh) && (metl1 > myConstants::metl1thresh)&& ( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 ||
                passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5  ))
                {
                    counter2++;
                }
                if ((algBMET > algBMETx3thresh) && (metl1 > myConstants::metl1thresh)&& ( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 ||
                passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5  ))
                {
                    counter3++;
                }
            //}
        }
    }
    else
    {
        for (Int_t i  = 0 ; i < zerobiasNentries ;i++) //determine events kept at each guess
        {
        zeroBiasTree->GetEntry(i);
            //if (passRndm > 0.5)
            //{
                if ((algAMET > algAMETx1thresh) && (algBMET > algBMETx1thresh) && (metl1 > myConstants::metl1thresh)&& ( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 ||
                passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5  ) )
                {
                counter1++;
                }
                if ((algAMET > algAMETx2thresh) && (algBMET > algBMETx2thresh) && (metl1 > myConstants::metl1thresh)&& ( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 ||
                passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5  ))
                {
                counter2++;
                }
                if ((algAMET > algAMETx3thresh) && (algBMET > algBMETx3thresh) && (metl1 > myConstants::metl1thresh)&& ( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 ||
                passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5  ) )
                {
                counter3++;
                }
            //}
        }
    }

    std::cout << "At x1 = " << x1 << " counter1: " << counter1 << " events" << std::endl;
    f1 = (Float_t) counter1 / (Float_t) numZeroBiasRndm;
    std::cout << "f1: " << f1 << std::endl;

    std::cout << "At x2 = " << initialGuess << " counter2: " << counter2 << " events" << std::endl;
    f2 = (Float_t) counter2 / (Float_t) numZeroBiasRndm;
    std::cout << "f2: " << f2 << std::endl;

    std::cout << "At x3 = " << x3 << " counter3: " << counter3 << " events" << std::endl;
    f3 = (Float_t) counter3 / (Float_t) numZeroBiasRndm;
    std::cout << "f3: " << f3 << std::endl;

    Float_t inputArray[100];
    Float_t outputArray[100];
    Float_t numEventsArray[100];
    Float_t thresholdAarray[100];
    Float_t thresholdBarray[100];

    inputArray[0] = x1;
    inputArray[2] = initialGuess;
    inputArray[1] = x3;
    outputArray[0] = f1;
    outputArray[2] = f2;
    outputArray[1] = f3;
    numEventsArray[0] = counter1;
    numEventsArray[2] = counter2;
    numEventsArray[1] = counter3;
    thresholdAarray[0] = (Float_t) algAMETx1thresh;
    thresholdAarray[2] = (Float_t) algAMETx2thresh;
    thresholdAarray[1] = (Float_t) algAMETx3thresh;
    thresholdBarray[0] = (Float_t) algBMETx1thresh;
    thresholdBarray[2] = (Float_t) algBMETx2thresh;
    thresholdBarray[1] = (Float_t) algBMETx3thresh;

    Int_t j = 0 ;
    Int_t imax = 30;
    Float_t binWidth = (metMax - metMin)/ nbins;
    Float_t algAThreshDiff;
    Float_t algBThreshDiff;

//TODO: make a TBenchmark here for "bisection"

do{
    j++;
    std::cout << "Inside iteration number: " << j << std::endl;
    if ( (f1-frac)*(f2-frac) < 0 ) //root is in left half of interval
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
    std::cout << "numZeroBiasRndm: " << numZeroBiasRndm << std::endl;
    numKeepx2 = numZeroBiasRndm * initialGuess;
    std::cout << "numKeepx2: " << numKeepx2 << std::endl;
    algAMETx2thresh = computeThresh(algAMETtarget, numKeepx2);
    algBMETx2thresh = computeThresh(algBMETtarget, numKeepx2);
    thresholdAarray[j+2] = (Float_t) algAMETx2thresh;
    thresholdBarray[j+2] = (Float_t) algBMETx2thresh;

    counter2 = 0;
    if (algA==algB)
    {
	for (Int_t i  = 0 ; i < zerobiasNentries ;i++)
	{
	  zeroBiasTree->GetEntry(i);
	  algAMET=algBMET;
	  if ((algBMET > algBMETx2thresh) && (metl1 > myConstants::metl1thresh)&& ( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 ||
          passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5  ))
    	  {
    	    counter2++;
    	  }
	}
    }
    else
    {
	for (Int_t i  = 0 ; i < zerobiasNentries ;i++)
	{
	  zeroBiasTree->GetEntry(i);
	  if ((algAMET > algAMETx2thresh) && (algBMET > algBMETx2thresh) && (metl1 > myConstants::metl1thresh)&& ( passnoalgL1XE10 > 0.5 ||
          passnoalgL1XE30 > 0.5 || passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5  ) )
	  {
	    counter2++;
	  }
	}
    }
    numEventsArray[j+2] = counter2;
    std::cout << "algAMETx2thresh: " << algAMETx2thresh << std::endl;
    std::cout << "algBMETx2thresh: " << algBMETx2thresh << std::endl;
    std::cout << "Counter2: " << counter2 << std::endl;
    f2 = (Float_t) counter2 / (Float_t) numZeroBiasRndm;
    std::cout << "f2: " << f2 << std::endl;
    std::cout << "Condition: " << abs(numZeroBiasRndm * frac - counter2) << " > " << eps << std::endl;
    outputArray[j+2] = f2;

    algAThreshDiff = (Float_t) thresholdAarray[j+2] - (Float_t) thresholdAarray[j+1];
    algBThreshDiff = (Float_t) thresholdBarray[j+2] - (Float_t) thresholdBarray[j+1];

    algAThreshDiff = abs(algAThreshDiff);
    algBThreshDiff = abs(algBThreshDiff);

  std::cout << "algA current threshold: " << Form("%.7f",thresholdAarray[j+2]) << std::endl;
  std::cout << "algA previous threshold: " << Form("%.7f",thresholdAarray[j+1]) << std::endl;
  std::cout << "algB current threshold: " << Form("%.7f",thresholdBarray[j+2]) << std::endl;
  std::cout << "algB previous threshold: " << Form("%.7f",thresholdBarray[j+1]) << std::endl;
  std::cout << "binWidth: " << binWidth << "\n" << std::endl;

}while ( abs( counter2 - (numZeroBiasRndm * frac) ) > eps && (abs(algAThreshDiff) > binWidth) && (abs(algBThreshDiff) > binWidth) && ( j <= imax ) );

  if ( abs( counter2 - (numZeroBiasRndm * frac) ) <= eps || abs(algAThreshDiff) <= binWidth || abs(algBThreshDiff) <= binWidth)
  {
    std::cout << "A root at x = " <<  initialGuess << " was found to within one bin: " << binWidth << " GeV"
              << " in " << j << " iterations" << std::endl;
    std::cout << "The number of combined events kept is  " << f2 * numZeroBiasRndm << std::endl;
    std::cout << "The fraction of combined events kept is  " << f2 << std::endl;
  }
  else{
    std::cout << "No root found; max iterations exceeded" << std::endl;
  }

acthresh = algAMETx2thresh;
bcthresh = algBMETx2thresh;

TString cstring = algA + " > " + Form(" %.2f", acthresh) + " and " + algB + " > " + Form(" %.2f", bcthresh));
TString astring = algA + " > " + Form(" %.2f", algAThresh);
TString bstring = algB + " > " + Form(" %.2f", algBThresh);
TString dstring = (TString) "L1 > " + Form(" %.2f" , myConstants::metl1thresh);

TEfficiency* Ateff  = new TEfficiency(astring , "Efficiency", muonNbins, muonMetMin, muonMetMax);
TEfficiency* Bteff  = new TEfficiency(bstring , "Efficiency", muonNbins, muonMetMin, muonMetMax);
TEfficiency* Cteff  = new TEfficiency(cstring,  "Efficiency", muonNbins, muonMetMin, muonMetMax);
TEfficiency* Dteff  = new TEfficiency(dstring,  "Efficiency", muonNbins, muonMetMin, muonMetMax);//combined just L1 cut, 0 on others

Float_t algAmuonMET = 0;
Float_t algBmuonMET = 0;
Float_t muonMetl1 = 0;
myMuonTree->SetBranchAddress(algA,&algAmuonMET);
myMuonTree->SetBranchAddress(algB,&algBmuonMET);
myMuonTree->SetBranchAddress("metl1",&muonMetl1);
Int_t numbPassMuon = 0;Float_t w;
for (Int_t l = 0 ; l < muonNentries ; l++)
{
    myMuonTree->GetEntry(l);
    if (algA == algB)
    {
        algAmuonMET = algBmuonMET;
        if ((passmuvarmed > 0.1 || passmuon > 0.1) && cleanCutsFlag > 0.1 && recalBrokeFlag < 0.1)
        {
            w = sqrt(2.0*offrecal_met*metrefmuon*(1-((offrecal_mex*mexrefmuon+offrecal_mey*meyrefmuon)/(
                offrecal_met * metrefmuon))));
            if (w >= 40.0 && w <= 80.0)
            {
                Float_t metnomu = sqrt(((offrecal_mex - offrecalmuon_mex) * (offrecal_mex - offrecalmuon_mex)) +
                ((offrecal_mey - offrecalmuon_mey)*(offrecal_mey - offrecalmuon_mey))); //compute metnomu
                numbPassMuon++;
                Ateff->Fill((algAmuonMET > algAThresh) && (muonMetl1 > myConstants::metl1thresh)&& ( passnoalgL1XE10 > 0.5 ||
                    passnoalgL1XE30 > 0.5 || passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5  ), metnomu);
                Bteff->Fill((algBmuonMET > algBThresh) && (muonMetl1 > myConstants::metl1thresh)&& ( passnoalgL1XE10 > 0.5 ||
                    passnoalgL1XE30 > 0.5 || passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5  ), metnomu);
                Cteff->Fill(((algAmuonMET > acthresh) && (algBmuonMET > bcthresh) && (muonMetl1 > myConstants::metl1thresh))&& ( passnoalgL1XE10 > 0.5 ||
                    passnoalgL1XE30 > 0.5 || passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5  ), metnomu);
            }
        }
    }
    else
    {
        if ((passmuvarmed > 0.1 || passmuon > 0.1) && (cleanCutsFlag > 0.1) && (recalBrokeFlag < 0.1))
    	{
            w = sqrt(2.0*offrecal_met*metrefmuon*(1-((offrecal_mex*mexrefmuon+offrecal_mey*meyrefmuon)/(
                offrecal_met * metrefmuon))));
            if (w >= 40.0 && w <= 80.0)
            {
        	    Float_t metnomu = sqrt(((offrecal_mex - offrecalmuon_mex) * (offrecal_mex - offrecalmuon_mex)) +
        	    ((offrecal_mey - offrecalmuon_mey)*(offrecal_mey - offrecalmuon_mey))); //compute metnomu
                numbPassMuon++;
                Ateff->Fill((algAmuonMET > algAThresh) && (muonMetl1 > myConstants::metl1thresh)&& ( passnoalgL1XE10 > 0.5 ||
                    passnoalgL1XE30 > 0.5 || passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5  ), metnomu);
        	    Bteff->Fill((algBmuonMET > algBThresh) && (muonMetl1 > myConstants::metl1thresh)&& ( passnoalgL1XE10 > 0.5 ||
                    passnoalgL1XE30 > 0.5 || passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5  ), metnomu);
        	    Cteff->Fill(((algAmuonMET > acthresh) && (algBmuonMET > bcthresh) && (muonMetl1 > myConstants::metl1thresh))&& ( passnoalgL1XE10 > 0.5 ||
                    passnoalgL1XE30 > 0.5 || passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5  ), metnomu);
                Dteff->Fill((muonMetl1 >= myConstants::metl1thresh)&& ( passnoalgL1XE10 > 0.5 ||
                    passnoalgL1XE30 > 0.5 || passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5  ), metnomu);
            }
    	}
    }
}

std::cout << "NUMB MUON ENTRIES PASSED ALG A: " << (Ateff->GetPassedHistogram())->GetEntries() << std::endl;
std::cout << "NUMB MUON ENTRIES PASSED ALG B: " << (Bteff->GetPassedHistogram())->GetEntries() << std::endl;
std::cout << "NUMB MUON ENTRIES PASSED ALG C: " << (Cteff->GetPassedHistogram())->GetEntries() << std::endl;
std::cout << "NUMB MUON ENTRIES TOTAL  ALG A: " << (Ateff->GetTotalHistogram())->GetEntries() << std::endl;
std::cout << "NUMB MUON ENTRIES TOTAL  ALG B: " << (Bteff->GetTotalHistogram())->GetEntries() << std::endl;
std::cout << "NUMB MUON ENTRIES TOTAL  ALG C: " << (Cteff->GetTotalHistogram())->GetEntries() << std::endl;
std::cout << "Running determineMuonEventsKeptCombined.C to check number of MUON events kept at fraction determined by the bisection algorithm..." << std::endl;
Float_t muonEventsCombined = determineMuonEventsKeptCombined( algA , acthresh , algB , bcthresh, muonFilename );

TCanvas* efficiencyCanvas = new TCanvas("Efficiency Canvas", "Efficiency Canvas");
efficiencyCanvas->RangeAxis(0,0,500,1.0);


if (algA==algB)
{
    Ateff->SetLineColorAlpha(kBlue,0.35);
    Cteff->SetLineColorAlpha(kRed,0.65);
    Bteff->SetLineColorAlpha(kGreen,0.45);
}
else
{
    Ateff->SetLineColor(kBlue);
    Cteff->SetLineColor(kRed);
    Bteff->SetLineColor(kGreen);
    Dteff->SetLineColor(kBlack);
}

const TString canvName = algA + " and " + algB + " Combined Efficiency" + ";Offline Recalibrated MET w/o Muon term [GeV];Efficiency";

Ateff->SetTitle(canvName);

Ateff->Draw();
Bteff->Draw("same");
Cteff->Draw("same");
Dteff->Draw("same");



TLegend *legend = new TLegend(0.60,0.15,0.87, 0.35 ,"","NDC");
legend->AddEntry(Ateff, astring);
legend->AddEntry(Bteff, bstring);
legend->AddEntry(Cteff, cstring);
legend->AddEntry(Dteff, dstring);
legend->Draw();
TString folderPath = "./TEfficienciesPics/" + folder + "-" +  algA + "_and_" + algB + "_efficiencies.png";
efficiencyCanvas->Print(folderPath);

TString logFileName = "./TEfficienciesPics/" + folder +  algA + "_and_" + algB + "_efficiencies.txt";
std::cout << "Generating log file: " << logFileName << std::endl;
const char* newLogFileName = logFileName.Data(); //need to go inside and grab data to caste to a data type so i can open ofstream
std::ofstream logFile;
logFile.open(newLogFileName, std::fstream::out);
if(logFile) std::cout << "logFile Successfully Opened" << std::endl;

logFile << "Algorithms: " << algA << "\t" << algB << "\r\n";
logFile << "Nbins: " << nbins << "\t METMIN: " << metMin << "\t METMAX: " << metMax << "\r\n";
logFile << "METL1 THRESH: " << myConstants::metl1thresh << "\r\n";
logFile << "Fraction to keep of zerobias for bisection: " << frac << "\r\n";
logFile << "ZEROBIAS DATAFILE: " << zerobiasFileName << "\r\n";
logFile << "ZEROIAS NENTRIES : " << zerobiasNentries << "\r\n";
logFile << "NUMBZEROBIASRNDM: " << numZeroBiasRndm << "\r\n";
logFile << "Fraction times numZeroBiasRndm: " << frac * numZeroBiasRndm << "\r\n";
logFile << "Threshold for " + algA + " to keep fraction by itself: " << algAThresh << "\r\n";
logFile << "Threshold for " + algB + " to keep fraction by itself: " << algBThresh << "\r\n";
logFile << "MUON DATAFILE: " << muonFilename << "\r\n";
logFile << "MUON NENTRIES: " << muonNentries << "\r\n";
logFile << "NUMBERPASSMUON: " << numbPassMuon << "\r\n";
logFile << "Number MUON events kept using final zerobias thresholds determined below: " << muonEventsCombined << "\r\n";
logFile << "Fraction times Numb MUON events kept: " << frac * numbPassMuon << "\r\n";
logFile << "NUMB MUON ENTRIES PASSED ALG A: " << (Ateff->GetPassedHistogram())->GetEntries() << "\r\n";
logFile << "NUMB MUON ENTRIES PASSED ALG B: " << (Bteff->GetPassedHistogram())->GetEntries() << "\r\n";
logFile << "NUMB MUON ENTRIES PASSED ALG C: " << (Cteff->GetPassedHistogram())->GetEntries() << "\r\n";
logFile << "NUMB MUON ENTRIES TOTAL  ALG A: " << (Ateff->GetTotalHistogram())->GetEntries() << "\r\n";
logFile << "NUMB MUON ENTRIES TOTAL  ALG B: " << (Bteff->GetTotalHistogram())->GetEntries() << "\r\n";
logFile << "NUMB MUON ENTRIES TOTAL  ALG C: " << (Cteff->GetTotalHistogram())->GetEntries() << "\r\n";
logFile << "Epsilon tolerance for bisection accuracy: " << eps << " events" << "\r\n";
logFile << "ZEROBIAS Bisection Information: " << "\r\n";
logFile << "Iteration Number : " << "\tIndividual Fraction: \t" << "Combined Fraction Kept: \t" << "Combined Events Kept: \t" <<
"Threshold for " + algA + '\t' << "Threshold for " + algB +'\t' << "\r\n";
logFile << "x1\t\t\t" << inputArray[0] << "\t\t\t" << outputArray[0] << "\t\t\t" << numEventsArray[0] << "\t\t\t" <<
algAMETx1thresh << "\t\t\t" << algBMETx1thresh << "\r\n";
logFile << "x2\t\t\t" << inputArray[2] << "\t\t" << outputArray[2] << "\t\t\t" << numEventsArray[2] << "\t\t\t" <<
algAMETx2thresh << "\t\t\t" << algBMETx2thresh <<"\r\n";
logFile << "x3\t\t\t" << inputArray[1] << "\t\t\t" << outputArray[1] << "\t\t\t" << numEventsArray[1] << "\t\t\t" <<
algAMETx3thresh << "\t\t\t" << algBMETx3thresh <<"\r\n";
for (Int_t m = 1; m < j+1 ; m++)
{
  logFile << Form("I%d",m) << "\t\t\t" << Form("%.7f",inputArray[m+2]) << "\t\t" << Form("%.7f",outputArray[m+2])
  << "\t\t\t" << Form("%.7f",numEventsArray[m+2]) << "\t\t" << Form("%.7f",thresholdAarray[m+2]) << "\t\t" <<
  Form("%.7f",thresholdBarray[m+2]) << "\r\n";
}
logFile.close();
return(0);
}

Float_t computeThresh(TH1F* target, Float_t numKeep)
{
    Int_t nbin = 0;
    gROOT->ProcessLine("gROOT->Reset();");
    target->GetBinWithContent(numKeep,nbin,0,-1,20000); //if firstx<=0{firstx=1}; if lastx<firstx{lastx=fXaxis.GetNbinsX()};
    Float_t thresh = (target->GetXaxis())->GetBinCenter(nbin);
    return(thresh);
}


Float_t determineZeroBiasThresh( const TString& alg, const Float_t frac = 0.00590,
const TString& zeroBiasFileName = "PhysicsMain.All.noalgXEtriggers.2016.f731f758._m1659m1710.48Runs")
{
    TString zeroBiasPath = "../myData/" + zeroBiasFileName;
    std::cout << "DETERMINETHRESH.C" << std::endl;
    std::cout << "ZERO BIAS DATAFILE: " << zeroBiasPath << std::endl;
    std::cout << "ALG: " << alg << std::endl;
    std::cout << "L1 THRESH: " << myConstants::metl1thresh << std::endl;
	TFile *zeroBiasFile = TFile::Open(zeroBiasPath, "READ");
	TTree *zeroBiasTree = (TTree*)(zeroBiasFile->Get("tree"));
	Int_t zerobiasNentries = zeroBiasTree->GetEntries();
    Int_t passRndm;
	Int_t nbins = myConstants::nbins;
	Double_t metMin = myConstants::metMin;
	Double_t metMax = myConstants::metMax;
    Float_t metl1thresh = myConstants::metl1thresh;
	Float_t metl1, metcell, metmht, mettopocl, mettopoclps, mettopoclpuc, indeterminate,
	metcellthresh, metmhtthresh, mettopoclthresh, mettopoclpsthresh, mettopoclpucthresh,rightHandSum;
    Int_t passnoalgL1XE10,passnoalgL1XE30,passnoalgL1XE40,passnoalgL1XE45;
    TH1F *indeterminateHist = new TH1F(alg, alg, nbins, metMin, metMax);
	zeroBiasTree->SetBranchAddress(alg,&indeterminate);
	zeroBiasTree->SetBranchAddress("metl1",&metl1);
    zeroBiasTree->SetBranchAddress("passrndm", &passRndm);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE10",&passnoalgL1XE10);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE30",&passnoalgL1XE30);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE40",&passnoalgL1XE40);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE45",&passnoalgL1XE45);
	TString xlabel = "MET [GeV]";
	TString yaxis = "Events";
    for (Int_t k = 0; k < zerobiasNentries; k++)
	{
		zeroBiasTree->GetEntry(k);
		if (( ( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 || passnoalgL1XE40 > 0.5 ||
            passnoalgL1XE45 > 0.5 ) && ( metl1 > metl1thresh ) ))
		{
			indeterminateHist->Fill(indeterminate);
		}

    }
	std::cout << "FRACTION: " << frac << std::endl;
	std::cout << "ZEROBIAS NENTRIES: " << zerobiasNentries << std::endl;

    TH1F *indeterminatetarget = (TH1F*) indeterminateHist->GetCumulative(kFALSE);
	Float_t numKeep = 5762.0;
	Float_t indeterminateThresh = computeThresh(indeterminatetarget, numKeep);
	std::cout << alg << " THRESHOLD: " << indeterminateThresh << std::endl;
	std::cout << "Number of events that should have been kept: " << numKeep << std::endl;
	std::cout << "Checking how many events are kept by the alg at the determined threshold..." << std::endl;
	Int_t counter=0;
	for (Int_t l = 0 ; l < zerobiasNentries ; l++)
	{
		zeroBiasTree->GetEntry(l);
		if (( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 || passnoalgL1XE40 > 0.5 ||
            passnoalgL1XE45 > 0.5 ) && (indeterminate > indeterminateThresh) && (metl1 > metl1thresh))
		{
			counter++;
		}
	}
	zeroBiasFile->Close();
	std::cout << "Number of events counted above threshold: " << counter << "\n" << std::endl;
	return(indeterminateThresh);
}

Float_t determineMuonEventsKeptCombined( const TString& algA, const Float_t threshA, const TString& algB,
    const Float_t threshB,
    const TString& muonFileName = "PhysicsMain2016.Muons.noalgL1XE45R3073065R311481Runs9B.root")
{
    std::cout << "Determining fraction of muon events kept when using combined algorithm of " << algA << " at: " << threshA << ", "
    << algB << " at: " << threshB << " and metl1 at: " << myConstants::metl1thresh << std::endl;
    TString muonFilePath = "../myData/"+muonFileName;
    TFile * muonFile = TFile::Open(muonFilePath, "READ");
    TTree* muonTree = (TTree*)muonFile->Get("tree");
    Int_t muonNentries = muonTree->GetEntries();
    Float_t algAMET, algBMET,metl1,w;
    Int_t passmuon,passmuvarmed,recalBrokeFlag,cleanCutsFlag;
    Float_t offrecal_met,offrecal_mex,offrecal_mey,offrecalmuon_mex,offrecalmuon_mey,metrefmuon,mexrefmuon,meyrefmuon;
    muonTree->SetBranchAddress("passmu26med",&passmuon);
    muonTree->SetBranchAddress("passmu26varmed",&passmuvarmed);
    muonTree->SetBranchAddress("recalbroke",&recalBrokeFlag);
    muonTree->SetBranchAddress("passcleancuts",&cleanCutsFlag);
    muonTree->SetBranchAddress(algA,&algAMET);
    muonTree->SetBranchAddress(algB,&algBMET);
    muonTree->SetBranchAddress("metl1",&metl1);
    muonTree->SetBranchAddress("metoffrecal", &offrecal_met);
    muonTree->SetBranchAddress("mexoffrecal", &offrecal_mex);
    muonTree->SetBranchAddress("meyoffrecal", &offrecal_mey);
    muonTree->SetBranchAddress("mexoffrecalmuon", &offrecalmuon_mex);
    muonTree->SetBranchAddress("meyoffrecalmuon", &offrecalmuon_mey);
    muonTree->SetBranchAddress("metrefmuon", &metrefmuon);
    muonTree->SetBranchAddress("mexrefmuon", &mexrefmuon);
    muonTree->SetBranchAddress("meyrefmuon", &meyrefmuon);
    Int_t counter = 0;
    Int_t numbPassMuon = 0;
    if (algA==algB)
    {
        for (Int_t i  = 0 ; i < muonNentries ;i++)
          {
            muonTree->GetEntry(i);
            algAMET=algBMET;
            w = sqrt(2.0*offrecal_met*metrefmuon*(1-((offrecal_mex*mexrefmuon+offrecal_mey*meyrefmuon)/(
                offrecal_met * metrefmuon))));
            if ( ((passmuon > 0.5) || (passmuvarmed > 0.5)) && cleanCutsFlag > 0.1 && recalBrokeFlag < 0.1&& w >= 40.0 && w <= 80.0 )
            {
              numbPassMuon++;
            }
            if (((passmuon > 0.5) || (passmuvarmed > 0.5)) && cleanCutsFlag > 0.1 && recalBrokeFlag < 0.1
            && (algAMET > threshA) && (algBMET > threshB) && (metl1 > myConstants::metl1thresh)&& w >= 40.0 && w <= 80.0 )
            {
              counter++;
            }
          }
    }
    else
    {
        for (Int_t i  = 0 ; i < muonNentries ;i++)
        {
          	muonTree->GetEntry(i);
            w = sqrt(2.0*offrecal_met*metrefmuon*(1-((offrecal_mex*mexrefmuon+offrecal_mey*meyrefmuon)/(
                offrecal_met * metrefmuon))));
          	if ( ((passmuon > 0.5) || (passmuvarmed > 0.5)) && cleanCutsFlag > 0.1 && recalBrokeFlag < 0.1 && w >= 40.0 && w <= 80.0)
          	{
          	  numbPassMuon++;
          	}
          	if ( ((passmuon > 0.5) || (passmuvarmed > 0.5)) && (algAMET > threshA) && (algBMET > threshB) &&
            ((metl1 > myConstants::metl1thresh)&& cleanCutsFlag > 0.1 && recalBrokeFlag < 0.1)&& w >= 40.0 && w <= 80.0)
          	{
          	  counter++;
          	}
        }
    }
    std::cout << "Number of pass muon events kept: " << counter << std::endl;
    Float_t frac = (Float_t) counter / (Float_t) passmuon;
    std::cout << "Fraction of pass muon events kept: " << frac << std::endl;
    return(counter);
}
