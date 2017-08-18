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

Int_t WAnalysis()
{
    //Plots the efficiency curves for (metcell, metmht) , (metcell, mettopocl) , (metcell , mettopoclps) , (metmht, mettopoclpuc)
    //using the W cut, versus not using the W cut

    Float_t computeThresh(TH1F*, FLoat_t);

    TString zeroBiasFileName = "PhysicsMain.All.noalgXEtriggers.2016.f731f758._m1659m1710.48Runs.root";
    TString signalFileName = "PhysicsMain2016.Muons.noalgL1XE45R3073065R311481Runs9B.root";

    TFile* zeroBiasFileHandle = TFile::Open( "../myData/" + zeroBiasFileName );
    TTree* zeroBiasTree = (TTree*) zeroBiasFileHandle->Get("tree");

    Int_t zbNentries = zeroBiasTree->GetEntries();
    Int_t numRndmFlag = 0;
    Int_t passnoalgL1XE10,passnoalgL1XE30,passnoalgL1XE40,passnoalgL1XE45;

    Float_t frac = 0.0059;

    Float_t metl1;
    Float_t metcell;
    Float_t metmht;
    Float_t mettopocl,mettopoclps,mettopoclpuc;

    zeroBiasTree->SetBranchAddress("metl1",&metl1);
    zeroBiasTree->SetBranchAddress("metcell",&metcell);
    zeroBiasTree->SetBranchAddress("metmht",&metmht);
    zeroBiasTree->SetBranchAddress("mettopocl",&mettopocl);
    zeroBiasTree->SetBranchAddress("mettopoclps",&mettopoclps);
    zeroBiasTree->SetBranchAddress("mettopoclpuc",&mettopoclpuc);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE10",&passnoalgL1XE10);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE30",&passnoalgL1XE30);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE40",&passnoalgL1XE40);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE45",&passnoalgL1XE45);

    TH1F *zbCellHist = new TH1F("metcell", "metcell", nbins, metMin, metMax);
    TH1F *zbMhtHist = new TH1F("metmht", "metmht", nbins, metMin, metMax);
    TH1F *zbTopoclHist = new TH1F("mettopocl", "mettopocl", nbins, metMin, metMax);
    TH1F *zbTopoclpsHist = new TH1F("mettopoclps", "mettopoclps", nbins, metMin, metMax);
    TH1F *zbTopoclpucHist = new TH1F("mettopoclpuc", "mettopoclpuc", nbins, metMin, metMax);

    for (Int_t zbIterator = 0 ; zbIterator < zbNentries ; zbIterator++)
    {
        zeroBiasTree->GetEntry(zbIterator);
        if ( (metl1>50.0) && ( passnoalgL1XE10>0.5 || passnoalgL1XE30>0.5 || passnoalgL1XE40>0.5 || passnoalgL1XE45>0.5 ) )
        {
            zbCellHist->Fill(metcell);
            zbMhtHist->Fill(metmht);
            zbTopoclHist->Fill(mettopocl);
            zbTopoclpsHist->Fill(mettopoclps);
            zbTopoclpucHist->Fill(mettopoclpuc);
            numRndmFlag++;
        }
    }
    std::cout << "Numb events pass rndm flag (should be 976825): " << numRndmFlag <<  std::endl;

    TH1F *zbCumulativeCellHist = (TH1F*) zbCellHist->GetCumulative(kFALSE);
    TH1F *zbCumulativeMhtHist = (TH1F*) zbMhtHist->GetCumulative(kFALSE);
    TH1F *zbCumulativeTopoclHist = (TH1F*) zbTopoclHist->GetCumulative(kFALSE);
    TH1F *zbCumulativeTopoclpsHist = (TH1F*) zbTopoclpsHist->GetCumulative(kFALSE);
    TH1F *zbCumulativeTopoclpucHist = (TH1F*) zbTopoclpucHist->GetCumulative(kFALSE);

    Float_t lower_bound = 0.5 * frac;
    Float_t upper_bound = 0.13;
    Float_t epsilon = 25.0;


    Float_t x1 = lower_bound;
    Float_t x3 = upper_bound;
    Float_t midpoint = 0.5 * ( lower_bound + upper_bound );

    Float_t numKeepx1 = numRndmFlag * x1;
    Float_t numKeepx2 = numRndmFlag * midpoint;
    Float_t numKeepx3 = numRndmFlag * x3;

    Float_t cellX1Thresh = computeThresh(zbCumulativeCellHist , numKeepx1);
    Float_t cellX2Thresh = computeThresh(zbCumulativeCellHist , numKeepx2);
    Float_t cellX3Thresh = computeThresh(zbCumulativeCellHist , numKeepx3);

    Float_t mhtX1Thresh = computeThresh(zbCumulativeMhtHist , numKeepx1);
    Float_t mhtX2Thresh = computeThresh(zbCumulativeMhtHist , numKeepx2);
    Float_t mhtX3Thresh = computeThresh(zbCumulativeMhtHist , numKeepx3);

    Float_t topoclX1Thresh = computeThresh(zbCumulativeTopoclHist , numKeepx1);
    Float_t topoclX2Thresh = computeThresh(zbCumulativeTopoclHist , numKeepx2);
    Float_t topoclX3Thresh = computeThresh(zbCumulativeTopoclHist , numKeepx3);

    Float_t topoclpsX1Thresh = computeThresh(zbCumulativeTopoclpsHist , numKeepx1);
    Float_t topoclpsX2Thresh = computeThresh(zbCumulativeTopoclpsHist , numKeepx2);
    Float_t topoclpsX3Thresh = computeThresh(zbCumulativeTopoclpsHist , numKeepx3);

    Float_t topoclpucX1Thresh = computeThresh(zbCumulativeTopoclpucHist , numKeepx1);
    Float_t topoclpucX2Thresh = computeThresh(zbCumulativeTopoclpucHist , numKeepx2);
    Float_t topoclpucX3Thresh = computeThresh(zbCumulativeTopoclpucHist , numKeepx3);

    Int_t cellmhtx1counter = 0;
    Int_t cellmhtx2counter = 0;
    Int_t cellmhtx3counter = 0;

    Int_t celltopoclx1counter = 0;
    Int_t celltopoclx2counter = 0;
    Int_t celltopoclx3counter = 0;

    Int_t celltopoclpsx1counter = 0;
    Int_t celltopoclpsx2counter = 0;
    Int_t celltopoclpsx3counter = 0;

    Int_t mhttopoclpucx1counter = 0;
    Int_t mhttopoclpucx2counter = 0;
    Int_t mhttopoclpucx3counter = 0;

    for ( zbIterator = 0 ; zbIterator < zbNentries ; zbIterator++ )
    {

        //metcell and metmht
        if ( (metcell > cellX1Thresh) && (metmht > mhtX1Thresh) && (metl1 > 50.0) &&
        (passnoalgL1XE10>0.5 || passnoalgL1XE30>0.5 || passnoalgL1XE40>0.5 || passnoalgL1XE45>0.5) )
        {
            cellmhtx1counter++;
        }
        if ( (metcell > cellX2Thresh) && (metmht > mhtX2Thresh) && (metl1 > 50.0) &&
        (passnoalgL1XE10>0.5 || passnoalgL1XE30>0.5 || passnoalgL1XE40>0.5 || passnoalgL1XE45>0.5) )
        {
            cellmhtx2counter++;
        }
        if ( (metcell > cellX3Thresh) && (metmht > mhtX3Thresh) && (metl1 > 50.0) &&
        (passnoalgL1XE10>0.5 || passnoalgL1XE30>0.5 || passnoalgL1XE40>0.5 || passnoalgL1XE45>0.5) )
        {
            cellmhtx3counter++;
        }

        //metcell and mettopocl
        if ( (metcell > cellX1Thresh) && (mettopocl > topoclX1Thresh) && (metl1 > 50.0) &&
        (passnoalgL1XE10>0.5 || passnoalgL1XE30>0.5 || passnoalgL1XE40>0.5 || passnoalgL1XE45>0.5) )
        {
            celltopoclx1counter++;
        }
        if ( (metcell > cellX2Thresh) && (mettopocl > topoclX2Thresh) && (metl1 > 50.0) &&
        (passnoalgL1XE10>0.5 || passnoalgL1XE30>0.5 || passnoalgL1XE40>0.5 || passnoalgL1XE45>0.5) )
        {
            celltopoclx2counter++;
        }
        if ( (metcell > cellX3Thresh) && (mettopocl > topoclX3Thresh) && (metl1 > 50.0) &&
        (passnoalgL1XE10>0.5 || passnoalgL1XE30>0.5 || passnoalgL1XE40>0.5 || passnoalgL1XE45>0.5) )
        {
            celltopoclx3counter++;
        }

        //metcell and mettopoclps
        if ( (metcell > cellX1Thresh) && (mettopoclps > topoclpsX1Thresh) && (metl1 > 50.0) &&
        (passnoalgL1XE10>0.5 || passnoalgL1XE30>0.5 || passnoalgL1XE40>0.5 || passnoalgL1XE45>0.5) )
        {
            celltopoclpsx1counter++;
        }
        if ( (metcell > cellX2Thresh) && (mettopoclps > topoclpsX2Thresh) && (metl1 > 50.0) &&
        (passnoalgL1XE10>0.5 || passnoalgL1XE30>0.5 || passnoalgL1XE40>0.5 || passnoalgL1XE45>0.5) )
        {
            celltopoclpsx2counter++;
        }
        if ( (metcell > cellX3Thresh) && (mettopoclps > topoclpsX3Thresh) && (metl1 > 50.0) &&
        (passnoalgL1XE10>0.5 || passnoalgL1XE30>0.5 || passnoalgL1XE40>0.5 || passnoalgL1XE45>0.5) )
        {
            celltopoclpsx3counter++;
        }

        //metmht and mettopoclpuc
        if ( (metmht > mhtX1Thresh) && (mettopoclpuc > topoclpucX1Thresh) && (metl1 > 50.0) &&
        (passnoalgL1XE10>0.5 || passnoalgL1XE30>0.5 || passnoalgL1XE40>0.5 || passnoalgL1XE45>0.5) )
        {
            mhttopoclpucx1counter++;
        }
        if ( (metmht > mhtX2Thresh) && (mettopoclpuc > topoclpucX2Thresh) && (metl1 > 50.0) &&
        (passnoalgL1XE10>0.5 || passnoalgL1XE30>0.5 || passnoalgL1XE40>0.5 || passnoalgL1XE45>0.5) )
        {
            mhttopoclpucx2counter++;
        }
        if ( (metmht > mhtX3Thresh) && (mettopoclpuc > topoclpucX3Thresh) && (metl1 > 50.0) &&
        (passnoalgL1XE10>0.5 || passnoalgL1XE30>0.5 || passnoalgL1XE40>0.5 || passnoalgL1XE45>0.5) )
        {
            mhttopoclpucx3counter++;
        }
    }

    Float_t cellmhtf1 = cellmhtx1counter / numRndmFlag;
    Float_t cellmhtf2 = cellmhtx2counter / numRndmFlag;
    Float_t cellmhtf3 = cellmhtx3counter / numRndmFlag;

    Float_t celltopoclf1 = celltopoclx1counter / numRndmFlag;
    Float_t celltopoclf2 = celltopoclx2counter / numRndmFlag;
    Float_t celltopoclf3 = celltopoclx3counter / numRndmFlag;

    Float_t celltopoclpsf1 = celltopoclpsx1counter / numRndmFlag;
    Float_t celltopoclpsf2 = celltopoclpsx2counter / numRndmFlag;
    Float_t celltopoclpsf3 = celltopoclpsx3counter / numRndmFlag;

    Float_t mhttopoclpucf1 = mhttopoclpucx1counter / numRndmFlag;
    Float_t mhttopoclpucf2 = mhttopoclpucx2counter / numRndmFlag;
    Float_t mhttopoclpucf3 = mhttopoclpucx3counter / numRndmFlag;


    Int_t iterator = 0;
    do{
        iterator++;
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





}

Float_t computeThresh(TH1F* cumulativeHist, Float_t numKeep)
{
    Int_t nbin = 0;
    gROOT->ProcessLine("gROOT->Reset();");
    cumulativeHist->GetBinWithContent(numKeep,nbin,0,-1,20000); //if firstx<=0{firstx=1}; if lastx<firstx{lastx=fXaxis.GetNbinsX()};
    Float_t thresh = (cumulativeHist->GetXaxis())->GetBinCenter(nbin);
    return(thresh);
}
