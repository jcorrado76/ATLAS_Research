#include "mincerMacros.h"
#include "userInfo.h"
#include "ChainHandler.h"


// analysis class definition
class HLTEfficiencyAnalysis
{
public:
    //constructor
    HLTEfficiencyAnalysis(
        const TString& algA ,
        const TString& algB ,
        const bool verbose=false);

    //destructor
    ~HLTEfficiencyAnalysis();

private:
    //analysis methods
    void Begin();
    void End();
    void DoAnalysis();
    void DetermineThresholds();
    void AnalyzeMuon ();

    //data members
    userInfo* parameters;

    TEfficiency* Ateff;
    TEfficiency* Bteff;
    TEfficiency* Cteff;
    TEfficiency* Dteff;


};

//constructor definition
HLTEfficiencyAnalysis::HLTEfficiencyAnalysis()
{
    parameters = new userInfo();
    parameters->setAlgAName( algA );
    parameters->setAlgAName( algB );

    if (verbose)
    {
        std::cout << "[HLTEfficiencyAnalysis]" << std::endl;
        std::cout << "HLTAnalysis has been initialized with the following parameters:" << std::endl;
        parameters->Print();
    }
};


//destructor definition
HLTEfficiencyAnalysis::~HLTEfficiencyAnalysis()
{
    if (verbose)
    {
        std::cout << "HLTAnalysis finished." << std::endl;
    }
}


void HLTEfficiencyAnalysis::Begin()
{

    //TODO: all this stuff shouldn't be initialized here unless it is a private member variable, it won't
    //      survive the scope of this function


    //INITIALIZE
    Int_t muonNbins = 200;
    Float_t metl1thresh = logFileParams->getMetL1Thresh();
    Float_t actintCut = logFileParams->getActintCut();
    Int_t nbins = logFileParams->getNbins();
    Double_t metMin = logFileParams->getMetMin();
    Double_t metMax = logFileParams->getMetMax();
    TString xlabel = "MET [GeV]";
    TString yaxis = "Events";

    //SET ZB BRANCHES
    zeroBiasTree->SetBranchAddress("passrndm", &passRndm); // get pass rndm flag
    zeroBiasTree->SetBranchAddress(algA,&algAMET);
    zeroBiasTree->SetBranchAddress(algB,&algBMET);
    zeroBiasTree->SetBranchAddress("metl1",&metl1);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE10",&passnoalgL1XE10);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE30",&passnoalgL1XE30);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE40",&passnoalgL1XE40);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE45",&passnoalgL1XE45);
    zeroBiasTree->SetBranchAddress("actint",&zb_actint);

    //CREATE ZB INDIVID HISTS
    TH1F *algAMETHist = new TH1F(algA, "algA", nbins, metMin, metMax);
    TH1F *algBMETHist = new TH1F(algB, "algB", nbins, metMin, metMax);


    //SET MUON BRANCHES
    Float_t algAmuonMET = 0;
    Float_t algBmuonMET = 0;
    Float_t muonMetl1 = 0;
    Float_t muonActint = 0;
    Int_t NumMuonPassProcess1WithActintCut = 0 ;
    Bool_t isMuon;
    Bool_t isClean;
    myMuonTree->SetBranchAddress(algA,&algAmuonMET);
    myMuonTree->SetBranchAddress(algB,&algBmuonMET);
    myMuonTree->SetBranchAddress("metl1",&muonMetl1);
    myMuonTree->SetBranchAddress("actint", &muonActint);

    //INITIALIZE EFFICIENCIES
    TEfficiency* Ateff  = new TEfficiency(algA , "Efficiency", muonNbins, metMin, metMax);
    TEfficiency* Bteff  = new TEfficiency(algB , "Efficiency", muonNbins, metMin, metMax);
    TEfficiency* Cteff  = new TEfficiency(algA + " " + algB,  "Efficiency", muonNbins, metMin, metMax);
    TEfficiency* Dteff  = new TEfficiency("METL1",  "Efficiency", muonNbins, metMin, metMax);

}

void HLTEfficiencyAnalysis::End()
{
    //TCANVAS
    const TString canvName = algA + " and " + algB + " Combined Efficiency" + ";Offline Recalibrated MET w/o Muon term [GeV];Efficiency";
    TCanvas* efficiencyCanvas = new TCanvas("Efficiency Canvas", "Efficiency Canvas");
    efficiencyCanvas->RangeAxis(0,0,500,1.0);
    efficiencyCanvas->SetTitle(canvName);

    //LINE COLORS
    Ateff->SetLineColor(kBlue);
    Cteff->SetLineColor(kRed);
    Bteff->SetLineColor(kGreen);
    Dteff->SetLineColor(kBlack);

    //DRAW ON SAME CANVAS
    Ateff->Draw();
    Bteff->Draw("same");
    Cteff->Draw("same");
    Dteff->Draw("same");

    //CREATE LEGEND
    TLegend *legend = new TLegend(0.57,0.15,0.9, 0.4 ,"","NDC");
    legend->AddEntry(Ateff, astring);
    legend->AddEntry(Bteff, bstring);
    legend->AddEntry(Cteff, cstring);
    legend->AddEntry(Dteff, dstring);
    legend->Draw();

    //compute number muon events actually kept using external macro
    Int_t muonEventsCombined = determineMuonEventsKeptCombined( algA, CombinedThreshAlgA , algB , CombinedThreshAlgB , muonFilename );

    //NUM PASS PROCESS 1
    logFileParams->setNumPassNoAlgPassProcess1( NumbPassnoAlgPassProcess1WithActintCut );
    logFileParams->setNumMuonPassProcess1( NumMuonPassProcess1WithActintCut );

    //NUM MUONS PASS PROCESS 2
    Int_t NumberMuonEventsProcess2AlgAActintCut = (Ateff->GetPassedHistogram())->GetEntries() ;
    Int_t NumberMuonEventsProcess2AlgBActintCut = (Bteff->GetPassedHistogram())->GetEntries() ;
    Int_t NumberMuonEventsProcess2CombinedActintCut = (Cteff->GetPassedHistogram())->GetEntries() ;

    //SET NUM PASSNOALG PROCESS 2
    logFileParams->setNumPassNoAlgPassProcess2Combined( NumberMuonEventsProcess2CombinedActintCut);
    logFileParams->setNumPassNoAlgPassProcess2AlgA( numPassnoalgPassProcess1AlgA);
    logFileParams->setNumPassNoAlgPassProcess2AlgB( numPassnoalgPassProcess1AlgB);

    //SET NUM MUON PROCESS 2
    logFileParams->setNumMuonPassProcess2Combined( NumberMuonEventsProcess2CombinedActintCut);
    logFileParams->setNumMuonPassProcess2AlgA( NumberMuonEventsProcess2AlgAActintCut);
    logFileParams->setNumMuonPassProcess2AlgB( NumberMuonEventsProcess2AlgBActintCut);

    //SET THRESHOLDS
    logFileParams->setAlgAIndividThresh( algAThresh);
    logFileParams->setAlgBIndividThresh( algBThresh );
    logFileParams->setAlgACombinedThresh( CombinedThreshAlgA);
    logFileParams->setAlgBCombinedThresh( CombinedThreshAlgB );

    logFileParams->setNumMuonKeptCombinedAtThresh( muonEventsCombined );
    logFileParams->setNumTotal((Ateff->GetTotalHistogram())->GetEntries());

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
            rootFile->Open( fileName ,"RECREATE");
        }

    Ateff->Write( astring );
    Bteff->Write( bstring );
    Cteff->Write( cstring );
    Dteff->Write( "METL1" );

    logFileData->Write("bisectionData");
    efficiencyCanvas->Write("efficiencyCanvas");
    logFileParams->Print();
    logFileParams->Write("parameters");

    rootFile->Close();
}

void HLTEfficiencyAnalysis::DetermineThresholds()
{
    using namespace treeReaderSpace;
}

void HLTEfficiencyAnalysis::AnalyzeMuon()
{

}


void HLTEfficiencyAnalysis::DoAnalysis()
{
    //TODO: make two different benchmarks, one for determining thresholds, and one for Determining
    //      muon efficiencies
    // benchmark
    TBenchmark bmark;
    bmark.Start("benchmark");

    // optimize
    TTreeCache::SetLearnEntries(10);
    chain.SetCacheSize(128*1024*1024);

    //FILES
    TString zerobiasFileName = logFileParams->get_passnoalgFileName();
    TString muonFilename = logFileParams->get_muonFileName();

    //ZB_FILE; ZB_TREE
    TString zerobiasFilePath = "../myData/"+ zerobiasFileName;
    TFile * zeroBiasFile = TFile::Open(zerobiasFilePath, "READ");
    TTree* zeroBiasTree = (TTree*)zeroBiasFile->Get("tree");
    Int_t zerobiasNentries = zeroBiasTree->GetEntries();
    logFileParams->set_PassnoalgNentries( zerobiasNentries );

    //MUON FILE; MUON TREE
    TString muonFilePath = "../myData/"+muonFilename;
    TFile * muonFile = TFile::Open(muonFilePath, "READ");
    TTree* myMuonTree = (TTree*)muonFile->Get("tree");
    Int_t muonNentries = myMuonTree->GetEntries();
    logFileParams->setMuonNentries( muonNentries );


    //TODO: use the same object to read the threshold tree, and then to read the muon tree
    //initialize reader with zb tree
    ChainHandler_obj.Init(zeroBiasTree);

    Begin();

    //TODO: pick up here where you left off in terms of porting your analysis into this one
    for (long long entry = 0; entry < zerobiasNentries; entry++)
    {
        // load the current event
        ChainHandler_obj.GetEntry(entry);

        // analyze the event
        DetermineThresholds();

    }

    ChainHandler_obj.Init(myMuonTree);

    for (long long entry = 0; entry < muonNentries; entry++)
    {
        // load the current event
        ChainHandler_obj.GetEntry(entry);

        // analyze the event
        Analyze();

    }

    // Done and benchmark results
    bmark.Stop("benchmark");
    fflush(stdout);
    cout << "[TrackingEfficiencyAnalysis::DoAnalysis] finished processing " << num_events << " events" << endl;
    cout << "------------------------------" << endl;
    cout << "CPU  Time: " << Form("%.01f", bmark.GetCpuTime("benchmark" )) << endl;
    cout << "Real Time: " << Form("%.01f", bmark.GetRealTime("benchmark")) << endl;
    cout << endl;

    // --------------------//
    // Run the End Job
    // --------------------//
    EndJob();
}

}
