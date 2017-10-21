#include "mincerMacros.h"

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

    void ScanChain( TChain* chain );

private:
    //analysis methods
    void Begin();
    void End();
    void Analyze();

    //data members
    userInfo* parameters;
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


HLTEfficiencyAnalysis::Begin()
{
    //FILES
    TString zerobiasFileName = logFileParams->get_passnoalgFileName();
    TString muonFilename = logFileParams->get_muonFileName();

    //ZB_FILE; ZB_TREE
    TString zerobiasFilePath = "../myData/"+ zerobiasFileName;
    TFile * zeroBiasFile = TFile::Open(zerobiasFilePath, "READ");
    TTree* zeroBiasTree = (TTree*)zeroBiasFile->Get("tree");
    Int_t zerobiasNentries = zeroBiasTree->GetEntries();

    //MUON FILE; MUON TREE
    TString muonFilePath = "../myData/"+muonFilename;
    TFile * muonFile = TFile::Open(muonFilePath, "READ");
    TTree* myMuonTree = (TTree*)muonFile->Get("tree");
    Int_t muonNentries = myMuonTree->GetEntries();

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


    //CREATE EFFICIENCY TITLES
    TString cstring = algA + " > " + Form(" %.2f", CombinedThreshAlgA) + " and " + algB + " > " + Form(" %.2f", CombinedThreshAlgB);
    TString astring = algA + " > " + Form(" %.2f", algAThresh);
    TString bstring = algB + " > " + Form(" %.2f", algBThresh);
    TString dstring = (TString) "L1 > " + Form(" %.2f" , metl1thresh);

    //INITIALIZE EFFICIENCIES
    TEfficiency* Ateff  = new TEfficiency(astring , "Efficiency", muonNbins, metMin, metMax);
    TEfficiency* Bteff  = new TEfficiency(bstring , "Efficiency", muonNbins, metMin, metMax);
    TEfficiency* Cteff  = new TEfficiency(cstring,  "Efficiency", muonNbins, metMin, metMax);
    TEfficiency* Dteff  = new TEfficiency(dstring,  "Efficiency", muonNbins, metMin, metMax);//combined just L1 cut, 0 on others
}


HLTEfficiencyAnalysis::End()
{
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

    logFileParams->setNumPassNoAlgPassProcess1( NumbPassnoAlgPassProcess1WithActintCut );
    logFileParams->setNumMuonPassProcess1( NumMuonPassProcess1WithActintCut );

    Int_t NumberMuonEventsProcess2CombinedActintCut = (Cteff->GetPassedHistogram())->GetEntries() ;
    Int_t NumberMuonEventsProcess2AlgAActintCut = (Ateff->GetPassedHistogram())->GetEntries() ;
    Int_t NumberMuonEventsProcess2AlgBActintCut = (Bteff->GetPassedHistogram())->GetEntries() ;

    logFileParams->setNumMuonPassProcess2Combined( NumberMuonEventsProcess2CombinedActintCut);
    logFileParams->setNumMuonPassProcess2AlgA( NumberMuonEventsProcess2AlgAActintCut);
    logFileParams->setNumMuonPassProcess2AlgB( NumberMuonEventsProcess2AlgBActintCut);

    logFileParams->setNumPassNoAlgPassProcess2Combined( NumberMuonEventsProcess2CombinedActintCut);
    logFileParams->setNumPassNoAlgPassProcess2AlgA( numPassnoalgPassProcess1AlgA);
    logFileParams->setNumPassNoAlgPassProcess2AlgB( numPassnoalgPassProcess1AlgB);

    logFileParams->setAlgAIndividThresh( algAThresh);
    logFileParams->setAlgBIndividThresh( algBThresh );
    logFileParams->setAlgACombinedThresh( CombinedThreshAlgA);
    logFileParams->setAlgBCombinedThresh( CombinedThreshAlgB );


    logFileParams->setMuonNentries( muonNentries );
    logFileParams->set_PassnoalgNentries( zerobiasNentries );
    logFileParams->setNumMuonKeptCombinedAtThresh( muonEventsCombined );
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
