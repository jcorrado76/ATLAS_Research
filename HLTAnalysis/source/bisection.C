#include "mincerMacros.h"


//TODO: implement proof lite
//TODO: use global calls to param list

Float_t bisection(TH1F* algAHist , TH1F* algBHist, const Float_t binWidth, Float_t &  individAThreshFinal , Float_t  & individBThreshFinal,
    const Int_t numPassedProcess1WithActintCut = 0 , Float_t frac = 0.00590, TNtuple* logFileData = NULL, TTree* passnoalgTree = NULL)
{
    Float_t computeThresh( const TH1F*, const Float_t);
    userInfo* logFileParams;
    //some useful parameters
    frac = logFileParams->getFrac();
    Float_t metl1thresh = logFileParams->getMetL1Thresh();
    Float_t actintCut = logFileParams->getActintCut();
    Int_t epsilon = logFileParams->getEpsilon();

    Int_t target = numPassedProcess1WithActintCut * frac;

    Float_t lwrbnd = 0.5 * frac;
    Float_t uprbnd = 0.13;

    Float_t x1,x3; //thresholds of individual algorithms
    Float_t Process2FracX1WithActintCut,Process2FracX2WithActintCut,Process2FracX3WithActintCut = 0; //fractions of events kept out of passrndm
    x1 = lwrbnd;
    x3 = uprbnd;
    Float_t initialGuess = ( x1 + x3 ) / 2.0;
    Float_t firstGuess = initialGuess;
    Float_t numKeepx1 = numPassedProcess1WithActintCut * x1;
    Float_t numKeepx2 = numPassedProcess1WithActintCut * initialGuess;
    Float_t numKeepx3 = numPassedProcess1WithActintCut * x3;

    //compute the cumulative right hand sum hists
    TH1F *algAMETtarget = (TH1F*) algAHist->GetCumulative(kFALSE);
    TH1F *algBMETtarget = (TH1F*) algBHist->GetCumulative(kFALSE);
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
    std::cout << "numPassedProcess1WithActintCut: " << numPassedProcess1WithActintCut << std::endl;
    std::cout << "Process2 No Actint Cut Fraction: " << frac << std::endl;
    std::cout << "Process 2 with Actint Cut Num to Keep: " << target << std::endl;

    std::cout << "Entering bisection to determine individual fractions" << std::endl;
    std::cout << "Lower Bound: " << lwrbnd << std::endl;
    std::cout << "Midpoint: " << (lwrbnd+uprbnd)/2. << std::endl;
    std::cout << "Upper Bound: " << uprbnd << std::endl;
    std::cout << "Epsilon: " << epsilon << std::endl;

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
    Float_t algAMET,algBMET, metl1;
    Float_t passnoalg_actint = 0 ;
    Int_t passnoalgL1XE10,passnoalgL1XE30,passnoalgL1XE40,passnoalgL1XE45;

    TString algA = algAHist->GetName();
    TString algB = algBHist->GetName();

    passnoalgTree->SetBranchAddress(algA,&algAMET);
    passnoalgTree->SetBranchAddress(algB,&algBMET);
    passnoalgTree->SetBranchAddress("metl1",&metl1);
    passnoalgTree->SetBranchAddress("passnoalgL1XE10",&passnoalgL1XE10);
    passnoalgTree->SetBranchAddress("passnoalgL1XE30",&passnoalgL1XE30);
    passnoalgTree->SetBranchAddress("passnoalgL1XE40",&passnoalgL1XE40);
    passnoalgTree->SetBranchAddress("passnoalgL1XE45",&passnoalgL1XE45);
    passnoalgTree->SetBranchAddress("actint",&passnoalg_actint);

    Int_t numPassedProcess2WithActintCutX1 = 0;
    Int_t numPassedProcess2WithActintCutX2 = 0;
    Int_t numPassedProcess2WithActintCutX3 = 0;

    Int_t passnoalgNentries = passnoalgTree->GetEntries();
    Bool_t passedProcess1ActintCut;
    Bool_t isPassnoalg;

    //compute number of noalg events that pass process 2 at initial 3 guesses of individ fractions
    for (Int_t i  = 0 ; i < passnoalgNentries ;i++) //determine events kept at each guess
    {
        passnoalgTree->GetEntry(i);
        passedProcess1ActintCut = ( metl1 > metl1thresh ) && (passnoalg_actint > actintCut);
        isPassnoalg = ( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 || passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5  );

        if ( isPassnoalg && passedProcess1ActintCut )
        {
            if ((algAMET > algAMETx1thresh) && (algBMET > algBMETx1thresh))
            {
            numPassedProcess2WithActintCutX1++;
            }
            if ((algAMET > algAMETx2thresh) && (algBMET > algBMETx2thresh))
            {
            numPassedProcess2WithActintCutX2++;
            }
            if ((algAMET > algAMETx3thresh) && (algBMET > algBMETx3thresh))
            {
            numPassedProcess2WithActintCutX3++;
            }
        }
    }

    //compute fractions kept at initial guesses
    Process2FracX1WithActintCut = (Float_t) numPassedProcess2WithActintCutX1 / (Float_t) numPassedProcess1WithActintCut;
    Process2FracX2WithActintCut = (Float_t) numPassedProcess2WithActintCutX2 / (Float_t) numPassedProcess1WithActintCut;
    Process2FracX3WithActintCut = (Float_t) numPassedProcess2WithActintCutX3 / (Float_t) numPassedProcess1WithActintCut;

    std::cout << "At x1 = " << x1 << " numPassedProcess2WithActintCutX1: " << numPassedProcess2WithActintCutX1 << " events " << std::endl;
    std::cout << "Process2FracX1WithActintCut: " << Process2FracX1WithActintCut << std::endl;
    std::cout << "At x2 = " << initialGuess << " numPassedProcess2WithActintCutX2: " << numPassedProcess2WithActintCutX2 << " events " << std::endl;
    std::cout << "Process2FracX2WithActintCut: " << Process2FracX2WithActintCut << std::endl;
    std::cout << "At x3 = " << x3 << " numPassedProcess2WithActintCutX3: " << numPassedProcess2WithActintCutX3 << " events " << std::endl;
    std::cout << "Process2FracX3WithActintCut: " << Process2FracX3WithActintCut << std::endl;


    Float_t inputArray[100];
    Float_t outputArray[100];
    Float_t numEventsArray[100];
    Float_t thresholdAarray[100];
    Float_t thresholdBarray[100];

    inputArray[0] = x1;
    inputArray[2] = initialGuess;
    inputArray[1] = x3;
    outputArray[0] = Process2FracX1WithActintCut;
    outputArray[2] = Process2FracX2WithActintCut;
    outputArray[1] = Process2FracX3WithActintCut;
    numEventsArray[0] = numPassedProcess2WithActintCutX1;
    numEventsArray[2] = numPassedProcess2WithActintCutX2;
    numEventsArray[1] = numPassedProcess2WithActintCutX3;
    thresholdAarray[0] = (Float_t) algAMETx1thresh;
    thresholdAarray[2] = (Float_t) algAMETx2thresh;
    thresholdAarray[1] = (Float_t) algAMETx3thresh;
    thresholdBarray[0] = (Float_t) algBMETx1thresh;
    thresholdBarray[2] = (Float_t) algBMETx2thresh;
    thresholdBarray[1] = (Float_t) algBMETx3thresh;

    Int_t j = 0;
    Int_t imax = 30;
    Float_t algAThreshDiff;
    Float_t algBThreshDiff;

    do{
        j++;
        std::cout << "Inside iteration number: " << j << std::endl;
        if ( (Process2FracX1WithActintCut-frac)*(Process2FracX2WithActintCut-frac) < 0 ) //root is in left half of interval
        {
          std::cout << "Root is to the left of " << initialGuess << std::endl;
          Process2FracX3WithActintCut = Process2FracX2WithActintCut;
          x3 = initialGuess;
        }
        else //root is in right half of  interval
        {
          std::cout << "Root is to the right of " << initialGuess << std::endl;
          Process2FracX1WithActintCut = Process2FracX2WithActintCut;
          x1 = initialGuess;
        }
        initialGuess = ( x1 + x3 ) / 2.0;
        inputArray[j+2] = initialGuess;
        std::cout << "New Guess: " << initialGuess << std::endl;
        std::cout << "numPassedProcess1WithActintCut: " << numPassedProcess1WithActintCut << std::endl;
        numKeepx2 = numPassedProcess1WithActintCut * initialGuess;
        std::cout << "numKeepx2: " << numKeepx2 << std::endl;
        algAMETx2thresh = computeThresh(algAMETtarget, numKeepx2);
        algBMETx2thresh = computeThresh(algBMETtarget, numKeepx2);

        thresholdAarray[j+2] = (Float_t) algAMETx2thresh;
        thresholdBarray[j+2] = (Float_t) algBMETx2thresh;


        numPassedProcess2WithActintCutX2 = 0;

    	for (Int_t i  = 0 ; i < passnoalgNentries ;i++)
    	{
    	  passnoalgTree->GetEntry(i);
    	  if ((algAMET > algAMETx2thresh) && (algBMET > algBMETx2thresh) && (metl1 > metl1thresh)&& (passnoalg_actint > actintCut) &&
          ( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 || passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5  ) )
    	  {
    	    numPassedProcess2WithActintCutX2++;
    	  }
        }

        numEventsArray[j+2] = numPassedProcess2WithActintCutX2;

        std::cout << "algAMETx2thresh: " << algAMETx2thresh << std::endl;
        std::cout << "algBMETx2thresh: " << algBMETx2thresh << std::endl;
        std::cout << "Counter2: " << numPassedProcess2WithActintCutX2 << std::endl;
        Process2FracX2WithActintCut = (Float_t) numPassedProcess2WithActintCutX2 / (Float_t) numPassedProcess1WithActintCut;
        std::cout << "Process2FracX2WithActintCut: " << Process2FracX2WithActintCut << std::endl;
        std::cout << "Condition: " << abs(target - numPassedProcess2WithActintCutX2) << " > " << epsilon << std::endl;
        outputArray[j+2] = Process2FracX2WithActintCut;




        algAThreshDiff = thresholdAarray[j+2] - thresholdAarray[j+1];
        algBThreshDiff = thresholdBarray[j+2] - thresholdBarray[j+1];

        algAThreshDiff = abs(algAThreshDiff);
        algBThreshDiff = abs(algBThreshDiff);

      std::cout << "algA current threshold: " << Form("%.7f",thresholdAarray[j+2]) << std::endl;
      std::cout << "algA previous threshold: " << Form("%.7f",thresholdAarray[j+1]) << std::endl;
      std::cout << "algB current threshold: " << Form("%.7f",thresholdBarray[j+2]) << std::endl;
      std::cout << "algB previous threshold: " << Form("%.7f",thresholdBarray[j+1]) << std::endl;
      std::cout << "binWidth: " << binWidth << "\n" << std::endl;



    }while ( abs( numPassedProcess2WithActintCutX2 - (target) ) > epsilon && (abs(algAThreshDiff) > binWidth) && (abs(algBThreshDiff) > binWidth) && ( j <= imax ) );

      if ( abs( numPassedProcess2WithActintCutX2 - (target) ) <= epsilon || abs(algAThreshDiff) <= binWidth || abs(algBThreshDiff) <= binWidth)
      {
        std::cout << "A root at x = " <<  initialGuess << " was found to within one bin: " << binWidth << " GeV"
                  << " in " << j << " iterations" << std::endl;
        std::cout << "The number of combined events kept is  " << Process2FracX2WithActintCut * numPassedProcess1WithActintCut << std::endl;
        std::cout << "The fraction of combined events kept is  " << Process2FracX2WithActintCut << std::endl;
      }
      else{
        std::cout << "No root found; max iterations exceeded" << std::endl;
      }


    individAThreshFinal = algAMETx2thresh;
    individBThreshFinal = algBMETx2thresh;

    //fill TNtuple with the numerical logfile data:
    Int_t k = 0;
    while ( inputArray[k] )
    {
        logFileData->Fill(inputArray[k],outputArray[k],numEventsArray[k],thresholdAarray[k],thresholdBarray[k]);
        k++;
    }

    return( initialGuess );
}
