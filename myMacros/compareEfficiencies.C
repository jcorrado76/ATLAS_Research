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
#include "TBenchmark.h"

Int_t compareEfficiencies(const TString& muonFileName = "PhysicsMain.L1KFmuontriggers.2016.f731f758_m1659m1710.Run309759.48Runs.root")
{
    /*
    This plots the same combination of algorithms twice on the same plot for two different sets of thresholds
    */

    gROOT->ProcessLine("gSystem->Load(\"./mincerMacros_C.so\")");
    Bool_t passTransverseMassCut( const Float_t , const Float_t ,const Float_t ,const Float_t ,const Float_t ,const Float_t);


    TBenchmark* compareThreshBench = new TBenchmark();


    compareThreshBench->Start("Threshold Comparison");

    //parameters
    Int_t nbins = 300;
    Float_t metMin = 0.0;
    Float_t metMax = 300.0;
    Float_t metl1thresh = 50.0;

    //worse pair of threhsolds
    Float_t mht = 123.62;
    Float_t puc = 106.38;

    //better pair of thresholds
    Float_t mhtbetter = 107.88;
    Float_t pucbetter = 91.38;

    ///combined algs
    TEfficiency* worsepair  = new TEfficiency("worsepair" , "Efficiency", nbins, metMin, metMax);
    TEfficiency* betterpair  = new TEfficiency("betterpair" , "Efficiency", nbins, metMin, metMax);

    //initialize branch variables

    ///open muon tree
    TString muonFilePath = "../myData/"+muonFileName;
    TFile * muonFile = TFile::Open(muonFilePath, "READ");
    TTree* myMuonTree = (TTree*)muonFile->Get("tree");
    Int_t muonNentries = myMuonTree->GetEntries();


    Float_t metcell,metmht,metl1,mettopocl,mettopoclps,mettopoclpuc,metoffrecal,mexoffrecal,
    meyoffrecal,metoffrecalmuon,mexoffrecalmuon,meyoffrecalmuon;
    Int_t passmuon,passmuvarmed,cleanCutsFlag,recalBrokeFlag;

    //assign branch variables to locations
    myMuonTree->SetBranchAddress("metmht",&metmht);
    myMuonTree->SetBranchAddress("metl1",&metl1);
    myMuonTree->SetBranchAddress("mettopoclpuc",&mettopoclpuc);

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

    for (Int_t l = 0 ; l < muonNentries ; l++)
    {
        myMuonTree->GetEntry(l);
        {
            if ((passmuvarmed > 0.1 || passmuon > 0.1) && cleanCutsFlag > 0.1 && recalBrokeFlag < 0.1)
            {
                if ( passTransverseMassCut(metoffrecal,mexoffrecal,meyoffrecal,metoffrecalmuon,mexoffrecalmuon,meyoffrecalmuon) )
                {
                    Float_t metnomu = sqrt(((mexoffrecal - mexoffrecalmuon) * (mexoffrecal - mexoffrecalmuon)) +
                    ((meyoffrecal - meyoffrecalmuon)*(meyoffrecal - meyoffrecalmuon))); //compute metnomu
                    betterpair->Fill( (metmht > mhtbetter) && (mettopoclpuc > pucbetter) && (metl1 > metl1thresh), metnomu);
                    worsepair->Fill( (metmht > mht) && (mettopoclpuc > puc) && (metl1 > metl1thresh), metnomu);
                }
            }
        }
    }


    TCanvas* efficiencyCanvas = new TCanvas("myCanv", "Efficiency Canvas");
    efficiencyCanvas->RangeAxis(0,0,500,1.0);

    betterpair->SetLineColor(kBlue);
    worsepair->SetLineColor(kRed);


    const TString canvName = "Efficiency Best Combination vs Best Individual;Offline Recalibrated MET w/o Muon term [GeV];Efficiency";

    betterpair->SetTitle(canvName);

    betterpair->Draw();
    worsepair->Draw("same");


    TLegend *legend = new TLegend(0.57,0.15,0.9, 0.4 ,"","NDC");
    legend->AddEntry(betterpair, "betterpair");
    legend->AddEntry(worsepair, "worsepair");
    legend->Draw();


    std::cout << "Number of events passed by worse pair: " << (worsepair->GetPassedHistogram())->GetEntries() << std::endl;
    std::cout << "Number of events passed by better pair: " << (betterpair->GetPassedHistogram())->GetEntries() << std::endl;
    std::cout << "Total number of entries: " << (betterpair->GetTotalHistogram())->GetEntries() << std::endl;



    TString folderPath = "./TEfficienciesPics/Print5Efficiencies/ThresholdComparison.tiff";
    efficiencyCanvas->Print(folderPath);

    compareThreshBench->Show("Threshold Comparison");

    return(0);
}
