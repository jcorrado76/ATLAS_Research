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
void plot_fit_parameters_vers_mu(){

    TFile *mu_analysis_file = TFile::Open("mu_analysis.root", "READ");
    
    TObjArray* l1xe30_efficiency_objects = 0;
    mu_analysis_file->GetObject( "l1xe30_efficiency_objects" , l1xe30_efficiency_objects );

    l = new TList();
    for ( int i = 0 ; i < l1xe30_efficiency_objects->GetLast() ; i++ ){
        l->Add( (TEfficiency*)l1xe30_efficiency_objects->At(i));
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
    std::cout << "Using number of mu bins: " << n << std::endl;
    Double_t mu[n] = {0.0};
    Double_t intercept_xerr[n] = {0};
    Double_t slope_xerr[n] = {0};
    Double_t sigma_xerr[n] = {0};

    Double_t intercept[n] = {0};
    Double_t slope[n] = {0};
    Double_t sigma[n] = {0};

    Double_t intercept_yerr[n] = {0};
    Double_t slope_yerr[n] = {0};
    Double_t sigma_yerr[n] = {0};

    Float_t avgs[3] = { 0.0 };
    Float_t intercept_sum = 0.0;
    Float_t slope_sum = 0.0;
    Float_t sigma_sum = 0.0;
    for ( int i = 0 ; i < n ; i++ ){
        mu[i] = i * 10;
        intercept[i] = ((TF1*)((TEfficiency*)l1xe30_efficiency_objects->At(i))->GetListOfFunctions()->At(0))->GetParameter("Translation");
        slope[i] = ((TF1*)((TEfficiency*)l1xe30_efficiency_objects->At(i))->GetListOfFunctions()->At(0))->GetParameter("Slope");
        sigma[i] = ((TF1*)((TEfficiency*)l1xe30_efficiency_objects->At(i))->GetListOfFunctions()->At(0))->GetParameter("Sigma");

        intercept_sum += intercept[i];
        slope_sum += slope[i];
        sigma_sum += sigma[i];
    }

    avgs[0] = intercept_sum / n;
    avgs[1] = slope_sum / n;
    avgs[2] = sigma_sum / n;

    std::cout << "Average intercept: " << avgs[0] << std::endl;
    std::cout << "Average slope: " << avgs[1] << std::endl;
    std::cout << "Average sigma: " << avgs[2] << std::endl;


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
    Canvas->HighlightConnect("HighlightTeff(TVirtualPad*, TObject* , Int_t , Int_t )");
    Canvas->cd(2);
    gPad->Draw();

}

void HighlightTeff( TVirtualPad *pad , TObject *obj , Int_t ihp , Int_t y){
    //if (obj != slopeGraph et cetera for the other graphs ) return;
    if (ihp == -1){
        return;
    }
    Double_t avg_intercept = -2.21539;
    Double_t avg_slope = 0.334675;
    Double_t avg_sigma = 8.91092;
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
    ((TF1*)l->At(ihp))->Draw("SAME");
    gPad->Update();
    savepad->cd();
}


