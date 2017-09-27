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


//TODO: make this return a bool, tell it to return true or false for a given entry if passes transverse mass cut
Float_t w( const Float_t metoffrecal     , const Float_t mexoffrecal     , const Float_t meyoffrecal ,
           const Float_t metoffrecalmuon , const Float_t mexoffrecalmuon , const Float_t meyoffrecalmuon )
{
    Float_t wValue = sqrt( 2.0 * metoffrecal * metoffrecalmuon * ( 1 + ( ( mexoffrecal * mexoffrecalmuon + meyoffrecal * meyoffrecalmuon ) /
                           ( metoffrecal * metoffrecalmuon ) ) ) );
    return(wValue);
}

Float_t computeThresh(const TH1F* target, const Float_t numberEventsToKeep)
{
    Int_t nbin = 0;
    target->GetBinWithContent( numberEventsToKeep , nbin , 5 , -1 , 20000 ); //if firstx<=0{firstx=1}; if lastx<firstx{lastx=fXaxis.GetNbinsX()};
    Float_t thresh = (target->GetXaxis())->GetBinCenter(nbin);
    return(thresh);
}


Float_t determineZeroBiasThresh( const TString& algName, const Float_t frac = 0.00590,
const TString& zeroBiasFileName = "PhysicsMain.All.noalgXEtriggers.2016.f731f758._m1659m1710.48Runs.root")
{
    /*Returns the threshold needed for an algorithm to keep the fraction of zerobias events*/

    const Float_t metL1Thresh = 50;

    //get zerobias tree
    const TString zeroBiasPath = "../myData/" + zeroBiasFileName;
	TFile *zeroBiasFile = TFile::Open(zeroBiasPath, "READ");
	TTree *zeroBiasTree = (TTree*)(zeroBiasFile->Get("tree"));
    const Int_t zerobiasNentries = zeroBiasTree->GetEntries();

    //display inputs
    std::cout << "DETERMINETHRESH.C" << std::endl;
    std::cout << "using zerobias datafile: " << zeroBiasFileName << std::endl;
    std::cout << "alg: " << algName << std::endl;
    std::cout << "using L1 thresh: " << metL1Thresh << std::endl;
    std::cout << "fraction of events to keep: " << frac << std::endl;
    std::cout << "zerobias nentries: " << zerobiasNentries << std::endl;

    //intialize parameters
    const Float_t numberEventsToKeep = 5762.0;
	const Int_t nbins = 1200;
	const Double_t metMin = 0.0;
	const Double_t metMax = 300.0;
	Float_t metl1, algMET;
    Int_t numberEventsKept = 0;
    Int_t passnoalgL1XE10 , passnoalgL1XE30 , passnoalgL1XE40 , passnoalgL1XE45;
    TH1F *indeterminateHist = new TH1F(algName, algName, nbins, metMin, metMax);

    //set branch address for zerobias branches
	zeroBiasTree->SetBranchAddress(algName,&algMET);
	zeroBiasTree->SetBranchAddress("metl1",&metl1);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE10",&passnoalgL1XE10);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE30",&passnoalgL1XE30);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE40",&passnoalgL1XE40);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE45",&passnoalgL1XE45);

    //fill the histogram with entries
    for (Int_t k = 0; k < zerobiasNentries; k++)
	{
		zeroBiasTree->GetEntry(k);
		if ( ( metl1 > metL1Thresh ) &&
            ( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 || passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5 ) )
		{
			indeterminateHist->Fill(algMET);
		}
    }

    //compute the threshold to keep appropriate fraction
    TH1F *indeterminatetarget = (TH1F*) indeterminateHist->GetCumulative(kFALSE);
	Float_t indeterminateThresh = computeThresh(indeterminatetarget, numberEventsToKeep);
	std::cout << algName << "threshold: " << indeterminateThresh << std::endl;
	std::cout << "target number events to keep: " << numberEventsToKeep << std::endl;

    //determine number of events kept at determined threshold (gives idea of error due to binning)
	for (Int_t l = 0 ; l < zerobiasNentries ; l++)
	{
		zeroBiasTree->GetEntry(l);
		if ( (algMET > indeterminateThresh) && (metl1 > metL1Thresh) &&
           ( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 || passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5 ) )
		{
			numberEventsKept++;
		}
	}

    std::cout << "number of events kept at threshold: " << numberEventsKept << "\n" << std::endl;

    zeroBiasFile->Close();

	return(indeterminateThresh);
}

Float_t determineMuonEventsKeptCombined( const TString& algA, const Float_t threshA,
                                         const TString& algB, Float_t threshB,
                                         const TString& muonFileName = "PhysicsMain2016.Muons.noalgL1XE45R3073065R311481Runs9B.root")
{

    const Float_t metL1Thresh = 50.0;
    //display algs and thresholds
    std::cout << "Determining fraction of muon events kept when using combined algorithm of " << algA << " at: " << threshA << ", "
    << algB << " at: " << threshB << " and metl1 at: " << metL1Thresh << std::endl;

    //get muon tree
    TString muonFilePath = "../myData/"+muonFileName;
    TFile * muonFile = TFile::Open(muonFilePath, "READ");
    TTree* muonTree = (TTree*)muonFile->Get("tree");
    Int_t muonNentries = muonTree->GetEntries();

    //initialize variables
    Float_t algAMET, algBMET,metl1, wValue;
    Int_t passmuon,passmuvarmed,recalBrokeFlag,cleanCutsFlag;
    Float_t metoffrecal,metoffrecalmuon,mexoffrecal,meyoffrecal,mexoffrecalmuon,meyoffrecalmuon,metrefmuon,mexrefmuon,meyrefmuon;
    Int_t numbPassedEvents = 0;
    Int_t numberMuonEvents = 0;


    muonTree->SetBranchAddress("passmu26med",&passmuon);
    muonTree->SetBranchAddress("passmu26varmed",&passmuvarmed);
    muonTree->SetBranchAddress("recalbroke",&recalBrokeFlag);
    muonTree->SetBranchAddress("passcleancuts",&cleanCutsFlag);
    muonTree->SetBranchAddress(algA,&algAMET);
    muonTree->SetBranchAddress("metl1",&metl1);
    muonTree->SetBranchAddress("metoffrecal", &metoffrecal);
    muonTree->SetBranchAddress("mexoffrecal", &mexoffrecal);
    muonTree->SetBranchAddress("meyoffrecal", &meyoffrecal);
    muonTree->SetBranchAddress("metoffrecalmuon", &metoffrecalmuon);
    muonTree->SetBranchAddress("mexoffrecalmuon", &mexoffrecalmuon);
    muonTree->SetBranchAddress("meyoffrecalmuon", &meyoffrecalmuon);
    muonTree->SetBranchAddress("metrefmuon", &metrefmuon);
    muonTree->SetBranchAddress("mexrefmuon", &mexrefmuon);
    muonTree->SetBranchAddress("meyrefmuon", &meyrefmuon);

    if ( algA != algB ) {//algs not the same, initialize second alg
         muonTree->SetBranchAddress( algB , &algBMET );
     }
    else {//algs are the same; set B to pass always
        threshB = threshA; algBMET = 0;
    }

    for (Int_t i  = 0 ; i < muonNentries ;i++)
      {
        muonTree->GetEntry(i);

        wValue = w( metoffrecal ,mexoffrecal , meyoffrecal , metoffrecalmuon , mexoffrecalmuon , meyoffrecalmuon );

        if (
               ((passmuon > 0.5) || (passmuvarmed > 0.5)) &&
               (cleanCutsFlag > 0.1 && recalBrokeFlag < 0.1) &&
               (wValue >= 40.0 && wValue <= 80.0) )
        {
          numberMuonEvents++;
        }
        if (
             ((algAMET > threshA) && (algBMET > threshB) && (metl1 > metL1Thresh)) &&
             ((passmuon > 0.5) || (passmuvarmed > 0.5)) &&
             (cleanCutsFlag > 0.1 && recalBrokeFlag < 0.1) &&
             (wValue >= 40.0 && wValue <= 80.0 )
           )
        {
          numbPassedEvents++;
        }
      }


    std::cout << "Number of muon events kept: " << numbPassedEvents << std::endl;
    Float_t frac = numbPassedEvents / numberMuonEvents;
    std::cout << "Fraction of muon events kept: " << frac << std::endl;
    return(numbPassedEvents);
}

/*
Float_t bisection(const TH1F* hist1 , const TH1F* hist2, const Float_t binWidth, const Int_t numZeroBiasRndm = 0 , const Float_t frac = 0.00590)
{
    //TODO: need to finish making the bisection compatible as a separate function

    //some useful parameters
    Int_t j = 0;
    Int_t imax = 30;
    Float_t lwrbnd = 0.5*frac;
    Float_t uprbnd = 0.13;
    Float_t eps = 25.0;
    Float_t x1,x3; //thresholds of individual algorithms
    Float_t f1,f2,f3 = 0; //number of events kept
    x1 = lwrbnd;
    x3 = uprbnd;
    Float_t initialGuess = ( x1 + x3 ) / 2.0;
    Float_t firstGuess = initialGuess;
    Float_t numKeepx1 = numZeroBiasRndm * x1;
    Float_t numKeepx2 = numZeroBiasRndm * initialGuess;
    Float_t numKeepx3 = numZeroBiasRndm * x3;

    //print the status
    std::cout << "Entering bisection to determine individual fractions" << std::endl;
    std::cout << "Lower Bound: " << lwrbnd << std::endl;
    std::cout << "Midpoint: " << (lwrbnd+uprbnd)/2. << std::endl;
    std::cout << "Upper Bound: " << uprbnd << std::endl;
    std::cout << "Epsilon: " << eps << std::endl;


    //generate the cumulative right hand sum histograms
    TH1F *algAMETtarget = (TH1F*) algAMETHist->GetCumulative(kFALSE);
    TH1F *algBMETtarget = (TH1F*) algBMETHist->GetCumulative(kFALSE);

    //set the names of the histograms to also contain the letters A and B
    algAMETtarget->SetName(algAMETtarget->GetName() + (const TString)"A");
    algBMETtarget->SetName(algBMETtarget->GetName() + (const TString)"B");


    //compute initial thresholds at each of the extrema and first guess
    algAMETx1thresh = computeThresh(algAMETtarget, numKeepx1);
    algBMETx1thresh = computeThresh(algBMETtarget, numKeepx1);
    algAMETx2thresh = computeThresh(algAMETtarget, numKeepx2);
    algBMETx2thresh = computeThresh(algBMETtarget, numKeepx2);
    algAMETx3thresh = computeThresh(algAMETtarget, numKeepx3);
    algBMETx3thresh = computeThresh(algBMETtarget, numKeepx3);

    std::cout << "algAx1Thresh: " << algAMETx1thresh << std::endl;
    std::cout << "algBx1Thresh: " << algBMETx1thresh << std::endl;
    std::cout << "metl1thresh : " << myConstants::metl1thresh << std::endl;


    f1 = (Float_t) counter1 / (Float_t) numZeroBiasRndm;
    f2 = (Float_t) counter2 / (Float_t) numZeroBiasRndm;
    f3 = (Float_t) counter3 / (Float_t) numZeroBiasRndm;


    std::cout << "At x1 = " << x1 << " counter1: " << counter1 << " events = " << "f1: " << f1 << std::endl;
    std::cout << "At x2 = " << initialGuess << " counter2: " << counter2 << " events = " << "f2: " << f2 << std::endl;
    std::cout << "At x3 = " << x3 << " counter3: " << counter3 << " events" << "f3: " << f3 << std::endl;





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

    return( initialGuess );
}*/
