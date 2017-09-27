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


//TODO: make this function return the .root TFile* handle to pass to generate efficiencies, so I can put all the root files
//from several threeEfficiencies runs into a single root file, separated by folders

Int_t threeEfficiencies( const TString& algA , const TString& algB,
        const Float_t frac = 0.00590, const TString folder = "",
        const TString& zerobiasFileName = "PhysicsMain.All.noalgXEtriggers.2016.f731f758._m1659m1710.48Runs.root",
        const TString& muonFilename = "PhysicsMain.L1KFmuontriggers.2016.f731f758_m1659m1710.Run309759.48Runs.root")
{
    gROOT->ProcessLine("gSystem->Load(\"./mincerMacros_C.so\")");
    Float_t passTransverseMassCut( const Float_t , const Float_t ,const Float_t ,const Float_t ,const Float_t ,const Float_t);
    Float_t determineZeroBiasThresh( const TString&, const Float_t, const TString&);
    Float_t computeThresh( const TH1F*, const Float_t);
    Float_t determineMuonEventsKeptCombined( const TString&, const Float_t, const TString&,
        const Float_t,const TString& );

    gROOT->ProcessLine("gROOT->Time();");


    //first, open the muon file and get the muon tree
    TString muonFilePath = "../myData/"+muonFilename;
    TFile * muonFile = TFile::Open(muonFilePath, "READ");
    TTree* myMuonTree = (TTree*)muonFile->Get("tree");

    std::cout << "Muon Data being used to compute algorithm efficiency: " << muonFilePath << std::endl;

    //initialize variables to be used later
    Float_t metl1thresh = 50.0;
    Int_t muonNentries = myMuonTree->GetEntries();
    Int_t muonNbins = 200;
    Int_t nbins = 1200;
    Double_t muonMetMin = 0.0;
    Double_t muonMetMax = 300.0;
    Int_t numZeroBiasRndm = 0; Int_t counter1 = 0; Int_t counter2 = 0; Int_t counter3 = 0;

    Double_t metMin = 0.0; Double_t metMax = muonMetMax;

    Int_t passRndm, numPassMuon,passmuon,passmuvarmed,cleanCutsFlag,recalBrokeFlag;
    Float_t algAMET,algBMET,metoffrecal,mexoffrecal,meyoffrecal,mexoffrecalmuon,
            meyoffrecalmuon, metl1,metcell,metrefmuon,mexrefmuon,meyrefmuon,metoffrecalmuon;
    Int_t passnoalgL1XE10,passnoalgL1XE30,passnoalgL1XE40,passnoalgL1XE45;

    myMuonTree->SetBranchAddress("passmu26med", &passmuon);
    myMuonTree->SetBranchAddress("passmu26varmed", &passmuvarmed);
    myMuonTree->SetBranchAddress("passcleancuts", &cleanCutsFlag);
    myMuonTree->SetBranchAddress("recalbroke", &recalBrokeFlag);
    myMuonTree->SetBranchAddress("metoffrecal", &metoffrecal);
    myMuonTree->SetBranchAddress("mexoffrecal", &mexoffrecal);
    myMuonTree->SetBranchAddress("meyoffrecal", &meyoffrecal);
    myMuonTree->SetBranchAddress("metoffrecalmuon", &metoffrecalmuon);
    myMuonTree->SetBranchAddress("mexoffrecalmuon", &mexoffrecalmuon);
    myMuonTree->SetBranchAddress("meyoffrecalmuon", &meyoffrecalmuon);
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
    std::cout << "Using METL1THRESH: " << metl1thresh << std::endl;

    //determine numZeroBiasRndm and fill histograms
    numZeroBiasRndm = 0 ;
	for (Int_t k = 0; k < zerobiasNentries; k++)
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

    Float_t inputArray[100];
    Float_t outputArray[100];
    Float_t numEventsArray[100];
    Float_t thresholdAarray[100];
    Float_t thresholdBarray[100];

    Float_t binWidth = (metMax - metMin)/ nbins;

    //the individual fraction needed such that when both algs constrained to keep the same fraction individually,
    //keep the proper amount when combined

    Float_t bisectionIndividFrac;
    Float_t individAThreshFinal;
    FLoat_t individBThreshFinal;

    //TODO: make a TBenchmark here for "bisection"
    //TODO: finish writing bisection in mincerMacros, and use it here for encapsulation




    bisectionIndividFrac = bisection( algAMETHist , algBMETHist, binWidth, numZeroBiasRndm , frac ,
    inputArray , outputArray ,numEventsArray ,thresholdAarray ,thresholdBarray,
    individAThreshFinal, individBThreshFinal );


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
    	for (Int_t i  = 0 ; i < zerobiasNentries ;i++)
    	{
    	  zeroBiasTree->GetEntry(i);
    	  if ((algAMET > algAMETx2thresh) && (algBMET > algBMETx2thresh) && (metl1 > metl1thresh)&& ( passnoalgL1XE10 > 0.5 ||
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


    //END ZEROBIAS


    individAThreshFinal = algAMETx2thresh;
    individBThreshFinal = algBMETx2thresh;

    TString cstring = algA + " > " + Form(" %.2f", individAThreshFinal) + " and " + algB + " > " + Form(" %.2f", individBThreshFinal);
    TString astring = algA + " > " + Form(" %.2f", algAThresh);
    TString bstring = algB + " > " + Form(" %.2f", algBThresh);
    TString dstring = (TString) "L1 > " + Form(" %.2f" , metl1thresh);

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
    Int_t numbPassMuon = 0;Float_t wValue;
    for (Int_t l = 0 ; l < muonNentries ; l++)
    {
        myMuonTree->GetEntry(l);
        if ((passmuvarmed > 0.1 || passmuon > 0.1) && (cleanCutsFlag > 0.1) && (recalBrokeFlag < 0.1))
    	{
            if ( passTransverseMassCut(metoffrecal,mexoffrecal,meyoffrecal,metoffrecalmuon,mexoffrecalmuon,meyoffrecalmuon) )
            {
        	    Float_t metnomu = sqrt(((mexoffrecal - mexoffrecalmuon) * (mexoffrecal - mexoffrecalmuon)) +
        	    ((meyoffrecal - meyoffrecalmuon)*(meyoffrecal - meyoffrecalmuon))); //compute metnomu
                numbPassMuon++;
                Ateff->Fill((algAmuonMET > algAThresh) && (muonMetl1 > metl1thresh), metnomu);
        	    Bteff->Fill((algBmuonMET > algBThresh) && (muonMetl1 > metl1thresh), metnomu);
        	    Cteff->Fill(((algAmuonMET > individAThreshFinal) && (algBmuonMET > individBThreshFinal) && (muonMetl1 > metl1thresh)), metnomu);
                Dteff->Fill((muonMetl1 >= metl1thresh), metnomu);
            }
    	}
    }


    //TODO: write all efficiencies to a root file
    std::cout << "NUMB MUON ENTRIES PASSED ALG A: " << (Ateff->GetPassedHistogram())->GetEntries() << std::endl;
    std::cout << "NUMB MUON ENTRIES PASSED ALG B: " << (Bteff->GetPassedHistogram())->GetEntries() << std::endl;
    std::cout << "NUMB MUON ENTRIES PASSED ALG C: " << (Cteff->GetPassedHistogram())->GetEntries() << std::endl;
    std::cout << "NUMB MUON ENTRIES TOTAL  ALG A: " << (Ateff->GetTotalHistogram())->GetEntries() << std::endl;
    std::cout << "NUMB MUON ENTRIES TOTAL  ALG B: " << (Bteff->GetTotalHistogram())->GetEntries() << std::endl;
    std::cout << "NUMB MUON ENTRIES TOTAL  ALG C: " << (Cteff->GetTotalHistogram())->GetEntries() << std::endl;
    std::cout << "Running determineMuonEventsKeptCombined.C to check number of MUON events kept at fraction determined by the bisection algorithm..." << std::endl;
    Float_t muonEventsCombined = determineMuonEventsKeptCombined( algA , individAThreshFinal , algB , individBThreshFinal, muonFilename );

    TCanvas* efficiencyCanvas = new TCanvas("Efficiency Canvas", "Efficiency Canvas");
    efficiencyCanvas->RangeAxis(0,0,500,1.0);

        Ateff->SetLineColor(kBlue);
        Cteff->SetLineColor(kRed);
        Bteff->SetLineColor(kGreen);
        Dteff->SetLineColor(kBlack);

    const TString canvName = algA + " and " + algB + " Combined Efficiency" + ";Offline Recalibrated MET w/o Muon term [GeV];Efficiency";

    Ateff->SetTitle(canvName);

    Ateff->Draw();
    Bteff->Draw("same");
    Cteff->Draw("same");
    Dteff->Draw("same");



    TLegend *legend = new TLegend(0.57,0.15,0.9, 0.4 ,"","NDC");
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

    //TODO: write logfile to the same root file
    logFile.open(newLogFileName, std::fstream::out);
    if(logFile) std::cout << "logFile Successfully Opened" << std::endl;

    logFile << "Algorithms: " << algA << "\t" << algB << "\r\n";
    logFile << "Nbins: " << nbins << "\t METMIN: " << metMin << "\t METMAX: " << metMax << "\r\n";
    logFile << "METL1 THRESH: " << metl1thresh << "\r\n";
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
