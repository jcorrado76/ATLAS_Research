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


const TString& zerobiasFileName = "PhysicsMain.All.noalgXEtriggers.2016.f731f758._m1659m1710.48Runs.root";
const TString& muonFileName = "PhysicsMain.L1KFmuontriggers.2016.f731f758_m1659m1710.Run309759.48Runs.root";

Int_t printEfficiencies()
{
    /* makes a plot with simply all 5 efficiency curves*/
    Float_t determineZeroBiasThresh( const TString&, const Float_t, const TString&);
    Float_t computeThresh(TH1F*,Float_t);
    const Float_t frac = 0.00590;
    const TString& folder = "";
    const TString metcellName = "metcell";
    const TString metmhtName = "metmht";
    const TString mettopoclName = "mettopocl";
    const TString mettopoclpsName = "mettopoclps";
    const TString mettopoclpucName = "mettopoclpuc";

    TString zerobiasFilePath = "../myData/"+ zerobiasFileName;
    TFile * zeroBiasFile = TFile::Open(zerobiasFilePath, "READ");
    TTree* zeroBiasTree = (TTree*)zeroBiasFile->Get("tree");
    Int_t zerobiasNentries = zeroBiasTree->GetEntries();

    Int_t nbins = 1200;
    Int_t muonNbins = 200;
    Float_t metMin = 0;
    Float_t metMax = 300;
    Float_t muonMetMin = metMin;
    Float_t muonMetMax = 300;
    Int_t numbPassMuon = 0;
    Float_t metcellThresh = determineZeroBiasThresh(metcellName,frac,zerobiasFileName);
    Float_t metmhtThresh = determineZeroBiasThresh(metmhtName,frac,zerobiasFileName);
    Float_t mettopoclThresh = determineZeroBiasThresh(mettopoclName,frac,zerobiasFileName);
    Float_t mettopoclpsThresh = determineZeroBiasThresh(mettopoclpsName,frac,zerobiasFileName);
    Float_t mettopoclpucThresh = determineZeroBiasThresh(mettopoclpucName,frac,zerobiasFileName);
    Float_t metl1Thresh = 50.0;
    Float_t metcell,metmht,mettopocl,mettopoclps,mettopoclpuc,metl1;
    Int_t passRndm, numPassMuon,passmuon,passmuvarmed,cleanCutsFlag,recalBrokeFlag;
    Float_t algAMET,algBMET,metoffrecal,mexoffrecal,meyoffrecal,offrecalmuon_mex,
            offrecalmuon_mey, acthresh,bcthresh,metrefmuon,mexrefmuon,meyrefmuon,w;
    Int_t passnoalgL1XE10,passnoalgL1XE30,passnoalgL1XE40,passnoalgL1XE45;

    TEfficiency* metcellteff  = new TEfficiency(metcellName , "Metcell Efficiency", muonNbins, muonMetMin, muonMetMax);
    TEfficiency* metmhtteff  = new TEfficiency(metmhtName , "Metmht Efficiency", muonNbins, muonMetMin, muonMetMax);
    TEfficiency* mettopoclteff  = new TEfficiency(mettopoclName,  "Mettopocl Efficiency", muonNbins, muonMetMin, muonMetMax);
    TEfficiency* mettopoclpsteff  = new TEfficiency(mettopoclpsName,  "Mettopoclps Efficiency", muonNbins, muonMetMin, muonMetMax);
    TEfficiency* mettopoclpucteff  = new TEfficiency(mettopoclpucName,  "Mettopoclpuc Efficiency", muonNbins, muonMetMin, muonMetMax);

    TString muonFilePath = "../myData/" + muonFileName;
    TFile * muonFile = TFile::Open(muonFilePath, "READ");
    TTree* myMuonTree = (TTree*)muonFile->Get("tree");



    Int_t muonNentries = myMuonTree->GetEntries();
    myMuonTree->SetBranchAddress("passmu26med", &passmuon);
    myMuonTree->SetBranchAddress("passmu26varmed", &passmuvarmed);
    myMuonTree->SetBranchAddress("passcleancuts", &cleanCutsFlag);
    myMuonTree->SetBranchAddress("recalbroke", &recalBrokeFlag);
    myMuonTree->SetBranchAddress("metoffrecal", &metoffrecal);
    myMuonTree->SetBranchAddress("mexoffrecal", &mexoffrecal);
    myMuonTree->SetBranchAddress("meyoffrecal", &meyoffrecal);
    myMuonTree->SetBranchAddress("metoffrecalmuon", &metoffrecalmuon);
    myMuonTree->SetBranchAddress("mexoffrecalmuon", &offrecalmuon_mex);
    myMuonTree->SetBranchAddress("meyoffrecalmuon", &offrecalmuon_mey);
    myMuonTree->SetBranchAddress("metrefmuon", &metrefmuon);
    myMuonTree->SetBranchAddress("mexrefmuon", &mexrefmuon);
    myMuonTree->SetBranchAddress("meyrefmuon", &meyrefmuon);
    myMuonTree->SetBranchAddress("metl1", &metl1);
    myMuonTree->SetBranchAddress(metcellName,&metcell);
    myMuonTree->SetBranchAddress(metmhtName,&metmht);
    myMuonTree->SetBranchAddress(mettopoclName,&mettopocl);
    myMuonTree->SetBranchAddress(mettopoclpsName,&mettopoclps);
    myMuonTree->SetBranchAddress(mettopoclpucName,&mettopoclpuc);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE10",&passnoalgL1XE10);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE30",&passnoalgL1XE30);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE40",&passnoalgL1XE40);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE45",&passnoalgL1XE45);

    for (Int_t l = 0 ; l < muonNentries ; l++)
    {
        myMuonTree->GetEntry(l);
        if ((passmuvarmed > 0.1 || passmuon > 0.1) && (cleanCutsFlag > 0.1) && (recalBrokeFlag < 0.1))
        {
            w = sqrt(2.0*metoffrecal*metoffrecalmuon*(1+((mexoffrecal*mexoffrecalmuon+meyoffrecal*meyoffrecalmuon)/(
                metoffrecal * metoffrecalmuon))));
            if (w >= 40.0 && w <= 80.0)
            {
                Float_t metnomu = sqrt(((mexoffrecal - offrecalmuon_mex) * (mexoffrecal - offrecalmuon_mex)) +
                ((meyoffrecal - offrecalmuon_mey)*(meyoffrecal - offrecalmuon_mey))); //compute metnomu
                numbPassMuon++;
                metcellteff->Fill((metcell > metcellThresh) && (metl1 > metl1Thresh), metnomu);
                metmhtteff->Fill((metmht > metmhtThresh) && (metl1 > metl1Thresh), metnomu);
                mettopoclteff->Fill((mettopocl > mettopoclThresh) && (metl1 > metl1Thresh), metnomu);
                mettopoclpsteff->Fill((mettopoclps > mettopoclpsThresh)&& (metl1 > metl1Thresh), metnomu);
                mettopoclpucteff->Fill((mettopoclpuc > mettopoclpucThresh)&& (metl1 > metl1Thresh), metnomu);
            }
        }
    }

    TCanvas* efficiencyCanvas = new TCanvas("Efficiency Canvas", "Efficiency Canvas");
    efficiencyCanvas->RangeAxis(0,0,500,1.0);

    metcellteff->SetLineColor(kBlue);
    metmhtteff->SetLineColor(kRed);
    mettopoclteff->SetLineColor(kGreen);
    mettopoclpsteff->SetLineColor(kBlack);
    mettopoclpucteff->SetLineColor(kYellow);

    const TString canvName = "5 Efficiencies;Offline Recalibrated MET w/o Muon term [GeV];Efficiency";

    metcellteff->SetTitle(canvName);

    metcellteff->Draw();
    metmhtteff->Draw("same");
    mettopoclteff->Draw("same");
    mettopoclpsteff->Draw("same");
    mettopoclpucteff->Draw("same");

    TLegend *legend = new TLegend(0.57,0.15,0.9, 0.4 ,"","NDC");
    legend->AddEntry(metcellteff, metcellName);
    legend->AddEntry(metmhtteff, metmhtName);
    legend->AddEntry(mettopoclteff, mettopoclName);
    legend->AddEntry(mettopoclpsteff, mettopoclpsName);
    legend->AddEntry(mettopoclpucteff, mettopoclpucName);
    legend->Draw();
    TString folderPath = "./TEfficienciesPics/" + folder + "_5_efficiencies.png";
    efficiencyCanvas->Print(folderPath);
}


Float_t determineZeroBiasThresh( const TString& alg, const Float_t frac = 0.00590, zerobiasFileName)
{
    Float_t computeThresh(TH1F*,Float_t);
    TString zeroBiasPath = "../myData/" + zeroBiasFileName;
	TFile *zeroBiasFile = TFile::Open(zeroBiasPath, "READ");
	TTree *zeroBiasTree = (TTree*)(zeroBiasFile->Get("tree"));
	Int_t zerobiasNentries = zeroBiasTree->GetEntries();
    Int_t passRndm;
	Int_t nbins = 1200;
	Double_t metMin = 0;
	Double_t metMax = 300;
    Float_t metl1thresh = 50.0;
	Float_t metl1, metcell, metmht, mettopocl, mettopoclps, mettopoclpuc, indeterminate,
	metcellthresh, metmhtthresh, mettopoclthresh, mettopoclpsthresh, mettopoclpucthresh,rightHandSum;
    Int_t passnoalgL1XE10,passnoalgL1XE30,passnoalgL1XE40,passnoalgL1XE45;
    TH1F *indeterminateHist = new TH1F(alg, alg, nbins, metMin, metMax);
	zeroBiasTree->SetBranchAddress(alg,&indeterminate);
	zeroBiasTree->SetBranchAddress("metl1",&metl1);
    zeroBiasTree->SetBranchAddress("passrndm", &passRndm);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE10",&passnoalgL1XE10);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE30",&passnoalgL1XE30);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE40",&passnoalgL1XE40);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE45",&passnoalgL1XE45);
	TString xlabel = "MET [GeV]";
	TString yaxis = "Events";
    for (Int_t k = 0; k < zerobiasNentries; k++)
	{
		zeroBiasTree->GetEntry(k);
		if (( ( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 || passnoalgL1XE40 > 0.5 ||
            passnoalgL1XE45 > 0.5 ) && ( metl1 > metl1thresh ) ))
		{
			indeterminateHist->Fill(indeterminate);
		}

    }
	std::cout << "FRACTION: " << frac << std::endl;
	std::cout << "ZEROBIAS NENTRIES: " << zerobiasNentries << std::endl;

    TH1F *indeterminatetarget = (TH1F*) indeterminateHist->GetCumulative(kFALSE);
	Float_t numKeep = 5762.0;
	Float_t indeterminateThresh = computeThresh(indeterminatetarget, numKeep);
	std::cout << alg << " THRESHOLD: " << indeterminateThresh << std::endl;
	std::cout << "Number of events that should have been kept: " << numKeep << std::endl;
	std::cout << "Checking how many events are kept by the alg at the determined threshold..." << std::endl;
	Int_t counter=0;
	for (Int_t l = 0 ; l < zerobiasNentries ; l++)
	{
		zeroBiasTree->GetEntry(l);
		if (( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 || passnoalgL1XE40 > 0.5 ||
            passnoalgL1XE45 > 0.5 ) && (indeterminate > indeterminateThresh) && (metl1 > metl1thresh))
		{
			counter++;
		}
	}
	zeroBiasFile->Close();
	std::cout << "Number of events counted above threshold: " << counter << "\n" << std::endl;
	return(indeterminateThresh);
}

Float_t computeThresh(TH1F* target, Float_t numKeep)
{
    Int_t nbin = 0;
    gROOT->ProcessLine("gROOT->Reset();");
    target->GetBinWithContent(numKeep,nbin,0,-1,20000); //if firstx<=0{firstx=1}; if lastx<firstx{lastx=fXaxis.GetNbinsX()};
    Float_t thresh = (target->GetXaxis())->GetBinCenter(nbin);
    return(thresh);
}
