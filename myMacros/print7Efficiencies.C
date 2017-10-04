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


Int_t print7Efficiencies(const TString& muonFileName = "PhysicsMain.L1KFmuontriggers.2016.f731f758_m1659m1710.Run309759.48Runs.root")
{
    /* makes a plot with all 7 efficiency curves*/
    /* This plot compares the 4 combined algorithms that do better when used together, and plots them
    on the same canvas as the algorithms CERN currently uses
    4 that do better: (metcell, metmht) , (metcell , mettopocl) , (mettcell , mettopoclps) , (metmht , mettopoclpuc)
    3 individually: metmht ; metcell ; mettopoclpuc
    */

    gROOT->ProcessLine("gSystem->Load(\"./mincerMacros_C.so\")");
    Bool_t passTransverseMassCut( const Float_t , const Float_t ,const Float_t ,const Float_t ,const Float_t ,const Float_t);

    //parameters
    Int_t nbins = 300;
    Float_t metMin = 0.0;
    Float_t metMax = 300.0;
    Float_t metl1thresh = 50.0;

    //individual thresholds
    Float_t cellThresh = 100.0;
    Float_t mhtThresh = 139.88;
    Float_t topoclpucThresh = 122.62;

    //combined pairs of threhsolds
    Float_t cellCombinedThresh = 81.12;
    Float_t mhtCombinedThresh = 116.62;

    Float_t mhtCombined2Thresh = 123.62;
    Float_t topoclpucCombinedThresh = 106.38;

    //individuals
    TEfficiency* cellTeff  = new TEfficiency("metcell" , "Efficiency", nbins, metMin, metMax);
    TEfficiency* mhtTeff  = new TEfficiency("metmht", "Efficiency", nbins, metMin, metMax);
    TEfficiency* topoclpucTeff  = new TEfficiency("mettopocl",  "Efficiency", nbins, metMin, metMax);

    ///combined algs
    TEfficiency* cellmhtTeff  = new TEfficiency("cellmhtcombined" , "Efficiency", nbins, metMin, metMax);
    TEfficiency* mhttopoclpucTeff  = new TEfficiency("mhttopoclpuccombined" , "Efficiency", nbins, metMin, metMax);

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
    myMuonTree->SetBranchAddress("metcell",&metcell);
    myMuonTree->SetBranchAddress("metmht",&metmht);
    myMuonTree->SetBranchAddress("metl1",&metl1);
    myMuonTree->SetBranchAddress("mettopocl",&mettopocl);
    myMuonTree->SetBranchAddress("mettopoclps",&mettopoclps);
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

    /*
    Int_t numbPassAllCutsndL1 = 0;
    for (Int_t l = 0 ; l < muonNentries ; l++)
    {
        myMuonTree->GetEntry(l);
        {
            if ((passmuvarmed > 0.1 || passmuon > 0.1) && cleanCutsFlag > 0.1 && recalBrokeFlag < 0.1)
            {
                if ( passTransverseMassCut(metoffrecal,mexoffrecal,meyoffrecal,metoffrecalmuon,mexoffrecalmuon,meyoffrecalmuon) )
                {
                    if ( metl1 > metl1thresh )
                    {
                        numbPassAllCutsndL1++;
                    }
                    Float_t metnomu = sqrt(((mexoffrecal - mexoffrecalmuon) * (mexoffrecal - mexoffrecalmuon)) +
                    ((meyoffrecal - meyoffrecalmuon)*(meyoffrecal - meyoffrecalmuon))); //compute metnomu
                    cellTeff->Fill( (metcell > cellThresh) && (metl1 > metl1thresh), metnomu);
                    mhtTeff->Fill( (metmht > mhtThresh) && (metl1 > metl1thresh), metnomu);
                    topoclpucTeff->Fill( (mettopoclpuc > topoclpucThresh) && (metl1 > metl1thresh) , metnomu);

                    cellmhtTeff->Fill( (metcell > cellCombinedThresh) && (metmht > mhtCombinedThresh)&& (metl1 > metl1thresh), metnomu );
                    mhttopoclpucTeff->Fill( ( (metmht > mhtCombined2Thresh) && (mettopoclpuc > topoclpucCombinedThresh) && (metl1 > metl1thresh)), metnomu);
                }
            }
        }
    }

    std::cout << "Number of events that passed all cuts, except for the cut on the alg itself (includes L1, etc.) "
    << numbPassAllCutsndL1 << std::endl;

*/
    TCanvas* efficiencyCanvas = new TCanvas("myCanv", "Efficiency Canvas");
    efficiencyCanvas->RangeAxis(0,0,500,1.0);

    cellTeff->SetLineColor(kBlue);
    mhtTeff->SetLineColor(kRed);
    topoclpucTeff->SetLineColor(kGreen);
    cellmhtTeff->SetLineColor(kBlack);
    mhttopoclpucTeff->SetLineColor(kTeal);


    const TString canvName = "Efficiency Best Combination vs Best Individual;Offline Recalibrated MET w/o Muon term [GeV];Efficiency";

    cellTeff->SetTitle(canvName);

    cellTeff->Draw();
    mhtTeff->Draw("same");
    topoclpucTeff->Draw("same");
    cellmhtTeff->Draw("same");
    mhttopoclpucTeff->Draw("same");


    TLegend *legend = new TLegend(0.57,0.15,0.9, 0.4 ,"","NDC");
    legend->AddEntry(cellTeff, "metcell");
    legend->AddEntry(mhtTeff, "metmht");
    legend->AddEntry(topoclpucTeff, "mettopoclpuc");
    legend->AddEntry(cellmhtTeff, "cell and mht");
    legend->AddEntry(mhttopoclpucTeff, "mht and topoclpuc");
    legend->Draw();

    TString folderPath = "./TEfficienciesPics/Print5Efficiencies/BestCombinationefficiencies.tiff";
    TString bestCombinationRootFileName = "./TEfficienciesPics/Print5Efficiencies/EfficiencyBestCombination.root";
    TFile rootFile(bestCombinationRootFileName,"CREATE");

    if ( !( rootFile.IsOpen() ) )
        {
            TString suffix = "";
            std::cout << "Unable to open file" << std::endl;
            std::cout << "Enter run number: ";
            std::cin >> suffix;
            suffix = "(" + suffix + ")";
            bestCombinationRootFileName.Insert( (bestCombinationRootFileName.Length()-5),suffix);
            rootFile.Open( bestCombinationRootFileName ,"RECREATE");
            folderPath.Insert( (folderPath.Length()-5),suffix);
        }

    std::cout << "Root file successfully opened" << std::endl;

    efficiencyCanvas->Write();
    cellTeff->Write();
    mhtTeff->Write();
    topoclpucTeff->Write();
    cellmhtTeff->Write();
    mhttopoclpucTeff->Write();


    efficiencyCanvas->Print(folderPath);
    return(0);
}
