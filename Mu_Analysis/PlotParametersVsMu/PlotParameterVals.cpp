#include "TGraphErrors.h"
#include "TMultiGraph.h"


void PlotParametersVsMu(){
    TCanvas *c1 = new TCanvas("c1","Fit Parameters versus Mu");
    c1->SetGrid();

    TMultiGraph *mg = new TMultiGraph();
    mg->SetTitle("Fit Parameters Versus Mu");


    const Int_t n = 7;
    //Double_t intercept[n],slope[n],sigma[n],mu[n];
    Double_t mu[n] = {10,20,30,40,50,60,70};

    Double_t intercept[n] = {-7.58999,-3.25036,-2.84429,-1.82258,-1.26243,7.67782,-0.33278};
    Double_t intercept_err[n] = {3.31817,0.707999,0.0209936,0.286969,0.569592,2.1684823.9325};

    Double_t slope[n] = {0.57763,0.339169,0.335548,0.296387,0.27781,0.181505,0.238594};
    Double_t slope_err[n] = {0.0532006,0.707107,2.8289e-24,0.00294974,0.00545491,0.0177855,0.188133};

    Double_t sigma[n] = {8.22652,8.72053,8.63395,8.91276,9.16529,7.07223,10.2882};
    Double_t sigma_err[n] = {0.731322,0.707108,2.74936e-23,0.0809516,0.167048,-.687461,8.11952};

    TGraph* interceptGraph = new TGraphErrors(n,mu,intercept);
    interceptGraph->SetLineColor(4);
    TGraph* slopeGraph = new TGraphErrors(n,mu,slope);
    slopeGraph->SetLineColor(2);
    TGraph* sigmaGraph = new TGraphErrors(n,mu,sigma);
    sigmaGraph->SetLineColor(6);

    mg->Add(interceptGraph);
    mg->Add(slopeGraph);
    mg->Add(sigmaGraph);

    interceptGraph->Draw("ALP");
    slopeGraph->Draw("SAME");
    sigmaGraph->Draw("SAME");
}


