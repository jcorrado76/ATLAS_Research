#include "TGraphErrors.h"
#include "TMultiGraph.h"


void PlotParametersVsMu(){
    TCanvas *c1 = new TCanvas("c1","Fit Parameters versus Mu");
    c1->SetGrid();

    TMultiGraph *mg = new TMultiGraph();
    mg->SetTitle("Fit Parameters Versus Mu");


    const int n = 7;
    //Double_t intercept[n],slope[n],sigma[n],mu[n];
    Double_t mu[n] = {10,20,30,40,50,60,70};
    Double_t intercept[n] = {-7.58999,-3.25036,-2.84429,-1.82258,-1.26243,7.67782,-0.33278};
    Double_t slope[n] = {0.57763,0.339169,0.335548,0.296387,0.27781,0.181505,0.238594};
    Double_t sigma[n] = {8.22652,8.72053,8.63395,8.91276,9.16529,7.07223,10.2882};

    TGraph* interceptGraph = new TGraphErrors(n,mu,intercept);
    TGraph* slopeGraph = new TGraphErrors(n,mu,slope);
    TGraph* sigmaGraph = new TGraphErrors(n,mu,sigma);

    interceptGraph->SetTitle("Fit Parameters versus Mu");


    interceptGraph->Draw("ALP");
    slopeGraph->Draw("SAME");
    sigmaGraph->Draw("SAME");
}


