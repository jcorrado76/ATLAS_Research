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


Int_t threeEfficiencies( const TString& algA , const TString& algB, const Float_t metl1thresh = 0.0, 
        const Float_t frac = 1e-4, const TString folder = "", 
        const TString& myFileName = "ZeroBias2016R307195R311481Runs56.root", 
        const TString& muonFilename = "PhysicsMain2016.Muons.noalgL1XE45R3073065R311481Runs9B.root")
{
    /*
    Makes TEFFICIENCY Plots ONCE
    TEFFICIENCY ALG A AT 10^(-4)
    TEFFICIENCY ALG b AT 10^(-4)
    TEFFICIENCY ALG c AT 10^(-4)
    */

    Float_t determineThresh( const TString&, const Float_t, Float_t, const TString&);
    TH1F* computeTarget(TH1F*,TH1F*,Int_t);
    Float_t computeThresh(TH1F*,Float_t,Int_t);
    Float_t determineCombinedEventsKept( const TString&, const Float_t, const TString&, 
            const Float_t, const Float_t, const TString&);

    gROOT->ProcessLine("gROOT->Reset();");
    gROOT->ProcessLine("gROOT->SetBatch(kTRUE);");
    gROOT->ProcessLine("gROOT->Time();");

    TString path = "../myData/"+muonFilename;
    TFile * muonFile = TFile::Open(path, "READ");
    TTree* myMuonTree = NULL;
    muonFile->GetObject("tree",myMuonTree);
    std::cout << "Muon Data being used to compute algorithm efficiency: " << path << std::endl;
    Int_t muonNentries = myMuonTree->GetEntries();
    Int_t muonNbins = 50;
    Int_t nbins = 400;
    Double_t muonMetMin = 0.0;
    Double_t muonMetMax = 250.0;
    Int_t numRndm = 0;
    Int_t counter1 = 0;
    Int_t counter2 = 0;
    Int_t counter3 = 0;
    Double_t metMin = 0.0;
    Double_t metMax = 250.0;
    Int_t passRndm, numPassMuon,passmuon,cleanCutsFlag,recalBrokeFlag;
    Float_t algAMET,algBMET,metoffrecal,offrecal_met,offrecal_mex,offrecal_mey,offrecalmuon_mex,
            offrecalmuon_mey, acthresh,bcthresh,metl1;

    //myMuonTree->SetBranchAddress("passmu24med", &passmuon);
    myMuonTree->SetBranchAddress("passmu26med", &passmuon);
    myMuonTree->SetBranchAddress("passcleancuts", &cleanCutsFlag);
    myMuonTree->SetBranchAddress("recalbroke", &recalBrokeFlag);
    myMuonTree->SetBranchAddress("metoffrecal", &offrecal_met);
    myMuonTree->SetBranchAddress("mexoffrecal", &offrecal_mex);
    myMuonTree->SetBranchAddress("meyoffrecal", &offrecal_mey);
    myMuonTree->SetBranchAddress("mexoffrecalmuon", &offrecalmuon_mex);
    myMuonTree->SetBranchAddress("meyoffrecalmuon", &offrecalmuon_mey);

    std::cout << "MuonNentries: " << muonNentries << std::endl;

    path = "../myData/"+ myFileName;
    TFile * myData = TFile::Open(path, "READ");
    TTree* myTree = NULL;
    myData->GetObject("tree",myTree);
    Int_t nentries = myTree->GetEntries();


    Float_t algAMETx1thresh,algBMETx1thresh;
    Float_t algAMETx2thresh,algBMETx2thresh;
    Float_t algAMETx3thresh,algBMETx3thresh;
    TString xlabel = "MET [GeV]";
    TString yaxis = "Events";
    myTree->SetBranchAddress("passrndm", &passRndm); // get pass rndm flag
    myTree->SetBranchAddress(algA,&algAMET);
    myTree->SetBranchAddress(algB,&algBMET);
    myTree->SetBranchAddress("metl1",&metl1);
    TH1F *algAMETHist = new TH1F("algA", "algA", nbins, metMin, metMax);
    TH1F *algBMETHist = new TH1F("algB", "algB", nbins, metMin, metMax);
    TH1F *algAMETtarget = new TH1F("cumu1", "algAcumu", nbins, metMin, metMax);
    TH1F *algBMETtarget = new TH1F("cumu2", "algBcumu", nbins, metMin, metMax);

    Float_t algAThresh = determineThresh(algA,frac,metl1thresh,myFileName);
    Float_t algBThresh = determineThresh(algB,frac,metl1thresh,myFileName);

    std::cout << "Returned to threeEfficiencies.c" << std::endl;
    std::cout << "algAThresh: " << algAThresh << std::endl;
    std::cout << "algBThresh: " << algBThresh << std::endl;
    std::cout << "Using METL1THRESH: " << metl1thresh << std::endl;

    numRndm = 0 ;
    std::cout << "algA==algB? " << (algA==algB) << std::endl;
    if (algA == algB)
    {
	for (Int_t k = 0; k < nentries; k++)
	{
	    myTree->GetEntry(k);
        //ADDITIONAL CHECK ON METL1 TO GET CORRECT INDIVIDUAL FRACTIONS
	    if (passRndm > 0.1 && metl1 > metl1thresh)
	    {
		algAMET = algBMET;
		//numRndm++;
		algAMETHist->Fill(algAMET);
		algBMETHist->Fill(algBMET);
	    }
        if (passRndm > 0.1)
        {
            numRndm++;
        }
	}
    }
    else
    {
	for (Int_t k = 0; k < nentries; k++) //determine numRndm and fill histograms
	{
	    myTree->GetEntry(k);
	    if (passRndm > 0.1 && metl1 > metl1thresh)
	    {
		//numRndm++;
		algAMETHist->Fill(algAMET);
		algBMETHist->Fill(algBMET);
	    }
        if (passRndm > 0.1)
        {
            numRndm++;
        }
	}
    }
    std::cout << "numRndm: " << numRndm << std::endl;
    std::cout << "frac " << frac << std::endl;
    std::cout << "numCombined to keep: " << numRndm * frac << std::endl;
    Float_t lwrbnd = 0.5*frac;
    Float_t uprbnd = 0.13;
    Float_t eps = 25.0;

    std::cout << "Entering bisection to determine individual fractions" << std::endl;
    std::cout << "Lower Bound: " << lwrbnd << std::endl;
    std::cout << "Midpoint: " << (lwrbnd+uprbnd)/2. << std::endl;
    std::cout << "Upper Bound: " << uprbnd << std::endl;
    std::cout << "Epsilon: " << eps << std::endl;
    Float_t x1,x3; //thresholds of individual algorithms
    Float_t f1,f2,f3 = 0; //number of events kept
    x1 = lwrbnd;
    x3 = uprbnd;
    Float_t initialGuess = ( x1 + x3 ) / 2.0;
    Float_t firstGuess = initialGuess;
    Float_t numKeepx1 = numRndm * x1;
    Float_t numKeepx2 = numRndm * initialGuess;
    Float_t numKeepx3 = numRndm * x3;
    
    
    computeTarget(algAMETHist,algAMETtarget,nbins);
    computeTarget(algBMETHist,algBMETtarget,nbins);

    algAMETx1thresh = computeThresh(algAMETtarget, numKeepx1, nbins);
    algBMETx1thresh = computeThresh(algBMETtarget, numKeepx1, nbins);
    algAMETx2thresh = computeThresh(algAMETtarget, numKeepx2, nbins);
    algBMETx2thresh = computeThresh(algBMETtarget, numKeepx2, nbins);
    algAMETx3thresh = computeThresh(algAMETtarget, numKeepx3, nbins);
    algBMETx3thresh = computeThresh(algBMETtarget, numKeepx3, nbins);

    std::cout << "algAx1Thresh: " << algAMETx1thresh << std::endl;
    std::cout << "algBx1Thresh: " << algBMETx1thresh << std::endl;
    std::cout << "metl1thresh : " << metl1thresh << std::endl;
    if (algA==algB)
    {
        for (Int_t i  = 0 ; i < nentries ;i++) //determine events kept at each guess
        {
            myTree->GetEntry(i);
            if (passRndm > 0.5)
            {
                algAMET = algBMET;
                if ((algBMET > algBMETx1thresh) && (metl1 > metl1thresh))
                {
                    counter1++;
                }
                if ((algBMET > algBMETx2thresh) && (metl1 > metl1thresh))
                {
                    counter2++;
                }
                if ((algBMET > algBMETx3thresh) && (metl1 > metl1thresh))
                {
                    counter3++;
                }
            }
        }
    }
    else
    {
        for (Int_t i  = 0 ; i < nentries ;i++) //determine events kept at each guess
        {
        myTree->GetEntry(i);
            if (passRndm > 0.5)
            {
                if ((algAMET > algAMETx1thresh) && (algBMET > algBMETx1thresh) && (metl1 > metl1thresh))
                {
                counter1++;
                }
                if ((algAMET > algAMETx2thresh) && (algBMET > algBMETx2thresh) && (metl1 > metl1thresh))
                {
                counter2++;
                }
                if ((algAMET > algAMETx3thresh) && (algBMET > algBMETx3thresh) && (metl1 > metl1thresh))
                {
                counter3++;
                }
            }
        }
    }

    std::cout << "At x1 = " << x1 << " counter1: " << counter1 << " events" << std::endl;
    f1 = (Float_t) counter1 / (Float_t) numRndm;
    std::cout << "f1: " << f1 << std::endl;

    std::cout << "At x2 = " << initialGuess << " counter2: " << counter2 << " events" << std::endl;
    f2 = (Float_t) counter2 / (Float_t) numRndm;
    std::cout << "f2: " << f2 << std::endl;

    std::cout << "At x3 = " << x3 << " counter3: " << counter3 << " events" << std::endl;
    f3 = (Float_t) counter3 / (Float_t) numRndm;
    std::cout << "f3: " << f3 << std::endl;

    Float_t inputArray[100];
    Float_t outputArray[100];
    Float_t numEventsArray[100];
    Float_t thresholdAarray[100];
    Float_t thresholdBarray[100];

    inputArray[0] = x1;
    inputArray[2] = initialGuess;
    inputArray[1] = x3;
    outputArray[0] = f1;
    outputArray[2] = f2;
    outputArray[1] = f3;
    numEventsArray[0] = counter1;
    numEventsArray[2] = counter2;
    numEventsArray[1] = counter3;
    thresholdAarray[0] = (Float_t) algAMETx1thresh;
    thresholdAarray[2] = (Float_t) algAMETx2thresh;
    thresholdAarray[1] = (Float_t) algAMETx3thresh;
    thresholdBarray[0] = (Float_t) algBMETx1thresh;
    thresholdBarray[2] = (Float_t) algBMETx2thresh;
    thresholdBarray[1] = (Float_t) algBMETx3thresh;

    //OLD CONDITION: While ((abs( numRndm * frac - counter2) > eps))

    Int_t j = 0 ;
    Int_t imax = 30;
    Float_t binWidth = (metMax - metMin)/ nbins;
    Float_t algAThreshDiff;
    Float_t algBThreshDiff;

do{
    j++;
    std::cout << "Inside iteration number: " << j << std::endl;
    if ( (f1-frac)*(f2-frac) < 0 ) //root is in left half of interval
    {
      std::cout << "Root is to the left of " << initialGuess << std::endl;
      f3 = f2;
      x3 = initialGuess;
    }
    else //root is in right half of  interval
    {
      std::cout << "Root is to the right of " << initialGuess << std::endl;
      f1 = f2;
      x1 = initialGuess;
    }
    initialGuess = ( x1 + x3 ) / 2.0;
    inputArray[j+2] = initialGuess;
    std::cout << "New Guess: " << initialGuess << std::endl;
    std::cout << "numRndm: " << numRndm << std::endl;
    numKeepx2 = numRndm * initialGuess;
    std::cout << "numKeepx2: " << numKeepx2 << std::endl;
    std::cout << "algAtarget"  << " nentries: " << algAMETtarget->GetEntries() << std::endl;
    std::cout << "algBtarget"  << " nentries: " << algBMETtarget->GetEntries() << std::endl;
    algAMETx2thresh = computeThresh(algAMETtarget, numKeepx2, nbins);
    algBMETx2thresh = computeThresh(algBMETtarget, numKeepx2, nbins);
    thresholdAarray[j+2] = (Float_t) algAMETx2thresh;
    thresholdBarray[j+2] = (Float_t) algBMETx2thresh;

    counter2 = 0;
    if (algA==algB)
    {
	for (Int_t i  = 0 ; i < nentries ;i++)
	{
	  myTree->GetEntry(i);
	  algAMET=algBMET;
	  if ((passRndm > 0.1) && (algBMET > algBMETx2thresh) && (metl1 > metl1thresh))
	  {
	    counter2++;
	  }
	}
    }
    else
    {
	for (Int_t i  = 0 ; i < nentries ;i++)
	{
	  myTree->GetEntry(i);
	  if ((passRndm > 0.1) && (algAMET > algAMETx2thresh) && (algBMET > algBMETx2thresh) && (metl1 > metl1thresh))
	  {
	    counter2++;
	  }
	}
    }
    numEventsArray[j+2] = counter2;
    std::cout << "algAMETx2thresh: " << algAMETx2thresh << std::endl;
    std::cout << "algBMETx2thresh: " << algBMETx2thresh << std::endl;
    std::cout << "Counter2: " << counter2 << std::endl;
    f2 = (Float_t) counter2 / (Float_t) numRndm;
    std::cout << "f2: " << f2 << std::endl;
    std::cout << "Condition: " << abs(numRndm * frac - counter2) << " > " << eps << std::endl;
    outputArray[j+2] = f2;

    algAThreshDiff = (Float_t) thresholdAarray[j+2] - (Float_t) thresholdAarray[j+1];
    algBThreshDiff = (Float_t) thresholdBarray[j+2] - (Float_t) thresholdBarray[j+1];

    algAThreshDiff = abs(algAThreshDiff);
    algBThreshDiff = abs(algBThreshDiff);

  std::cout << "algA current threshold: " << Form("%.7f",thresholdAarray[j+2]) << std::endl;
  std::cout << "algA previous threshold: " << Form("%.7f",thresholdAarray[j+1]) << std::endl;
  std::cout << "algB current threshold: " << Form("%.7f",thresholdBarray[j+2]) << std::endl;
  std::cout << "algB previous threshold: " << Form("%.7f",thresholdBarray[j+1]) << std::endl;
  std::cout << "binWidth: " << binWidth << std::endl;

}while ( abs( counter2 - (numRndm * frac) ) > eps && (abs(algAThreshDiff) > binWidth) && (abs(algBThreshDiff) > binWidth) && ( j <= imax ) );

//first condition: abs(counter2-(numRndm*frac)) <= eps ||
  if ( abs( counter2 - (numRndm * frac) ) <= eps || abs(algAThreshDiff) <= binWidth || abs(algBThreshDiff) <= binWidth)
  {
    std::cout << "A root at x = " <<  initialGuess << " was found to within one bin: " << binWidth << " GeV"
              << " in " << j << " iterations" << std::endl;
    std::cout << "The number of combined events kept is  " << f2 * numRndm << std::endl;
    std::cout << "The fraction of combined events kept is  " << f2 << std::endl;
  }
  else{
    std::cout << "No root found; max iterations exceeded" << std::endl;
  }

acthresh = algAMETx2thresh;
bcthresh = algBMETx2thresh;

TString cstring = "TEfficiency using " + algA + " at thresh " + Form(" %.2f", acthresh) + " and " + algB +
" at thresh " + Form(" %.2f", bcthresh);
TString astring = algA + " TEfficiency at thresh of " + Form(" %.2f", algAThresh);
TString bstring = algB + " TEfficiency at thresh of " + Form(" %.2f", algBThresh);

TEfficiency* Ateff  = new TEfficiency(astring , "Efficiency", muonNbins, muonMetMin, muonMetMax);
TEfficiency* Bteff  = new TEfficiency(bstring , "Efficiency", muonNbins, muonMetMin, muonMetMax);
TEfficiency* Cteff  = new TEfficiency(cstring,  "Efficiency", muonNbins, muonMetMin, muonMetMax);
Float_t algAmuonMET = 0;
Float_t algBmuonMET = 0;
myMuonTree->SetBranchAddress(algA,&algAmuonMET);
myMuonTree->SetBranchAddress(algB,&algBmuonMET);
for (Int_t l = 0 ; l < nentries ; l++)
{
    myMuonTree->GetEntry(l);
    //CLEANCUTS AND RECALBROKE
    if (algA == algB)
    {
	algAmuonMET = algBmuonMET;
	if (passmuon > 0.1 && cleanCutsFlag > 0.1 && recalBrokeFlag < 0.1)
	{
	    Float_t metnomu = sqrt(((offrecal_mex - offrecalmuon_mex) * (offrecal_mex - offrecalmuon_mex)) +
	    ((offrecal_mey - offrecalmuon_mey)*(offrecal_mey - offrecalmuon_mey))); //compute metnomu
	    Ateff->Fill(algAmuonMET > algAThresh, metnomu);
	    Bteff->Fill(algBmuonMET > algBThresh, metnomu);
	    Cteff->Fill(((algAmuonMET > acthresh) && (algBmuonMET > bcthresh) ), metnomu);
	}
    }
    else
    {
	if (passmuon > 0.1 && cleanCutsFlag > 0.1 && recalBrokeFlag < 0.1)
	{
	    Float_t metnomu = sqrt(((offrecal_mex - offrecalmuon_mex) * (offrecal_mex - offrecalmuon_mex)) +
	    ((offrecal_mey - offrecalmuon_mey)*(offrecal_mey - offrecalmuon_mey))); //compute metnomu
	    Ateff->Fill(algAmuonMET > algAThresh, metnomu);
	    Bteff->Fill(algBmuonMET > algBThresh, metnomu);
	    Cteff->Fill(((algAmuonMET > acthresh) && (algBmuonMET > bcthresh) ), metnomu);
	}
    }
}

std::cout << "Running an external check macro to verify number of events kept at fraction determined by the bisection algorithm..." << std::endl;
std::cout << "ENTERING determineCombinedEventsKept.c" <<std::endl;
Float_t eventsCombined = determineCombinedEventsKept( algA , acthresh , algB , bcthresh , metl1thresh , myFileName );

TCanvas* efficiencyCanvas = new TCanvas("Efficiency Canvas", "Efficiency Canvas");

if (algA==algB)
{
    Ateff->SetLineColorAlpha(kBlue,0.35);
    Cteff->SetLineColorAlpha(kRed,0.65);
    Bteff->SetLineColorAlpha(kGreen,0.45);
}
else
{
    Ateff->SetLineColor(kBlue);
    Cteff->SetLineColor(kRed);
    Bteff->SetLineColor(kGreen);
}

Ateff->Draw();
Bteff->Draw("same");
Cteff->Draw("same");



TLegend *legend = new TLegend(.1,.7,.48,.9);
legend->AddEntry(Ateff, astring);
legend->AddEntry(Bteff, bstring);
legend->AddEntry(Cteff, cstring);
legend->Draw();
path = "./TEfficienciesPics/" + folder + "/" + algA + "_and_" + algB + "_efficiencies.pdf";
efficiencyCanvas->Print(path);

TString logFileName = "./TEfficienciesPics/" + folder + "/" + algA + "_and_" + algB + "_efficiencies.txt";
std::cout << "Generating log file: " << logFileName << std::endl;
const char* newLogFileName = logFileName.Data(); //need to go inside and grab data to caste to a data type so i can open ofstream
ofstream logFile;
logFile.open(newLogFileName, std::fstream::out);
if(logFile) std::cout << "logFile Successfully Opened" << std::endl;

logFile << "Algorithms: " << algA << "\t" << algB << "\r\n";
logFile << "ZEROBIAS DATAFILE: " << myFileName << "\r\n";
logFile << "Zerboias Nentries: " << nentries << "\r\n";
logFile << "METL1 THRESH: " << metl1thresh << "\r\n";
logFile << "MUON DATAFILE: " << muonFilename << "\r\n";
logFile << "Muon nentries: " << muonNentries << "\r\n";
logFile << "Nbins: " << nbins << "\t METMIN: " << metMin << "\t METMAX: " << metMax << "\r\n";
logFile << "Fraction to keep for bisection: " << frac << "\r\n";
logFile << "Fraction times numRndm: " << frac * numRndm << "\r\n";
logFile << "Threshold for " + algA + " to keep fraction by itself: " << algAThresh << "\r\n";
logFile << "Threshold for " + algB + " to keep fraction by itself: " << algBThresh << "\r\n";
logFile << "Epsilon tolerance for bisection accuracy: " << eps << " events" << "\r\n";
logFile << "Bisection Information: " << "\r\n";
logFile << "Iteration Number : " << "\tIndividual Fraction: \t" << "Combined Fraction Kept: \t" << "Number Events Kept: \t" <<
"Threshold for " + algA + '\t' << "Threshold for " + algB +'\t' << "\r\n";
logFile << "x1\t\t\t" << inputArray[0] << "\t\t\t" << outputArray[0] << "\t\t\t" << numEventsArray[0] << "\t\t\t" <<
algAMETx1thresh << "\t\t\t" << algBMETx1thresh << "\r\n";
logFile << "x2\t\t\t" << inputArray[2] << "\t\t\t" << outputArray[2] << "\t\t\t" << numEventsArray[2] << "\t\t\t" <<
algAMETx2thresh << "\t\t\t" << algBMETx2thresh <<"\r\n";
logFile << "x3\t\t\t" << inputArray[1] << "\t\t\t" << outputArray[1] << "\t\t\t" << numEventsArray[1] << "\t\t\t" <<
algAMETx3thresh << "\t\t\t" << algBMETx3thresh <<"\r\n";
for (int m = 1; m < j+1 ; m++)
{
  logFile << Form("I%d",m) << "\t\t\t" << Form("%.7f",inputArray[m+2]) << "\t\t" << Form("%.7f",outputArray[m+2])
  << "\t\t\t" << Form("%.7f",numEventsArray[m+2]) << "\t\t" << Form("%.7f",thresholdAarray[m+2]) << "\t\t" <<
  Form("%.7f",thresholdBarray[m+2]) << "\r\n";
}
logFile << "Number of combined events kept, as determined by verification macro 'determineCombinedEventsKept.c': "
<< eventsCombined << "\r\n";
logFile.close();
return(0);
}

//HELPER FUNCTIONS
TH1F* computeTarget(TH1F* hist , TH1F* target, Int_t nbins)
{
	Float_t rightHandSum = 0;
	for (Int_t t = nbins; t >= 0; t--)
	{
		rightHandSum = hist->Integral(t,nbins); //compute t'th target bin
		target->SetBinContent(t, rightHandSum);
	}
	return(target);
}

Float_t computeThresh(TH1F* target, Float_t numKeep, Int_t nbins)
{
    std::cout << "Targethist name: " << target->GetName() << " Nentries: " << target->GetEntries() << std::endl;
	Float_t thresh = 0;
	for (Int_t t = nbins; t >= 0; t--)
	{
        std::cout << "bincontent at t=" << t << ": " << target->GetBinContent(t) << std::endl;
		if (((target->GetBinContent(t) - (numKeep)) > 0) != ((target->GetBinContent(t + 1) - (numKeep)) > 0))
		{
			thresh = target->GetBinCenter(t);
		}
	}
	return(thresh);

}



Float_t determineThresh( const TString& all = "y", const Float_t frac = (1.e-4), Float_t metl1thresh = 0.0, const TString& dataFile = "ZeroBias2016R307195R311481Runs56.root")
{
	gROOT->ProcessLine("gROOT->Reset();");
	cout << "Entering determineThresh.c" << std::endl;
	TString fileName = "../myData/" + dataFile;
	std::cout << "DATAFILE: " << fileName << std::endl;
	TFile *myFile = TFile::Open(fileName, "READ");
	TTree *tree = (TTree*)myFile->Get("tree");
	Int_t nentries = tree->GetEntries();
	Int_t nbins = 400;
	Int_t numRndm = 0;
	Int_t passRndm;
	Double_t metMin = 0.0;
	Double_t metMax = 500.0;
	Float_t metl1, metcell, metmht, mettopocl, mettopoclps, mettopoclpuc, metoffrecal,indeterminate,
	metcellthresh, metmhtthresh, mettopoclthresh, mettopoclpsthresh, mettopoclpucthresh,rightHandSum;
	TString xlabel = "MET [GeV]";
	TString yaxis = "Events";
	tree->SetBranchAddress("passrndm", &passRndm);
	std::cout << "FRACTION: " << frac << std::endl;
	std::cout << "NENTRIES: " << nentries << std::endl;
	Float_t indeterminateThresh = 0;

	if (all == "y")
	{
		TH1F *metl1Hist         = new TH1F("metl1", "metl1", nbins, metMin, metMax);;
		TH1F *metcellHist       = new TH1F("metcell", "metcell", nbins, metMin, metMax);
		TH1F *metmhtHist        = new TH1F("metmht", "metmht", nbins, metMin, metMax);
		TH1F *mettopoclHist     = new TH1F("mettopocl", "mettopocl", nbins, metMin, metMax);
		TH1F *mettopoclpsHist   = new TH1F("mettopoclps", "mettopoclps", nbins, metMin, metMax);
		TH1F *mettopoclpucHist  = new TH1F("mettopoclpuc", "mettopoclpuc", nbins, metMin, metMax);
		TH1F *metl1target         = new TH1F("cumu1", "cumu", nbins, metMin, metMax);;
		TH1F *metcelltarget       = new TH1F("cumu2", "cumu", nbins, metMin, metMax);
		TH1F *metmhttarget        = new TH1F("cumu3", "cumu", nbins, metMin, metMax);
		TH1F *mettopocltarget     = new TH1F("cumu4", "cumu", nbins, metMin, metMax);
		TH1F *mettopoclpstarget   = new TH1F("cumu5", "cumu", nbins, metMin, metMax);
		TH1F *mettopoclpuctarget  = new TH1F("cumu6", "cumu", nbins, metMin, metMax);
		tree->SetBranchAddress("metl1", &metl1);
		tree->SetBranchAddress("metcell", &metcell);
		tree->SetBranchAddress("metmht", &metmht);
		tree->SetBranchAddress("mettopocl", &mettopocl);
		tree->SetBranchAddress("mettopoclps", &mettopoclps);
		tree->SetBranchAddress("mettopoclpuc", &mettopoclpuc);
		tree->SetBranchAddress("metoffrecal", &metoffrecal);
		std::cout << "ALL ALGORITHMS SELECTED..." << std::endl;
		for (Int_t k = 0; k < nentries; k++)
		{
			tree->GetEntry(k);
			if ((passRndm > 0.1) && (metl1 > metl1thresh))
			{
			    //numRndm++;
				metl1Hist->Fill(metl1);
				metcellHist->Fill(metcell);
				metmhtHist->Fill(metmht);
				mettopoclHist->Fill(mettopocl);
				mettopoclpsHist->Fill(mettopoclps);
				mettopoclpucHist->Fill(mettopoclpuc);
			}
            if (passRndm > 0.5)
            {
                numRndm++;
            }
		}
	
		Float_t numKeep = numRndm * frac;
	
		computeTarget(metl1Hist,metl1target,nbins);
		metl1thresh = computeThresh(metl1target, numKeep, nbins);
	
		computeTarget(metcellHist,metcelltarget,nbins);
		metcellthresh = computeThresh(metcelltarget, numKeep, nbins);
	
		computeTarget(metmhtHist,metmhttarget,nbins);
		metmhtthresh = computeThresh(metmhttarget, numKeep, nbins);
	
		computeTarget(mettopoclHist,mettopocltarget,nbins);
		mettopoclthresh = computeThresh(mettopocltarget, numKeep, nbins);
	
		computeTarget(mettopoclpsHist,mettopoclpstarget,nbins);
		mettopoclpsthresh = computeThresh(mettopoclpstarget, numKeep, nbins);
	
		computeTarget(mettopoclpucHist,mettopoclpuctarget,nbins);
		mettopoclpucthresh = computeThresh(mettopoclpuctarget, numKeep, nbins);
	
		std::cout << "METL1 THRESHOLD: " << metl1thresh << std::endl;
		std::cout << "METCELL THRESHOLD: " << metcellthresh << std::endl;
		std::cout << "METMHT THRESHOLD: " << metmhtthresh << std::endl;
		std::cout << "METTOPOCL THRESHOLD: " << mettopoclthresh << std::endl;
		std::cout << "METTOPOCLPS THRESHOLD: " << mettopoclpsthresh << std::endl;
		std::cout << "METTOPOCLPUC THRESHOLD: " << mettopoclpucthresh << std::endl;
	}

	if (all != "y") //only compute thresh for one alg
	{
		TH1F *indeterminateHist = new TH1F(all, all, nbins, metMin, metMax);
		TH1F *indeterminatetarget = new TH1F("indeterminatecumu", "indeterminatecumu", nbins, metMin, metMax);
		tree->SetBranchAddress(all,&indeterminate);
		tree->SetBranchAddress("metl1",&metl1);
		std::cout << all << " SELECTED..." << std::endl;
		std::cout << "Computing number to keep after cutting on metl1 at thresh: " << metl1thresh << std::endl;
		for (Int_t k = 0; k < nentries; k++)
		{
			tree->GetEntry(k);
			if ((passRndm > 0.1) && (metl1 >= metl1thresh))
			{
			    //numRndm++;
				indeterminateHist->Fill(indeterminate);
			}
            if (passRndm > 0.5)
            {
                numRndm++;
            }
		}
		computeTarget(indeterminateHist,indeterminatetarget,nbins);
		Float_t numKeep = numRndm * frac;
		indeterminateThresh = computeThresh(indeterminatetarget, numKeep, nbins);
		std::cout << all << " THRESHOLD: " << indeterminateThresh << std::endl;
	}
	std::cout << "Number of events that should have been kept: " << frac * numRndm << std::endl;
	std::cout << "Checking how many events are kept by the alg at the determined threshold..." << std::endl;
	int counter=0;
	for (int l = 0 ; l < nentries ; l++)
	{
		tree->GetEntry(l);
		if ((passRndm > 0.5) && ((indeterminate >= ( indeterminateThresh - ( ( metMax - metMin ) / ( 2 * nbins ))))))//count the event if its geq left edge of bin (we use center for thresh)
		{
			counter++;
		}
	}
	myFile->Close();
	std::cout << "Number of events counted above threshold: " << counter << std::endl;
	return(indeterminateThresh);
}





Float_t determineCombinedEventsKept( const TString& algA, const Float_t threshA, const TString& algB, const Float_t threshB, const Float_t metl1thresh = 0.0, const TString& fileName = "ZeroBias2016new.13Runs.root")
{
    gROOT->ProcessLine("gROOT->Reset();");
    std::cout << "Determining fraction of zero bias events kept when using combined algorithm of " << algA << " at: " << threshA << " and "
    << algB << " at: " << threshB << std::endl;
    TString path = "../myData/"+fileName;
    TFile * myFile = TFile::Open(path, "READ");
    TTree* tree = (TTree*)myFile->Get("tree");
    Int_t nbins = 400;
    Double_t metMin = 0.0;
    Double_t metMax = 500.0;
    Int_t nentries = tree->GetEntries();
    Float_t algAMET, algBMET,metl1;
    Int_t passRndm;
    tree->SetBranchAddress("passrndm",&passRndm);
    tree->SetBranchAddress(algA,&algAMET);
    tree->SetBranchAddress(algB,&algBMET);
    tree->SetBranchAddress("metl1",&metl1);
    Int_t counter = 0;
    Int_t numRndm = 0;
if (algA==algB)
{
    for (Int_t i  = 0 ; i < nentries ;i++)
      {
	tree->GetEntry(i);
	algAMET=algBMET;
	if (passRndm >0.1)
	{
	  numRndm++;
	}
	if ((passRndm > 0.1) && (algAMET > threshA) && (algBMET > threshB) && (metl1 > metl1thresh))
	{
	  counter++;
	}
      }
}
else
{
    for (Int_t i  = 0 ; i < nentries ;i++)
      {
	tree->GetEntry(i);
	if (passRndm >0.1)
	{
	  numRndm++;
	}
	if ((passRndm > 0.1) && (algAMET > threshA) && (algBMET > threshB) && (metl1 > metl1thresh))
	{
	  counter++;
	}
      }
}
std::cout << "Combined alg kept: " << counter << " events" << std::endl;
Float_t frac = (Float_t) counter / (Float_t) numRndm;
std::cout << "Fraction of passRndm events: " << frac << std::endl;
return(counter);
}

