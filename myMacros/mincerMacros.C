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

Bool_t passTransverseMassCut( const Float_t metoffrecal     , const Float_t mexoffrecal     , const Float_t meyoffrecal ,
           const Float_t metoffrecalmuon , const Float_t mexoffrecalmuon , const Float_t meyoffrecalmuon )
{
    Float_t wLowerbnd = 40.0;
    Float_t wUpperbnd = 100.0;
    Float_t wValue = sqrt( 2.0 * metoffrecal * metoffrecalmuon * ( 1 + ( ( mexoffrecal * mexoffrecalmuon + meyoffrecal * meyoffrecalmuon ) /
                           ( metoffrecal * metoffrecalmuon ) ) ) );
    Bool_t pass;
    pass = ( wValue >= wLowerbnd ) && ( wValue <= wUpperbnd );
    return( pass );
}

Float_t computeThresh(const TH1F* target, const Float_t numberEventsToKeep)
{
    Int_t nbin = 0;
    target->GetBinWithContent( numberEventsToKeep , nbin , 5 , -1 , 20000 ); //if firstx<=0{firstx=1}; if lastx<firstx{lastx=fXaxis.GetNbinsX()};
    Float_t thresh = (target->GetXaxis())->GetBinCenter(nbin);
    return(thresh);
}


Float_t determineZeroBiasThresh( const TString& algName, const Float_t frac = 0.00590,
const TString& zeroBiasFileName = "PhysicsMain.All.noalgXEtriggers.2016.f731f758._m1659m1710.48Runs.root")
{
    /*Returns the threshold needed for an algorithm to keep the fraction of zerobias events*/

    const Float_t metL1Thresh = 50;

    //get zerobias tree
    const TString zeroBiasPath = "../myData/" + zeroBiasFileName;
	TFile *zeroBiasFile = TFile::Open(zeroBiasPath, "READ");
	TTree *zeroBiasTree = (TTree*)(zeroBiasFile->Get("tree"));
    const Int_t zerobiasNentries = zeroBiasTree->GetEntries();

    //display inputs
    std::cout << "DETERMINETHRESH.C" << std::endl;
    std::cout << "using zerobias datafile: " << zeroBiasFileName << std::endl;
    std::cout << "alg: " << algName << std::endl;
    std::cout << "using L1 thresh: " << metL1Thresh << std::endl;
    std::cout << "fraction of events to keep: " << frac << std::endl;
    std::cout << "zerobias nentries: " << zerobiasNentries << std::endl;

    //intialize parameters
    const Float_t numberEventsToKeep = 5762.0;
	const Int_t nbins = 1200;
	const Double_t metMin = 0.0;
	const Double_t metMax = 300.0;
	Float_t metl1, algMET;
    Int_t numberEventsKept = 0;
    Int_t passnoalgL1XE10 , passnoalgL1XE30 , passnoalgL1XE40 , passnoalgL1XE45;
    TH1F *indeterminateHist = new TH1F(algName, algName, nbins, metMin, metMax);

    //set branch address for zerobias branches
	zeroBiasTree->SetBranchAddress(algName,&algMET);
	zeroBiasTree->SetBranchAddress("metl1",&metl1);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE10",&passnoalgL1XE10);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE30",&passnoalgL1XE30);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE40",&passnoalgL1XE40);
    zeroBiasTree->SetBranchAddress("passnoalgL1XE45",&passnoalgL1XE45);

    //fill the histogram with entries
    for (Int_t k = 0; k < zerobiasNentries; k++)
	{
		zeroBiasTree->GetEntry(k);
		if ( ( metl1 > metL1Thresh ) &&
            ( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 || passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5 ) )
		{
			indeterminateHist->Fill(algMET);
		}
    }

    //compute the threshold to keep appropriate fraction
    TH1F *indeterminatetarget = (TH1F*) indeterminateHist->GetCumulative(kFALSE);
	Float_t indeterminateThresh = computeThresh(indeterminatetarget, numberEventsToKeep);
	std::cout << algName << "threshold: " << indeterminateThresh << std::endl;
	std::cout << "target number events to keep: " << numberEventsToKeep << std::endl;

    //determine number of events kept at determined threshold (gives idea of error due to binning)
	for (Int_t l = 0 ; l < zerobiasNentries ; l++)
	{
		zeroBiasTree->GetEntry(l);
		if ( (algMET > indeterminateThresh) && (metl1 > metL1Thresh) &&
           ( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 || passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5 ) )
		{
			numberEventsKept++;
		}
	}

    std::cout << "number of events kept at threshold: " << numberEventsKept << "\n" << std::endl;

    zeroBiasFile->Close();

	return(indeterminateThresh);
}

Float_t determineMuonEventsKeptCombined( const TString& algA, const Float_t threshA,
                                         const TString& algB, Float_t threshB,
                                         const TString& muonFileName = "PhysicsMain2016.Muons.noalgL1XE45R3073065R311481Runs9B.root")
{

    const Float_t metL1Thresh = 50.0;
    //display algs and thresholds
    std::cout << "Determining fraction of muon events kept when using combined algorithm of " << algA << " at: " << threshA << ", "
    << algB << " at: " << threshB << " and metl1 at: " << metL1Thresh << std::endl;

    //get muon tree
    TString muonFilePath = "../myData/"+muonFileName;
    TFile * muonFile = TFile::Open(muonFilePath, "READ");
    TTree* muonTree = (TTree*)muonFile->Get("tree");
    Int_t muonNentries = muonTree->GetEntries();

    //initialize variables
    Float_t algAMET, algBMET,metl1, wValue;
    Int_t passmuon,passmuvarmed,recalBrokeFlag,cleanCutsFlag;
    Float_t metoffrecal,metoffrecalmuon,mexoffrecal,meyoffrecal,mexoffrecalmuon,meyoffrecalmuon,metrefmuon,mexrefmuon,meyrefmuon;
    Int_t numbPassedEvents = 0;
    Int_t numberMuonEvents = 0;


    muonTree->SetBranchAddress("passmu26med",&passmuon);
    muonTree->SetBranchAddress("passmu26varmed",&passmuvarmed);
    muonTree->SetBranchAddress("recalbroke",&recalBrokeFlag);
    muonTree->SetBranchAddress("passcleancuts",&cleanCutsFlag);
    muonTree->SetBranchAddress(algA,&algAMET);
    muonTree->SetBranchAddress("metl1",&metl1);
    muonTree->SetBranchAddress("metoffrecal", &metoffrecal);
    muonTree->SetBranchAddress("mexoffrecal", &mexoffrecal);
    muonTree->SetBranchAddress("meyoffrecal", &meyoffrecal);
    muonTree->SetBranchAddress("metoffrecalmuon", &metoffrecalmuon);
    muonTree->SetBranchAddress("mexoffrecalmuon", &mexoffrecalmuon);
    muonTree->SetBranchAddress("meyoffrecalmuon", &meyoffrecalmuon);
    muonTree->SetBranchAddress("metrefmuon", &metrefmuon);
    muonTree->SetBranchAddress("mexrefmuon", &mexrefmuon);
    muonTree->SetBranchAddress("meyrefmuon", &meyrefmuon);

    if ( algA != algB ) {//algs not the same, initialize second alg
         muonTree->SetBranchAddress( algB , &algBMET );
     }
    else {//algs are the same; set B to pass always
        threshB = threshA; algBMET = 0;
    }

    for (Int_t i  = 0 ; i < muonNentries ;i++)
      {
        muonTree->GetEntry(i);

        wValue = w( metoffrecal ,mexoffrecal , meyoffrecal , metoffrecalmuon , mexoffrecalmuon , meyoffrecalmuon );

        if (
               ((passmuon > 0.5) || (passmuvarmed > 0.5)) &&
               (cleanCutsFlag > 0.1 && recalBrokeFlag < 0.1) &&
               (wValue >= 40.0 && wValue <= 80.0) )
        {
          numberMuonEvents++;
        }
        if (
             ((algAMET > threshA) && (algBMET > threshB) && (metl1 > metL1Thresh)) &&
             ((passmuon > 0.5) || (passmuvarmed > 0.5)) &&
             (cleanCutsFlag > 0.1 && recalBrokeFlag < 0.1) &&
             (wValue >= 40.0 && wValue <= 80.0 )
           )
        {
          numbPassedEvents++;
        }
      }


    std::cout << "Number of muon events kept: " << numbPassedEvents << std::endl;
    Float_t frac = numbPassedEvents / numberMuonEvents;
    std::cout << "Fraction of muon events kept: " << frac << std::endl;
    return(numbPassedEvents);
}
