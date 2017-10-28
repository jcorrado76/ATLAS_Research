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
    friend Float_t bisection();

    //TEfficiencies
    TEfficiency* Ateff;
    TEfficiency* Bteff;
    TEfficiency* Cteff;
    TEfficiency* Dteff;

    //passnoalg hists
    TH1F *algAMETHist;
    TH1F *algBMETHist;
    TH1F *algCMETHist;

    //target passnoalg hists
    TH1F *algATarget;
    TH1F *algBTarget;
    TH1F *algCTarget;

};

//constructor definition
HLTEfficiencyAnalysis::HLTEfficiencyAnalysis()
{
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
    //INITIALIZE HISTOGRAMS
    algAMETHist = new TH1F(algA, "algA", nbins, metMin, metMax);
    algBMETHist = new TH1F(algB, "algB", nbins, metMin, metMax);
    algCMETHist = new TH1F(algA + algB , "Combined" , nbins, metMin, metMax);

    //INITIALIZE EFFICIENCIES
    Ateff  = new TEfficiency(algA , "Efficiency", muonNbins, metMin, metMax);
    Bteff  = new TEfficiency(algB , "Efficiency", muonNbins, metMin, metMax);
    Cteff  = new TEfficiency(algA + " " + algB,  "Efficiency", muonNbins, metMin, metMax);
    Dteff  = new TEfficiency("METL1",  "Efficiency", muonNbins, metMin, metMax);
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

    //TODO: need to define astring, bstring, cstring, and dstring

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

//TODO: need to finish this piece
void HLTEfficiencyAnalysis::DetermineThresholds()
{
    using namespace treeReaderSpace;

    const Float_t metl1Thresh = parameters->getMetL1Thresh();
    const Float_t actintCut = parameters->getActintCut();

    const Float_t algA = get_algA();
    const Float_t algB = get_algB();
    const Float_t passnoalgL1XE10 = get_passnoalgL1XE10();
    const Float_t passnoalgL1XE30 = get_passnoalgL1XE30();
    const Float_t passnoalgL1XE40 = get_passnoalgL1XE40();
    const Float_t passnoalgL1XE45 = get_passnoalgL1XE45();

    //filling the zb hists
	if ( ( metl1 > metL1Thresh ) && ( passnoalg_actint > actintCut ) &&
        ( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 || passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5 ) )
	{
		algAMETHist->Fill(algA);
        algBMETHist->Fill(algB);
	}

}

void HLTEfficiencyAnalysis::AnalyzeMuon()
{
    //import aliases to access values of each branch at current entry

    using namespace treeReaderSpace;

    const Float_t metl1thresh = parameters->getMetL1Thresh();
    const Float_t actintCut = parameters->getActintCut();
    const Float_t CombinedThreshAlgA = parameters->GetAlgACombinedThresh();
    const Float_t CombinedThreshAlgB = parameters->GetAlgBCombinedThresh();
    const Float_t algAThresh = parameters->GetAlgAIndividThresh();
    const Float_t algBThresh = parameters->GetAlgBIndividThresh();

    const Float_t passmuon = get_passmuon();
    const Float_t passmuvarmed = get_passmuvarmed();
    const Float_t cleanCutsFlag = get_cleanCutsFlag();
    const Float_t recalBrokeFlag = get_recalBrokeFlag();
    const Float_t metoffrecal = get_metoffrecal();
    const Float_t mexoffrecal = get_mexoffrecal();
    const Float_t meyoffrecal = get_meyoffrecal();
    const Float_t metoffrecalmuon = get_metoffrecalmuon();
    const Float_t mexoffrecalmuon = get_mexoffrecalmuon();
    const Float_t meyoffrecalmuon = get_meyoffrecalmuon();
    const Float_t metl1 = get_metl1();
    const Float_t actint = get_actint();
    const Float_t algAMET = get_algA();
    const Float_t algBMET = get_algB();



    if ( IsMuon(passmuon,passmuvarmed) && IsClean(cleanCutsFlag,recalBrokeFlag) && metl1 > metl1thresh)
    {
        parameters->IncrementNumMuonPassProcess1();
    }

    if ( IsMuon(passmuon,passmuvarmed) && IsClean(cleanCutsFlag,recalBrokeFlag) && ( actint > actintCut ))
    {
        if ( passTransverseMassCut(metoffrecal,mexoffrecal,meyoffrecal,metoffrecalmuon,mexoffrecalmuon,meyoffrecalmuon) )
        {
            Float_t metnomu = computeMetNoMu(  mexoffrecal , meyoffrecal , mexoffrecalmuon , meyoffrecalmuon );

            Ateff->Fill((algAMET > algAThresh) && (metl1 > metl1thresh) && ( actint > actintCut ), metnomu);
            Bteff->Fill((algBMET > algBThresh) && (metl1 > metl1thresh)&& ( actint > actintCut ), metnomu);
            Cteff->Fill(((algAMET > CombinedThreshAlgA) && (algBMET > CombinedThreshAlgB)
            && ( actint > actintCut )&& (metl1 > metl1thresh)), metnomu);
            Dteff->Fill((metl1 >= metl1thresh) && ( actint > actintCut ), metnomu);
        }
    }
}

//TODO: need to finish determine thresholds portion
void HLTEfficiencyAnalysis::DoAnalysis()
{
    // benchmark
    TBenchmark bmark;
    bmark.Start("Determine Thresholds");

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


    //initialize reader with zb tree
    ChainHandler_obj.Init(zeroBiasTree);

    Begin();


    //DETERMINE INDIVIDUAL ZB thresholds

    //convenient alias
    Int_t numbKeep = parameters->getNumbToKeep();

    for (long long entry = 0; entry < zerobiasNentries; entry++)
    {
        // load the current event
        ChainHandler_obj.GetEntry(entry);

        DetermineThresholds();
    }

    TH1F *algATarget = (TH1F*) algAMETHist->GetCumulative(kFALSE);
	parameters->setAlgAIndividThresh(computeThresh(algATarget, numbKeep));

    TH1F *algBTarget = (TH1F*) algBMETHist->GetCumulative(kFALSE);
	parameters->setAlgBIndividThresh(computeThresh(algBTarget, numbKeep));

    //DETERMINE COMINED THRESHOLDS

    bisection( algAMETHist , algBMETHist, binWidth, CombinedThreshAlgA,
    CombinedThreshAlgB, NumbPassnoAlgPassProcess1WithActintCut , frac ,
    logFileData,zeroBiasTree);


    // Done and benchmark results
    bmark.Stop("DetermineThresholds");
    cout << "CPU  Time: " << Form("%.01f", bmark.GetCpuTime("DetermineThresholds" )) << endl;
    cout << "Real Time: " << Form("%.01f", bmark.GetRealTime("DetermineThresholds")) << endl;
    cout << endl;

    //COMPUTE EFFICIENCIES
    ChainHandler_obj.Init(myMuonTree);
    ChainHandler_obj.ZbBranchInit(zeroBiasTree)

    bmark.Start("Analyze Efficiencies");
    for (long long entry = 0; entry < muonNentries; entry++)
    {
        // load the current event
        ChainHandler_obj.GetEntry(entry);

        // analyze the event
        AnalyzeMuon();

    }

    bmark.Stop("Analyze Efficiencies");
    cout << "CPU  Time: " << Form("%.01f", bmark.GetCpuTime("Analyze Efficiencies" )) << endl;
    cout << "Real Time: " << Form("%.01f", bmark.GetRealTime("Analyze Efficiencies")) << endl;
    cout << endl;

    End();
}

}
