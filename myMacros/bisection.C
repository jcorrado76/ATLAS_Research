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
#include "TNtuple.h"


//TODO: implement proof lite
Float_t bisection(TString& algA , TString& algB, const Float_t binWidth, const Int_t numZeroBiasRndm = 0 , const Float_t frac = 0.00590, TNtuple* logFileData = NULL,
                  Float_t & individAThreshFinal = 0.0, Float_t & individBThreshFinal = 0.0, TTree* zeroBiasTree = NULL)
{
    Float_t computeThresh( const TH1F*, const Float_t);
    //some useful parameters

    Float_t metl1thresh = 50.0;

    Float_t lwrbnd = 0.5*frac;
    Float_t uprbnd = 0.13;
    Float_t eps = 25.0;

    Float_t x1,x3; //thresholds of individual algorithms
    Float_t f1,f2,f3 = 0; //fractions of events kept out of passrndm
    x1 = lwrbnd;
    x3 = uprbnd;
    Float_t initialGuess = ( x1 + x3 ) / 2.0;
    Float_t firstGuess = initialGuess;
    Float_t numKeepx1 = numZeroBiasRndm * x1;
    Float_t numKeepx2 = numZeroBiasRndm * initialGuess;
    Float_t numKeepx3 = numZeroBiasRndm * x3;

    //compute the cumulative right hand sum hists
    TH1F *algAMETtarget = (TH1F*) hist1->GetCumulative(kFALSE);
    TH1F *algBMETtarget = (TH1F*) hist2->GetCumulative(kFALSE);
    //rename for clarity later on
    algAMETtarget->SetName(algAMETtarget->GetName() + (const TString)"A");
    algBMETtarget->SetName(algBMETtarget->GetName() + (const TString)"B");

    //compute thresholds at boundaris to use
    Float_t algAMETx1thresh,algAMETx2thresh,algAMETx3thresh,algBMETx1thresh,algBMETx2thresh, algBMETx3thresh;
    algAMETx1thresh = computeThresh(algAMETtarget, numKeepx1);
    algBMETx1thresh = computeThresh(algBMETtarget, numKeepx1);

    algAMETx2thresh = computeThresh(algAMETtarget, numKeepx2);
    algBMETx2thresh = computeThresh(algBMETtarget, numKeepx2);

    algAMETx3thresh = computeThresh(algAMETtarget, numKeepx3);
    algBMETx3thresh = computeThresh(algBMETtarget, numKeepx3);

    //print the status
    std::cout << "numZeroBiasRndm: " << numZeroBiasRndm << std::endl;
    std::cout << "frac " << frac << std::endl;
    std::cout << "numCombined to keep: " << numZeroBiasRndm * frac << std::endl;

    std::cout << "Entering bisection to determine individual fractions" << std::endl;
    std::cout << "Lower Bound: " << lwrbnd << std::endl;
    std::cout << "Midpoint: " << (lwrbnd+uprbnd)/2. << std::endl;
    std::cout << "Upper Bound: " << uprbnd << std::endl;
    std::cout << "Epsilon: " << eps << std::endl;

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
    std::cout << "metl1thresh : " << metl1thresh << std::endl;
    Float_t algAMET,algBMET, metl1,passnoalgL1XE10,passnoalgL1XE30,passnoalgL1XE40,passnoalgL1XE45;

    zeroBiasTree->SetBranchAddress(algA,&algAMET);
    zeroBiasTree->SetBranchAddress(algB,&algBMET);
    zeroBiasTree->SetBranchAddress("metl1",&metl1);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE10",&passnoalgL1XE10);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE30",&passnoalgL1XE30);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE40",&passnoalgL1XE40);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE45",&passnoalgL1XE45);

    Int_t counter1,counter2,counter3;

    Int_t zerobiasNentries = zeroBiasTree->GetEntries();

    for (Int_t i  = 0 ; i < zerobiasNentries ;i++) //determine events kept at each guess
    {
    zeroBiasTree->GetEntry(i);
        //if (passRndm > 0.5)
        //{
            if ((algAMET > algAMETx1thresh) && (algBMET > algBMETx1thresh) && (metl1 > metl1thresh)&& ( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 ||
            passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5  ) )
            {
            counter1++;
            }
            if ((algAMET > algAMETx2thresh) && (algBMET > algBMETx2thresh) && (metl1 > metl1thresh)&& ( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 ||
            passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5  ))
            {
            counter2++;
            }
            if ((algAMET > algAMETx3thresh) && (algBMET > algBMETx3thresh) && (metl1 > metl1thresh)&& ( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 ||
            passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5  ) )
            {
            counter3++;
            }
        //}
    }

    //compute fractions kept at initial guesses
    f1 = (Float_t) counter1 / (Float_t) numZeroBiasRndm;
    f2 = (Float_t) counter2 / (Float_t) numZeroBiasRndm;
    f3 = (Float_t) counter3 / (Float_t) numZeroBiasRndm;

    //initialize ntuples with initial guess values
    logFileData->Fill(x1,f1,counter1,algAMETx1thresh,algBMETx1thresh);
    logFileData->Fill(initialGuess,f2,counter2,algAMETx2thresh,algBMETx2thresh);
    logFileData->Fill(x3,f3,counter3,algAMETx3thresh,algBMETx3thresh);

    std::cout << "At x1 = " << x1 << " counter1: " << counter1 << " events = " << "f1: " << f1 << std::endl;
    std::cout << "At x2 = " << initialGuess << " counter2: " << counter2 << " events = " << "f2: " << f2 << std::endl;
    std::cout << "At x3 = " << x3 << " counter3: " << counter3 << " events" << "f3: " << f3 << std::endl;


    Int_t j = 0;
    Int_t imax = 30;

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
        std::cout << "New Guess: " << initialGuess << std::endl;
        std::cout << "numZeroBiasRndm: " << numZeroBiasRndm << std::endl;
        numKeepx2 = numZeroBiasRndm * initialGuess;
        std::cout << "numKeepx2: " << numKeepx2 << std::endl;
        algAMETx2thresh = computeThresh(algAMETtarget, numKeepx2);
        algBMETx2thresh = computeThresh(algBMETtarget, numKeepx2);


        counter2 = 0;

    	for (Int_t i  = 0 ; i < zerobiasNentries ;i++)
    	{
    	  zeroBiasTree->GetEntry(i);
    	  if ((algAMET > algAMETx2thresh) && (algBMET > algBMETx2thresh) && (metl1 > metl1thresh)&& ( passnoalgL1XE10 > 0.5 ||
              passnoalgL1XE30 > 0.5 || passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5  ) )
    	  {
    	    counter2++;
    	  }
        }


        std::cout << "algAMETx2thresh: " << algAMETx2thresh << std::endl;
        std::cout << "algBMETx2thresh: " << algBMETx2thresh << std::endl;
        std::cout << "Counter2: " << counter2 << std::endl;
        f2 = (Float_t) counter2 / (Float_t) numZeroBiasRndm;
        std::cout << "f2: " << f2 << std::endl;
        std::cout << "Condition: " << abs(numZeroBiasRndm * frac - counter2) << " > " << eps << std::endl;




        algAThreshDiff = (thresholdAarray->GetArgs())[j+2] - (thresholdAarray->GetArgs())[j+1];
        algBThreshDiff = (thresholdBarray->GetArgs())[j+2] - (thresholdBarray->GetArgs())[j+1];

        algAThreshDiff = abs(algAThreshDiff);
        algBThreshDiff = abs(algBThreshDiff);

      std::cout << "algA current threshold: " << Form("%.7f",(thresholdAarray->GetArgs())[j+2]) << std::endl;
      std::cout << "algA previous threshold: " << Form("%.7f",(thresholdAarray->GetArgs())[j+1]) << std::endl;
      std::cout << "algB current threshold: " << Form("%.7f",(thresholdBarray->GetArgs())[j+2]) << std::endl;
      std::cout << "algB previous threshold: " << Form("%.7f",(thresholdBarray->GetArgs())[j+1]) << std::endl;
      std::cout << "binWidth: " << binWidth << "\n" << std::endl;

      logFileData->Fill(initialGuess,f2,counter2,algAMETx2thresh,algBMETx2thresh);
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

    individAThreshFinal = algAMETx2thresh;
    individBThreshFinal = algBMETx2thresh;

    return( initialGuess );
}
