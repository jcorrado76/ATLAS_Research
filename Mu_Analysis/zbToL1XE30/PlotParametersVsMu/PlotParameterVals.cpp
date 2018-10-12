#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TH1F.h"
#include "TGaxis.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TLegend.h"
#include "TList.h"
#include "TFile.h"
#include "TKey.h"
#include "TClass.h"
#include "TEfficiency.h"


TList* l = 0;
void HighlightTeff(TVirtualPad *pad , TObject *obj , Int_t ihp , Int_t y);
void PlotParameterVals(){

    l = new TList();

    TFile *mu_analysis_file = TFile::Open("../Root_Files/mu_analysis.root");
    
    TDirectory* efficiency_dir = mu_analysis_file->GetDirectory("efficiency_curves");
    TIter next(efficiency_dir->GetListOfKeys());
    TKey *key;

    while ((key = (TKey*)next())){
            TClass *cl = gROOT->GetClass(key->GetClassName());
            if (!cl->InheritsFrom("TEfficiency")) continue;
            TEfficiency * teff = (TEfficiency*)key->ReadObj();
            l->Add(teff);
    }

    TCanvas *Canvas = new TCanvas("Canvas","Fit Parameters versus Mu",200,10,700,900);
    Canvas->SetFillColor(42);
    Canvas->Divide(1,2);

    Canvas->cd(1);
    //gPad->SetFrameFillColor(33);
    gPad->SetGrid();
    TMultiGraph *mg = new TMultiGraph();
    mg->SetTitle("Fit Parameters Versus Mu");


    const Int_t n = 7;
    Double_t mu[n] = {10,20,30,40,50,60,70};

    Double_t intercept[n] = {-7.58999,-3.25036,-2.84429,-1.82258,-1.26243,7.67782,-0.33278};
    Double_t intercept_yerr[n] = {3.31817,0.707999,0.0209936,0.286969,0.569592,2.16848,23.9325};
    Double_t intercept_xerr[n] = {0};

    Double_t slope[n] = {0.57763,0.339169,0.335548,0.296387,0.27781,0.181505,0.238594};
    Double_t slope_yerr[n] = {0.0532006,0.707107,2.8289e-24,0.00294974,0.00545491,0.0177855,0.188133};
    Double_t slope_xerr[n] = {0};

    Double_t sigma[n] = {8.22652,8.72053,8.63395,8.91276,9.16529,7.07223,10.2882};
    Double_t sigma_yerr[n] = {0.731322,0.707108,2.74936e-23,0.0809516,0.167048,-.687461,8.11952};
    Double_t sigma_xerr[n] = {0};

    TGraphErrors* interceptGraph = new TGraphErrors(n,mu,intercept,intercept_xerr,intercept_yerr);
    interceptGraph->SetMarkerStyle(20);
    interceptGraph->SetLineColor(4);
    interceptGraph->SetMarkerColor(4);
    interceptGraph->SetMarkerSize(1.5);

    TGraphErrors* slopeGraph = new TGraphErrors(n,mu,slope,slope_xerr,slope_yerr);
    slopeGraph->SetMarkerStyle(21);
    slopeGraph->SetLineColor(2);
    slopeGraph->SetMarkerColor(2);
    slopeGraph->SetMarkerSize(1.5);

    TGraphErrors* sigmaGraph = new TGraphErrors(n,mu,sigma,sigma_xerr,sigma_yerr);
    sigmaGraph->SetMarkerStyle(22);
    sigmaGraph->SetLineColor(6);
    sigmaGraph->SetMarkerColor(6);
    sigmaGraph->SetMarkerSize(1.5);

    mg->Add(interceptGraph);
   // mg->Add(slopeGraph);
    mg->Add(sigmaGraph);

    // DRAW THE TWO GRAPHS 
    // A means draw axis around the graph
    // C means a smooth curve is drawn
    // P means draw the markers
    mg->Draw("ACP");
    mg->GetXaxis()->SetTitle("Mu");
    mg->GetYaxis()->SetTitle("Value of Parameter");

    // SCALE THE SLOPE GRAPH
   Float_t scale = gPad->GetUymax() ;
   std::cout << "GetUymax(): " << gPad->GetUymax() << std::endl;
   for (int i = 0 ; i< n ; i++){
       slopeGraph->GetY()[i] *= gPad->GetUymax();
   }

   // CREATE NEW RHS AXIS
   // Remove A here because it'll mess with the axes
   slopeGraph->Draw("SAME CP");
   TGaxis *axis = new TGaxis( gPad->GetUxmax() , gPad->GetUymin(), gPad->GetUxmax(), gPad->GetUymax() , 0 , 1.0 , 510, "+L");
   axis->SetLineColor(kRed);
   axis->SetTextColor(kRed);
   axis->Draw("SAME");

    TLegend* legend = new TLegend(0.1,0.7,0.48,0.9);
    legend->AddEntry(interceptGraph,"Intercept");
    legend->AddEntry(slopeGraph,"Slope");
    legend->AddEntry(sigmaGraph,"Sigma");
    //legend->SetFillColor(42);
    legend->Draw();
    gPad->Modified();
    // in case if you want to set limits on plots
    //mg->GetXaxis()->SetLimits(0.0,20.0);
    //mg->SetMinimum(0.);
    //mg->SetMaximum(10.);

    slopeGraph->SetHighlight();
    interceptGraph->SetHighlight();
    sigmaGraph->SetHighlight();
    Canvas->HighlightConnect("HighlightTeff(TVirtualPad*, TObject* , Int_t , Int_t)");
    Canvas->cd(2);
    gPad->Draw();

}

void HighlightTeff( TVirtualPad *pad , TObject *obj , Int_t ihp , Int_t y){
    //if (obj != slopeGraph et cetera for the other graphs ) return;
    if (ihp == -1){
        return;
    }
    Double_t avg_intercept = -1.902488;
    Double_t avg_slope = 0.2975016;
    Double_t avg_sigma = 9.144146;
    Double_t l1cut = 30.0;
    TF1 *avg_errFunc= new TF1("AvgErrorFunc","(1./2.)*(1.+TMath::Erf(([0]*x+[1]-[3])/([2]*TMath::Sqrt(2.))))",0.0,300.0);
    avg_errFunc->SetParameter(0,avg_slope);
    avg_errFunc->SetParameter(1,avg_intercept);
    avg_errFunc->SetParameter(2,avg_sigma);
    avg_errFunc->SetParameter(3,l1cut);
    TVirtualPad *savepad = gPad;
    pad->GetCanvas()->cd(2);
    avg_errFunc->Draw();
    avg_errFunc->SetLineColor(kBlue);
    l->At(ihp)->Draw("SAME");
    gPad->Update();
    savepad->cd();
}

