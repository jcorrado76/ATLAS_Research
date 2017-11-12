#include "mincerMacros.h"


TFile* threeEfficiencies( const TString& algA , const TString& algB,
        const Float_t frac = 0.00590, const TString folder = "" )
{

    //GLOBAL DEFINITION 
    userInfo* parameters = new userInfo();
    parameters->Print();

    //FILES
    TString zerobiasFileName = parameters->get_passnoalgFileName();
    TString muonFilename = parameters->get_muonFileName();

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
    Float_t metl1thresh = parameters->getMetL1Thresh();
    Float_t actintCut = parameters->getActintCut();
    Int_t muonNentries = myMuonTree->GetEntries();
    Int_t muonNbins = 200;
    Int_t nbins = parameters->getNbins();
    Double_t metMin = parameters->getMetMin();
    Double_t metMax = parameters->getMetMax();
    Int_t NumbPassnoAlgPassProcess1WithActintCut = 0; Int_t counter1 = 0; Int_t counter2 = 0; Int_t counter3 = 0;
  //initialize some more variables
    Int_t passRndm, numPassMuon,passmuon,passmuvarmed,cleanCutsFlag,recalBrokeFlag;
    Float_t algAMET,algBMET,metoffrecal,mexoffrecal,meyoffrecal,mexoffrecalmuon, zb_actint,
            meyoffrecalmuon, metl1,metcell,metrefmuon,mexrefmuon,meyrefmuon,metoffrecalmuon;
    Int_t passnoalgL1XE10,passnoalgL1XE30,passnoalgL1XE40,passnoalgL1XE45;
  //initialize branch addresses to the local variables
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


    //ZBTREE
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
    Int_t numPassnoalgPassProcess1AlgA=0;
       
    Float_t algAThresh = determineZeroBiasThresh(algA,numPassnoalgPassProcess1AlgA,frac,zerobiasFileName);

    threeEfficienciesBenchmark->Show( "determine" + algA + "Thresh");
    std::cout << "\n" << std::endl;

    threeEfficienciesBenchmark->Start( "determine" + algB + "Thresh");
    Int_t numPassnoalgPassProcess1AlgB;
    Float_t algBThresh = determineZeroBiasThresh(algB,numPassnoalgPassProcess1AlgB,frac,zerobiasFileName);
    threeEfficienciesBenchmark->Show( "determine" + algB + "Thresh");
    std::cout << "\n" << std::endl;


    std::cout << "AlgAThresh: " << algAThresh << std::endl;
    std::cout << "AlgBThresh: " << algBThresh << std::endl;
    //FINISHED COMPUTING INDIVIDUAL THRESHOLDS; NOW DO THEM TOGETHER
    std::cout << "Returned to threeEfficiencies.C" << std::endl;
    std::cout << "algAThresh: " << algAThresh << std::endl;
    std::cout << "algBThresh: " << algBThresh << std::endl;
    std::cout << "Using METL1THRESH: " << metl1thresh << std::endl;

    //determine NumbPassnoAlgPassProcess1WithActintCut and fill histograms
    //TODO: determineZeroBias thresh actually does this, try to pass it around to not have to do it
    //again
    NumbPassnoAlgPassProcess1WithActintCut = 0 ;
	for (Int_t k = 0; k < zerobiasNentries; k++)
	{
	    zeroBiasTree->GetEntry(k);
	    if ( (metl1 > metl1thresh) && (zb_actint > actintCut) &&
         ( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 ||
        passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5  ))
	    {
    		algAMETHist->Fill(algAMET);
    		algBMETHist->Fill(algBMET);
            NumbPassnoAlgPassProcess1WithActintCut++;
	    }
	}

    Float_t binWidth = (metMax - metMin)/ nbins;

    //the individual fraction needed such that when both algs constrained to keep the same fraction individually,
    //keep the proper amount when combined

    Float_t bisectionIndividFrac;
    Float_t CombinedThreshAlgA;
    Float_t CombinedThreshAlgB;


    TNtuple* logFileData = new TNtuple("logFileData" , "Bisection Data" ,
    "Individual Fraction:Combined Fraction: Numb Events Kept:" + algA + " Threshold:" + algB + " Threshold");

    //start bisection timer
    threeEfficienciesBenchmark->Start("Bisection");

    //run BISECTION
    bisectionIndividFrac = bisection( algAMETHist , algBMETHist, binWidth, CombinedThreshAlgA,
    CombinedThreshAlgB, NumbPassnoAlgPassProcess1WithActintCut , frac ,
    logFileData,zeroBiasTree);

    //end bisection timer
    threeEfficienciesBenchmark->Show("Bisection");

    //END ZEROBIAS TIMER
    threeEfficienciesBenchmark->Show("ZeroBias Thresholds");


    TString cstring = algA + " > " + Form(" %.2f", CombinedThreshAlgA) + " and " + algB + " > " + Form(" %.2f", CombinedThreshAlgB);
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

    Int_t NumMuonPassProcess1WithActintCut = 0 ;

    Bool_t isMuon;
    Bool_t isClean;
    for (Int_t l = 0 ; l < muonNentries ; l++)
    {
        myMuonTree->GetEntry(l);
        isMuon = (passmuvarmed > 0.1 || passmuon > 0.1);
        isClean = (cleanCutsFlag > 0.1) && (recalBrokeFlag < 0.1);

        if ( isMuon && isClean && muonMetl1 > metl1thresh)
        {
            NumMuonPassProcess1WithActintCut++;
        }


        if ( isMuon && isClean && ( muonActint > actintCut ))
    	{
            if ( passTransverseMassCut(metoffrecal,mexoffrecal,meyoffrecal,metoffrecalmuon,mexoffrecalmuon,meyoffrecalmuon) )
            {
        	    Float_t metnomu = computeMetNoMu(  mexoffrecal , meyoffrecal , mexoffrecalmuon , meyoffrecalmuon );

                Ateff->Fill((algAmuonMET > algAThresh) && (muonMetl1 > metl1thresh) && ( muonActint > actintCut ), metnomu);
        	    Bteff->Fill((algBmuonMET > algBThresh) && (muonMetl1 > metl1thresh)&& ( muonActint > actintCut ), metnomu);
        	    Cteff->Fill(((algAmuonMET > CombinedThreshAlgA) && (algBmuonMET > CombinedThreshAlgB)
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
    Int_t muonEventsCombined = determineMuonEventsKeptCombined( algA, CombinedThreshAlgA , algB , CombinedThreshAlgB , muonFilename );

    parameters->setNumPassNoAlgPassProcess1( NumbPassnoAlgPassProcess1WithActintCut );
    parameters->setNumMuonPassProcess1( NumMuonPassProcess1WithActintCut );

    Int_t NumberMuonEventsProcess2CombinedActintCut = (Cteff->GetPassedHistogram())->GetEntries() ;
    Int_t NumberMuonEventsProcess2AlgAActintCut = (Ateff->GetPassedHistogram())->GetEntries() ;
    Int_t NumberMuonEventsProcess2AlgBActintCut = (Bteff->GetPassedHistogram())->GetEntries() ;

    parameters->setNumMuonPassProcess2Combined( NumberMuonEventsProcess2CombinedActintCut);
    parameters->setNumMuonPassProcess2AlgA( NumberMuonEventsProcess2AlgAActintCut);
    parameters->setNumMuonPassProcess2AlgB( NumberMuonEventsProcess2AlgBActintCut);

    parameters->setNumPassNoAlgPassProcess2Combined( NumberMuonEventsProcess2CombinedActintCut);
    //TODO: pass numPassnoalgPassProcess2AlgA from determinezerobiasthresh to set it here
    //parameters->setNumPassNoAlgPassProcess2AlgA( numPassnoalgPassProcess2AlgA);
    //parameters->setNumPassNoAlgPassProcess2AlgB( numPassnoalgPassProcess2AlgB);

    parameters->setAlgAIndividThresh( algAThresh);
    parameters->setAlgBIndividThresh( algBThresh );
    parameters->setAlgACombinedThresh( CombinedThreshAlgA);
    parameters->setAlgBCombinedThresh( CombinedThreshAlgB );


    parameters->setMuonNentries( muonNentries );
    parameters->set_PassnoalgNentries( zerobiasNentries );
    parameters->setNumMuonKeptCombinedAtThresh( muonEventsCombined );
    parameters->setNumTotal((Ateff->GetTotalHistogram())->GetEntries());
    parameters->setActintCut(actintCut);
    parameters->setAlgAName(algA);
    parameters->setAlgBName(algB);

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

    //print the canvas itself to a picture in the TEfficiencies pics folder
    efficiencyCanvas->Print("./pictures/" + folder + "/" + algA + "_" + algB + "_efficiencies.tiff");
    //write the TEfficiency objects to root file using the names as the key
    Ateff->Write( astring );
    Bteff->Write( bstring );
    Cteff->Write( cstring );
    Dteff->Write( "METL1" );
    logFileData->Write("bisectionData");
    efficiencyCanvas->Write("efficiencyCanvas");
    //display the values of parameters object 
    parameters->Print();
    parameters->Write("parameters");
    threeEfficienciesBenchmark->Stop("Three Efficiencies");
  
    //show the summary and totals of all benchmarks
    Float_t realtime, cputime;
    threeEfficienciesBenchmark->Summary(realtime ,cputime);

    rootFile->Close();

    return( rootFile );
    }
