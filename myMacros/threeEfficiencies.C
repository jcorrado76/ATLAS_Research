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
#include "TF1.h"
#include "TBenchmark.h"
#include "TNtuple.h"
#include "userInfo.h"

TFile* threeEfficiencies( const TString& algA , const TString& algB,
        const Float_t frac = 0.00590, const TString folder = "" )
{
    /*
    This macro basically will take 2 algorithms, and it generate the combined efficiency curve
    between them needed to keep the proper amount of events, such that they individually keep the same
    fraction of events.
    In addition, generates a root file with all of the statistics.
    */

    gROOT->ProcessLine("gSystem->Load(\"./mincerMacros_C.so\")");
    gROOT->ProcessLine("gSystem->Load(\"./bisection_C.so\")");

    Bool_t passTransverseMassCut( const Float_t , const Float_t ,const Float_t ,const Float_t ,const Float_t ,const Float_t);
    Float_t determineZeroBiasThresh( const TString&, const Float_t);
    Float_t computeThresh( const TH1F*, const Float_t);
    Float_t determineMuonEventsKeptCombined( const TString&, const Float_t, const TString&,
        const Float_t,const TString& );
    Float_t bisection(TH1F* , TH1F* , const Float_t , Float_t& , Float_t&  , const Int_t, Float_t , TNtuple* ,TTree* );
    Float_t computeMetNoMu( const Float_t , const Float_t , const Float_t , const Float_t );

    //INITIALIZE PARAMS
    //HERE IS THE ONE AND TRUE DEFINITION
    userInfo* logFileParams = new userInfo();
    logFileParams->Print();

    //FILES
    TString zerobiasFileName = logFileParams->get_zbFileName();
    TString muonFilename = logFileParams->get_muonFileName();

    //THREEFF BENCHMARK
    TBenchmark* threeEfficienciesBenchmark = new TBenchmark();

    //TOTAL TIMER
    threeEfficienciesBenchmark->Start("Three Efficiencies");

    //MUON FILE; MUON TREE
    TString muonFilePath = "../myData/"+muonFilename;
    TFile * muonFile = TFile::Open(muonFilePath, "READ");
    TTree* myMuonTree = (TTree*)muonFile->Get("tree");

    std::cout << "Muon Data being used to compute algorithm efficiency: " << muonFilePath << std::endl;

    //initialize variables to be used later
    Float_t metl1thresh = logFileParams->getMetL1Thresh();
    Float_t actintCut = logFileParams->getActintCut();
    Int_t muonNentries = myMuonTree->GetEntries();
    Int_t muonNbins = 200;
    Int_t nbins = logFileParams->getNbins();
    Double_t metMin = logFileParams->getMetMin();
    Double_t metMax = logFileParams->getMetMax();
    Int_t NumberEventsProcess1ActintCutPassNoAlg = 0; Int_t counter1 = 0; Int_t counter2 = 0; Int_t counter3 = 0;

    Int_t passRndm, numPassMuon,passmuon,passmuvarmed,cleanCutsFlag,recalBrokeFlag;
    Float_t algAMET,algBMET,metoffrecal,mexoffrecal,meyoffrecal,mexoffrecalmuon, zb_actint,
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
    zeroBiasTree->SetBranchAddress("actint",&zb_actint);
    TH1F *algAMETHist = new TH1F(algA, "algA", nbins, metMin, metMax);
    TH1F *algBMETHist = new TH1F(algB, "algB", nbins, metMin, metMax);

    //start timer on zerobias determination of thresholds
    threeEfficienciesBenchmark->Start("ZeroBias Thresholds");

    //IN DETERMINE THRESH I COMPUTE THRESHOLD AFTER ALSO CUTTING ON METL1 TO MAKE HISTOGRAMS
    threeEfficienciesBenchmark->Start( "determine" + algA + "Thresh");
    Float_t algAThresh = determineZeroBiasThresh(algA,frac,zerobiasFileName);
    threeEfficienciesBenchmark->Show( "determine" + algA + "Thresh");
    std::cout << "\n" << std::endl;
    threeEfficienciesBenchmark->Start( "determine" + algB + "Thresh");
    Float_t algBThresh = determineZeroBiasThresh(algB,frac,zerobiasFileName);
    threeEfficienciesBenchmark->Show( "determine" + algB + "Thresh");
    std::cout << "\n" << std::endl;

    //FINISHED COMPUTING INDIVIDUAL THRESHOLDS; NOW DO THEM TOGETHER
    std::cout << "Returned to threeEfficiencies.C" << std::endl;
    std::cout << "algAThresh: " << algAThresh << std::endl;
    std::cout << "algBThresh: " << algBThresh << std::endl;
    std::cout << "Using METL1THRESH: " << metl1thresh << std::endl;

    //determine NumberEventsProcess1ActintCutPassNoAlg and fill histograms
    NumberEventsProcess1ActintCutPassNoAlg = 0 ;
	for (Int_t k = 0; k < zerobiasNentries; k++)
	{
	    zeroBiasTree->GetEntry(k);
	    if ( (metl1 > metl1thresh) && (zb_actint > actintCut) &&
         ( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 ||
        passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5  ))
	    {
    		algAMETHist->Fill(algAMET);
    		algBMETHist->Fill(algBMET);
            NumberEventsProcess1ActintCutPassNoAlg++;
	    }
	}

    Float_t binWidth = (metMax - metMin)/ nbins;

    //the individual fraction needed such that when both algs constrained to keep the same fraction individually,
    //keep the proper amount when combined

    Float_t bisectionIndividFrac;
    Float_t individAThreshFinal;
    Float_t individBThreshFinal;


    TNtuple* logFileData = new TNtuple("logFileData" , "Bisection Data" ,
    "Individual Fraction:Combined Fraction: Numb Events Kept:" + algA + " Threshold:" + algB + " Threshold");

    //start bisection timer
    threeEfficienciesBenchmark->Start("Bisection");

    //run BISECTION
    bisectionIndividFrac = bisection( algAMETHist , algBMETHist, binWidth, individAThreshFinal,
    individBThreshFinal, NumberEventsProcess1ActintCutPassNoAlg , frac ,
    logFileData,zeroBiasTree);

    //end bisection timer
    threeEfficienciesBenchmark->Show("Bisection");

    //END ZEROBIAS TIMER
    threeEfficienciesBenchmark->Show("ZeroBias Thresholds");


    TString cstring = algA + " > " + Form(" %.2f", individAThreshFinal) + " and " + algB + " > " + Form(" %.2f", individBThreshFinal);
    TString astring = algA + " > " + Form(" %.2f", algAThresh);
    TString bstring = algB + " > " + Form(" %.2f", algBThresh);
    TString dstring = (TString) "L1 > " + Form(" %.2f" , metl1thresh);

    TEfficiency* Ateff  = new TEfficiency(astring , "Efficiency", muonNbins, metMin, metMax);
    TEfficiency* Bteff  = new TEfficiency(bstring , "Efficiency", muonNbins, metMin, metMax);
    TEfficiency* Cteff  = new TEfficiency(cstring,  "Efficiency", muonNbins, metMin, metMax);
    TEfficiency* Dteff  = new TEfficiency(dstring,  "Efficiency", muonNbins, metMin, metMax);//combined just L1 cut, 0 on others

    threeEfficienciesBenchmark->Start("Fill TEfficiencies");

    Float_t algAmuonMET = 0;
    Float_t algBmuonMET = 0;
    Float_t muonMetl1 = 0;
    Float_t muonActint = 0;
    myMuonTree->SetBranchAddress(algA,&algAmuonMET);
    myMuonTree->SetBranchAddress(algB,&algBmuonMET);
    myMuonTree->SetBranchAddress("metl1",&muonMetl1);
    myMuonTree->SetBranchAddress("actint", &muonActint);

    std::cout << "Starting to fill TEfficiencies.." << std::endl;

    Bool_t isMuon;
    Bool_t isClean;
    for (Int_t l = 0 ; l < muonNentries ; l++)
    {
        myMuonTree->GetEntry(l);
        isMuon = (passmuvarmed > 0.1 || passmuon > 0.1);
        isClean = (cleanCutsFlag > 0.1) && (recalBrokeFlag < 0.1);

        if ( isMuon && isClean && ( muonActint > actintCut ))
    	{
            if ( passTransverseMassCut(metoffrecal,mexoffrecal,meyoffrecal,metoffrecalmuon,mexoffrecalmuon,meyoffrecalmuon) )
            {
        	    Float_t metnomu = computeMetNoMu(  mexoffrecal , meyoffrecal , mexoffrecalmuon , meyoffrecalmuon );

                Ateff->Fill((algAmuonMET > algAThresh) && (muonMetl1 > metl1thresh) && ( muonActint > actintCut ), metnomu);
        	    Bteff->Fill((algBmuonMET > algBThresh) && (muonMetl1 > metl1thresh)&& ( muonActint > actintCut ), metnomu);
        	    Cteff->Fill(((algAmuonMET > individAThreshFinal) && (algBmuonMET > individBThreshFinal)
                && ( muonActint > actintCut )&& (muonMetl1 > metl1thresh)), metnomu);
                Dteff->Fill((muonMetl1 >= metl1thresh) && ( muonActint > actintCut ), metnomu);
            }
    	}
    }


    threeEfficienciesBenchmark->Show("Fill TEfficiencies");

    const TString canvName = algA + " and " + algB + " Combined Efficiency" + ";Offline Recalibrated MET w/o Muon term [GeV];Efficiency";

    TCanvas* efficiencyCanvas = new TCanvas("Efficiency Canvas", "Efficiency Canvas");

    efficiencyCanvas->RangeAxis(0,0,500,1.0);

    efficiencyCanvas->SetTitle(canvName);

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

    //compute number muon events actually kept using external macro
    Int_t muonEventsCombined = determineMuonEventsKeptCombined( algA, individAThreshFinal , algB , individBThreshFinal , muonFilename );

    logFileParams->setNum_zbRndm( NumberEventsProcess1ActintCutPassNoAlg );
    logFileParams->setAlgAThresh( algAThresh);
    logFileParams->setAlgBThresh( algBThresh );
    logFileParams->setMuonNentries( muonNentries );
    logFileParams->set_zbNentries( zerobiasNentries );
    logFileParams->setNumMuonKeptCombined( muonEventsCombined );
    logFileParams->setNumPassA((Ateff->GetPassedHistogram())->GetEntries());
    logFileParams->setNumPassB((Bteff->GetPassedHistogram())->GetEntries());
    logFileParams->setNumPassCombined((Cteff->GetPassedHistogram())->GetEntries());
    logFileParams->setNumTotal((Ateff->GetTotalHistogram())->GetEntries());
    logFileParams->setActintCut(actintCut);
    logFileParams->setAlgAName(algA);
    logFileParams->setAlgBName(algB);

    TString fileName = "./TEfficienciesPics/" + folder + "/" + algA + "_" + algB + "Efficiencies.root";
    //if file already exists, not opened
    TFile* rootFile = new TFile(fileName,"CREATE");

    //TODO: add filehandling to use one root file for a given combination, and have it create subfolders within the root file to
    //store different runs
    if ( !( rootFile->IsOpen() ) )
        {
            TString suffix = "";
            std::cout << "Unable to open file" << std::endl;
            std::cout << "Enter run number: ";
            std::cin >> suffix;
            suffix = "(" + suffix + ")";
            fileName.Insert( (fileName.Length()-5),suffix);
            //try again, but this time if user inputs, can overwrite
            rootFile->Open( fileName ,"RECREATE");
        }

    std::cout << "Root file successfully opened" << std::endl;

    Ateff->Write( astring );
    Bteff->Write( bstring );
    Cteff->Write( cstring );
    Dteff->Write( "METL1" );
    logFileData->Write("bisectionData");
    efficiencyCanvas->Write("efficiencyCanvas");
    logFileParams->Print();
    logFileParams->Write("parameters");
    threeEfficienciesBenchmark->Stop("Three Efficiencies");

    //show the summary and totals of all benchmarks
    Float_t realtime, cputime;
    threeEfficienciesBenchmark->Summary(realtime ,cputime);

    rootFile->Close();

    return( rootFile );
    }
