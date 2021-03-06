#include "Efficiency_Library.h"
#include "Bisection_Objective_Function.h"


Float_t bisection( userInfo* parameters , TH1F* algAHist , TH1F* algBHist, TTree* passnoalgTree )
{
    // Get Parameters from UserInfo {{{
    const Float_t trigger_rate                          = parameters->Get_Frac(); 
    Float_t metl1thresh                         = parameters->Get_MetL1Thresh();
    Float_t actintCut                           = parameters->Get_ActintCut();
    Int_t epsilon                               = parameters->Get_Epsilon();
    Float_t passrndmcut                         = parameters->Get_Passrndmcut();
    // process 1 means ispassnoalg and is l1>50. if i were using zb events, it would just mean passed rndm
    const Int_t Number_ZeroBias_Events      = parameters->Get_NumThreshPassProcess1();
    const Float_t BinWidth                      = parameters->Get_BinWidth();
    const Float_t passnoalgcut                  = parameters->Get_Passnoalgcut();
    Int_t target = Number_ZeroBias_Events * trigger_rate;
    //}}}
    Bisection_Objective_Function* Bisection_Objective = new Bisection_Objective_Function();
    // printing the number of entries in histograms 
    std::cout << "Number_ZeroBias_Events: " << Number_ZeroBias_Events << std::endl;
    std::cout << "algAHist nentries: " << algAHist->GetEntries() << std::endl;
    std::cout << "algBHist nentries: " << algBHist->GetEntries() << std::endl;
    // Compute Some Parameters and Initialize Variables {{{
    Float_t lwrbnd = 0.5 * trigger_rate;
    Float_t uprbnd = 0.13;
    Float_t x1,x3; //thresholds of individual algorithms
    Float_t FractionEventsKeptCombinedCutAtX1,FractionEventsKeptCombinedCutAtX2,FractionEventsKeptCombinedCutAtX3 = 0; //trigger_ratetions of events kept out of passrndm
    x1 = lwrbnd;
    x3 = uprbnd;
    Float_t initialGuess = ( x1 + x3 ) / 2.0;
    Float_t firstGuess = initialGuess;
    Float_t numKeepx1 = Number_ZeroBias_Events * x1;
    Float_t numKeepx2 = Number_ZeroBias_Events * initialGuess;
    Float_t numKeepx3 = Number_ZeroBias_Events * x3;
    std::cout << "Number zerobias events * x1: " << numKeepx1 << std::endl;
    std::cout << "Number zerobias events * x2: " << numKeepx2 << std::endl;
    std::cout << "Number zerobias events * x3: " << numKeepx3 << std::endl;
    //}}}
    //compute the cumulative right hand sum hists{{{
    TH1F *algAMETtarget = (TH1F*) algAHist->GetCumulative(kFALSE);
    TH1F *algBMETtarget = (TH1F*) algBHist->GetCumulative(kFALSE);
    //}}}
    //rename for clarity later on{{{
    algAMETtarget->SetName(algAMETtarget->GetName() + (const TString)"A");
    algBMETtarget->SetName(algBMETtarget->GetName() + (const TString)"B");
    //}}}
    //compute thresholds at boundaris to use
    Float_t algAMETx1thresh,algAMETx2thresh,algAMETx3thresh,algBMETx1thresh,algBMETx2thresh, algBMETx3thresh;
    //Display parameters of bisection {{{
    std::cout << "Number Zero Bias Events: " << Number_ZeroBias_Events << std::endl;
    std::cout << "Process2 No Actint Cut trigger_ratetion: " << trigger_rate << std::endl;
    std::cout << "Number of ZeroBias Events to Keep at trigger rate: " << target << std::endl;

    std::cout << "Entering bisection to determine individual fractions to keep trigger rate when combined" << std::endl;
    std::cout << "Lower Bound: " << lwrbnd << std::endl;
    std::cout << "Midpoint: " << (lwrbnd+uprbnd)/2. << std::endl;
    std::cout << "Upper Bound: " << uprbnd << std::endl;
    std::cout << "Epsilon: " << epsilon << std::endl;
    //}}}

    passnoalgTree->SetBranchAddress("actint",&passnoalg_actint);
    passnoalgTree->SetBranchAddress("passrndm",&passrndm);
    passnoalgTree->SetBranchAddress("passcleancuts",&passcleancutsflag);
    passnoalgTree->SetBranchAddress("recalbroke",&recalbrokeflag);

    Bisection_Objective->Set_ActintCut( actintCut );
    Bisection_Objective->SetL1Thresh( metl1thresh );

    //compute trigger_ratetions kept at initial guesses{{{
    // TODO: replace these RHS's with function evaluations to bisection objective that returns trigger rate
    // then delete virtually everything above
    Bisection_Objective->SetNumbToKeep( numKeepx1 );
    zb_tree->Process( Bisection_Objective );
    FractionEventsKeptCombinedCutAtX1 = Bisection_Objective->GetTriggerRate();

    Bisection_Objective->SetNumbToKeep( numKeepx2 );
    zb_tree->Process( Bisection_Objective );
    FractionEventsKeptCombinedCutAtX2 = Bisection_Objective->GetTriggerRate();

    Bisection_Objective->SetNumbToKeep( numKeepx3 );
    zb_tree->Process( Bisection_Objective );
    FractionEventsKeptCombinedCutAtX3 = Bisection_Objective->GetTriggerRate();

    std::cout << "At x1 = " << x1 << " number_events_kept_combined_at_x1: " << number_events_kept_combined_at_x1 << " events " << std::endl;
    std::cout << "FractionEventsKeptCombinedCutAtX1: " << FractionEventsKeptCombinedCutAtX1 << std::endl;
    std::cout << "At x2 = " << initialGuess << " number_events_kept_combined_at_x2: " << number_events_kept_combined_at_x2 << " events " << std::endl;
    std::cout << "FractionEventsKeptCombinedCutAtX2: " << FractionEventsKeptCombinedCutAtX2 << std::endl;
    std::cout << "At x3 = " << x3 << " number_events_kept_combined_at_x3: " << number_events_kept_combined_at_x3 << " events " << std::endl;
    std::cout << "FractionEventsKeptCombinedCutAtX3: " << FractionEventsKeptCombinedCutAtX3 << std::endl;


    Float_t inputArray[100];
    Float_t outputArray[100];
    Float_t numEventsArray[100];
    Float_t thresholdAarray[100];
    Float_t thresholdBarray[100];

    inputArray[0] = x1;
    inputArray[2] = initialGuess;
    inputArray[1] = x3;
    outputArray[0] = FractionEventsKeptCombinedCutAtX1;
    outputArray[2] = FractionEventsKeptCombinedCutAtX2;
    outputArray[1] = FractionEventsKeptCombinedCutAtX3;
    numEventsArray[0] = number_events_kept_combined_at_x1;
    numEventsArray[2] = number_events_kept_combined_at_x2;
    numEventsArray[1] = number_events_kept_combined_at_x3;
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
    //}}}
    // Bisection {{{
    do{
        j++;
        std::cout << "Inside iteration number: " << j << std::endl;
        if ( (FractionEventsKeptCombinedCutAtX1-trigger_rate)*(FractionEventsKeptCombinedCutAtX2-trigger_rate) < 0 ) //root is in left half of interval
        {
          std::cout << "Root is to the left of " << initialGuess << std::endl;
          FractionEventsKeptCombinedCutAtX3 = FractionEventsKeptCombinedCutAtX2;
          x3 = initialGuess;
        }
        else //root is in right half of  interval
        {
          std::cout << "Root is to the right of " << initialGuess << std::endl;
          FractionEventsKeptCombinedCutAtX1 = FractionEventsKeptCombinedCutAtX2;
          x1 = initialGuess;
        }
        initialGuess = ( x1 + x3 ) / 2.0;
        inputArray[j+2] = initialGuess;
        std::cout << "New Guess: " << initialGuess << std::endl;
        std::cout << "numPassedProcess1WithActintCut: " << Number_ZeroBias_Events << std::endl;
        numKeepx2 = Number_ZeroBias_Events * initialGuess;
        std::cout << "numKeepx2: " << numKeepx2 << std::endl;
        algAMETx2thresh = computeThresh(algAMETtarget, numKeepx2);
        algBMETx2thresh = computeThresh(algBMETtarget, numKeepx2);

        thresholdAarray[j+2] = (Float_t) algAMETx2thresh;
        thresholdBarray[j+2] = (Float_t) algBMETx2thresh;

        number_events_kept_combined_at_x2 = 0;
        Bisection_Objective->SetNumbToKeep( numKeepx2 );
        passnoalgTree->Process( Bisection_Objective );
        FractionEventsKeptCombinedCutAtX2 = Bisection_Objective->GetTriggerRate();
        Bisection_Objective->Clear();

        numEventsArray[j+2] = number_events_kept_combined_at_x2;

        std::cout << "algAMETx2thresh: " << algAMETx2thresh << std::endl;
        std::cout << "algBMETx2thresh: " << algBMETx2thresh << std::endl;
        std::cout << "Trigger Rate at x2: " << FractionEventsKeptCombinedCutAtX2 << std::endl;
        std::cout << "Condition: " << abs(target - number_events_kept_combined_at_x2) << " > " << epsilon << std::endl;
        outputArray[j+2] = FractionEventsKeptCombinedCutAtX2;

        algAThreshDiff = thresholdAarray[j+2] - thresholdAarray[j+1];
        algBThreshDiff = thresholdBarray[j+2] - thresholdBarray[j+1];

        algAThreshDiff = abs(algAThreshDiff);
        algBThreshDiff = abs(algBThreshDiff);

      std::cout << "algA current threshold: " << Form("%.7f",thresholdAarray[j+2]) << std::endl;
      std::cout << "algA previous threshold: " << Form("%.7f",thresholdAarray[j+1]) << std::endl;
      std::cout << "algB current threshold: " << Form("%.7f",thresholdBarray[j+2]) << std::endl;
      std::cout << "algB previous threshold: " << Form("%.7f",thresholdBarray[j+1]) << std::endl;
      std::cout << "BinWidth: " << BinWidth << "\n" << std::endl;



    }while ( abs( number_events_kept_combined_at_x2 - (target) ) > epsilon && (abs(algAThreshDiff) > BinWidth) && (abs(algBThreshDiff) > BinWidth) && ( j <= imax ) );

      if ( abs( number_events_kept_combined_at_x2 - (target) ) <= epsilon || abs(algAThreshDiff) <= BinWidth || abs(algBThreshDiff) <= BinWidth)
      {
        std::cout << "A root at x = " <<  initialGuess << " was found to within one bin: " << BinWidth << " GeV"
                  << " in " << j << " iterations" << std::endl;
        std::cout << "The number of combined events kept is  " << FractionEventsKeptCombinedCutAtX2 * Number_ZeroBias_Events << std::endl;
        std::cout << "The fraction of combined events kept is  " << FractionEventsKeptCombinedCutAtX2 << std::endl;
      }
      else{
        std::cout << "No root found; max iterations exceeded" << std::endl;
      }

//}}}
    parameters->Set_AlgACombinedThresh(algAMETx2thresh);
    parameters->Set_AlgBCombinedThresh(algBMETx2thresh);

    //fill TNtuple with the numerical logfile data:
    Int_t k = 0;
    while ( inputArray[k] )
    {
        //write a setter that calls tntuple's fill method on the stuff
        parameters->Fill_Bisection_Data(inputArray[k],outputArray[k],numEventsArray[k],thresholdAarray[k],thresholdBarray[k]);
        k++;
    }

    return( initialGuess );
}
