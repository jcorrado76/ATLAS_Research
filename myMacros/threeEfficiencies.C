#include <iostream>
#include <fstream>
#include "TMath.h"
#include "TH1.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TEfficiency.h"
#include "TLegend.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TF1.h"
#include "TBenchmark.h"
#include "TNtuple.h"
#include <TParameter.h>
#include "TList.h"
#include "TBranch.h"
#include "TObjString.h"

struct userInfo {
    TString algAName;
    TString algBName;
    Int_t nbins;
    Float_t metmin;
    Float_t metmax;
    Float_t metl1thresh;
    Float_t frac;
    TString zbFileName;
    TString muonFileName;
    Int_t numzbRndm;
    Float_t algAThresh;
    Float_t algBThresh;
    Int_t muonNentries;
    Int_t zbNentries;
    Int_t numPassMuon;
    Int_t numMuonKeptCombined;

    Int_t numMuonPassNumeratorAlgA;
    Int_t numMuonPassNumeratorAlgB;
    Int_t numMuonPassNumeratorAlgC;
    Int_t numMuonDenominator;
    Float_t eps;

}


/*
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
logFile << "Epsilon tolerance for bisection accuracy: " << eps << " events" << "\r\n";
*/

TFile* threeEfficiencies( const TString& algA , const TString& algB,
        const Float_t frac = 0.00590, const TString folder = "",
        const TString& zerobiasFileName = "PhysicsMain.All.noalgXEtriggers.2016.f731f758._m1659m1710.48Runs.root",
        const TString& muonFilename = "PhysicsMain.L1KFmuontriggers.2016.f731f758_m1659m1710.Run309759.48Runs.root")
{
    /*
    This macro basically will take 2 algorithms, and it generate the combined efficiency curve
    between them needed to keep the proper amount of events, such that they individually keep the same
    fraction of events.
    In addition, generates a root file with all of the statistics.
    */


    gROOT->ProcessLine("gSystem->Load(\"./mincerMacros_C.so\")");
    gROOT->ProcessLine("gSystem->Load(\"./bisection_C.so\")");
    Float_t passTransverseMassCut( const Float_t , const Float_t ,const Float_t ,const Float_t ,const Float_t ,const Float_t);
    Float_t determineZeroBiasThresh( const TString&, const Float_t, const TString&);
    Float_t computeThresh( const TH1F*, const Float_t);
    Float_t determineMuonEventsKeptCombined( const TString&, const Float_t, const TString&,
        const Float_t,const TString& );

    //user defined struct to store all log data
    userInfo logFileParams;

    //initialize TBenchmark for this macro
    TBenchmark* threeEfficienciesBenchmark = new TBenchmark();
    //start the clock running for total time
    threeEfficienciesBenchmark->Start("Three Efficiencies");

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

    //start timer on zerobias determination of thresholds
    threeEfficienciesBenchmark->Start("ZeroBias Thresholds");

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

    Float_t binWidth = (metMax - metMin)/ nbins;

    //the individual fraction needed such that when both algs constrained to keep the same fraction individually,
    //keep the proper amount when combined

    Float_t bisectionIndividFrac;
    Float_t individAThreshFinal;
    FLoat_t individBThreshFinal;


    TNtuple* logFileData = new TNtuple("logFileData" , "Bisection Data" , "Individual Fraction:Combined Fraction: Numb Events Kept: Threshold A:Threshold B");

    //start bisection timer
    threeEfficienciesBenchmark->Start("Bisection");

    //run BISECTION
    bisectionIndividFrac = bisection( algAMETHist , algBMETHist, binWidth, numZeroBiasRndm , frac ,
    logFileData,
    individAThreshFinal, individBThreshFinal, zeroBiasTree);

    //end bisection timer
    threeEfficienciesBenchmark->Show("Bisection");

    //END ZEROBIAS TIMER
    threeEfficienciesBenchmark->Show("ZeroBias Thresholds");


    TString cstring = algA + " > " + Form(" %.2f", individAThreshFinal) + " and " + algB + " > " + Form(" %.2f", individBThreshFinal);
    TString astring = algA + " > " + Form(" %.2f", algAThresh);
    TString bstring = algB + " > " + Form(" %.2f", algBThresh);
    TString dstring = (TString) "L1 > " + Form(" %.2f" , metl1thresh);

    TEfficiency* Ateff  = new TEfficiency(astring , "Efficiency", muonNbins, muonMetMin, muonMetMax);
    TEfficiency* Bteff  = new TEfficiency(bstring , "Efficiency", muonNbins, muonMetMin, muonMetMax);
    TEfficiency* Cteff  = new TEfficiency(cstring,  "Efficiency", muonNbins, muonMetMin, muonMetMax);
    TEfficiency* Dteff  = new TEfficiency(dstring,  "Efficiency", muonNbins, muonMetMin, muonMetMax);//combined just L1 cut, 0 on others

    threeEfficienciesBenchmark->Start("Fill Muon TEfficiencies");

    Float_t algAmuonMET = 0;
    Float_t algBmuonMET = 0;
    Float_t muonMetl1 = 0;
    myMuonTree->SetBranchAddress(algA,&algAmuonMET);
    myMuonTree->SetBranchAddress(algB,&algBmuonMET);
    myMuonTree->SetBranchAddress("metl1",&muonMetl1);
    Int_t numbPassMuon = 0;Float_t wValue;
    //TODO: add in actint > 35.0 in the numerator and denominator
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


    threeEfficienciesBenchmark->Show("Fill Muon TEfficiencies");

    //TODO: write efficiencies and canvas to a root file
    //TODO: handle the case if there is already a root file with same name
    TString fileName = algA + "_" + algB + " efficiencies.root";
    TFile myFile = new TFile(fileName,"RECREATE");

    const TString canvName = algA + " and " + algB + " Combined Efficiency" + ";Offline Recalibrated MET w/o Muon term [GeV];Efficiency";

    TCanvas* efficiencyCanvas = new TCanvas("Efficiency Canvas", "Efficiency Canvas");

    efficiencyCanvas->RangeAxis(0,0,500,1.0);

    Ateff->SetTitle(canvName);

    Ateff->SetLineColor(kBlue);
    Cteff->SetLineColor(kRed);
    Bteff->SetLineColor(kGreen);
    Dteff->SetLineColor(kBlack);

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


    //write efficiencies to the root file
    Ateff->Write( algA + " TEfficiency" );
    Bteff->Write( algB + " TEfficiency" );
    Cteff->Write( algC + " TEfficiency" );
    Dteff->Write( algD + " TEfficiency" );

    //make a tiff picture of the efficiency canvas just in case
    TString folderPath = "./TEfficienciesPics/" + folder + "-" +  algA + "_and_" + algB + "_efficiencies.tiff";
    efficiencyCanvas->Print(folderPath);
    //write canvas to the root file
    efficiencyCanvas->Write("Efficiency Cavnas");


    //TODO: Figure out how to add the numerical data to the logTTree
    //TODO: fill param data into the user info struct
    //TODO: write TTree to the logfile
    TTree* logFileTree = new TTree("tree" , "Log File Tree");
    //adds the log file data struct containing information on all parameters
    logFilTree->GetUserInfo()->Add(logFileParams);


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

    //end the three efficiencies benchmark
    threeEfficienciesBenchmark->Show("Three Efficiencies");
    //show the summary and totals of all benchmarks
    threeEfficienciesBenchmark->Summary();
    return( myFile );
    }
