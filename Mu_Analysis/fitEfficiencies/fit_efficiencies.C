#include <iostream>
#include <TEfficiency.h>
#include <TFile.h>
#include <TF1.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TImage.h>
#include <TGraphAsymmErrors.h>


Double_t fitFunction(Double_t *x , Double_t *par ){
    Float_t xx = x[0];
    Double_t l1cut = 30.0;
    Double_t fitval = (1./2.)*(1.+TMath::Erf((par[0]*x[0]+par[1]-l1cut)/(par[2]*TMath::Sqrt(2.))));
    return fitval;
}

TF1* generateFitFunction(TEfficiency* teff_obj){
    TF1 *fitErrorFunction = new TF1("fitFunction",fitFunction,0.0,300.0,3);
    //set the normalization to 1
    //set the x translation to 0
    //initialize sigma to 10
    fitErrorFunction->SetParameter(0, 1.);
    fitErrorFunction->SetParameter(1, 0.);
    fitErrorFunction->SetParameter(2, 10.);
    //initializing parameters reasonably is important because it is a maximum likelihood fit
    fitErrorFunction->SetParNames("Slope","Translation","Sigma");
    //"R" tells the fit function from BinomialEfficiency::Fit to use the range of the TF1 as the fitting range
    teff_obj->Fit( fitErrorFunction  , "R" );

    std::cout << "Value of fit for a: " << fitErrorFunction->GetParameter(0) << std::endl;
    std::cout << "Value of error on a: " << fitErrorFunction->GetParError(0) << std::endl;
    std::cout << "Value of fit for b: " << fitErrorFunction->GetParameter(1) << std::endl;
    std::cout << "Value of error on b: " << fitErrorFunction->GetParError(1) << std::endl;
    std::cout << "Value of fit for sigma: " << fitErrorFunction->GetParameter(2) << std::endl;
    std::cout << "Value of error on sigma: " << fitErrorFunction->GetParError(2) << std::endl;
    return fitErrorFunction;
}

void fit_efficiencies(){
    TString efficiencyObjectFilePath = "../Root_Files/EfficiencyObjects.root";
    TString efficiencyFitsFilePath = "../Root_Files/EfficiencyFits.root";

    TFile* myfile = TFile::Open(efficiencyObjectFilePath);
    std::cout << "Getting efficiency objects from file" << std::endl;
    TEfficiency*  MET_Algmu0thru10Efficiency = (TEfficiency*)myfile->Get("metmu0thru10Efficiency");
    std::cout << "First efficiency object name: " << MET_Algmu0thru10Efficiency->GetName() << std::endl;
    TEfficiency*  MET_Algmu10thru20Efficiency =(TEfficiency*)myfile->Get("metmu10thru20Efficiency");
    TEfficiency*  MET_Algmu20thru30Efficiency = (TEfficiency*)myfile->Get("metmu20thru30Efficiency");
    TEfficiency*  MET_Algmu30thru40Efficiency = (TEfficiency*)myfile->Get("metmu30thru40Efficiency");
    TEfficiency*  MET_Algmu40thru50Efficiency = (TEfficiency*)myfile->Get("metmu40thru50Efficiency");
    TEfficiency*  MET_Algmu50thru60Efficiency = (TEfficiency*)myfile->Get("metmu50thru60Efficiency");
    TEfficiency*  MET_Algmu60thru70Efficiency = (TEfficiency*)myfile->Get("metmu60thru70Efficiency");
    std::cout << "Successfully got efficiency objects from file" << std::endl;

    std::cout << "\nGenerating Fit for mu 0 to 10" << std::endl;
    TF1* mu0thru10FitFunction = generateFitFunction( MET_Algmu0thru10Efficiency);
    std::cout << "\nGenerating Fit for mu 10 to 20" << std::endl;
    TF1* mu10thru20FitFunction = generateFitFunction( MET_Algmu10thru20Efficiency);
    std::cout << "\nGenerating Fit for mu 20 to 30" << std::endl;
    TF1* mu20thru30FitFunction = generateFitFunction( MET_Algmu20thru30Efficiency);
    std::cout << "\nGenerating Fit for mu 30 to 40" << std::endl;
    TF1* mu30thru40FitFunction = generateFitFunction( MET_Algmu30thru40Efficiency);
    std::cout << "\nGenerating Fit for mu 40 to 50" << std::endl;
    TF1* mu40thru50FitFunction = generateFitFunction( MET_Algmu40thru50Efficiency);
    std::cout << "\nGenerating Fit for mu 50 to 60" << std::endl;
    TF1* mu50thru60FitFunction = generateFitFunction( MET_Algmu50thru60Efficiency);
    std::cout << "\nGenerating Fit for mu 60 to 70" << std::endl;
    TF1* mu60thru70FitFunction = generateFitFunction( MET_Algmu60thru70Efficiency);
    std::cout << "Successfully generated fit functions" << std::endl;

    myfile->Close();

    TCanvas* canv1 = new TCanvas("canv1", "mu0thru10");
    MET_Algmu0thru10Efficiency->Draw();
    gPad->Update();
    auto graph = MET_Algmu0thru10Efficiency->GetPaintedGraph();
    graph->SetMinimum(0);
    graph->SetMaximum(1);

    TCanvas* canv2 = new TCanvas("canv2", "mu10thru20");
    MET_Algmu10thru20Efficiency->Draw();
    gPad->Update();
    graph = MET_Algmu10thru20Efficiency->GetPaintedGraph();
    graph->SetMinimum(0);
    graph->SetMaximum(1);

    TCanvas* canv3 = new TCanvas("canv3", "mu20thru30");
    MET_Algmu20thru30Efficiency->Draw();
    gPad->Update();
    graph = MET_Algmu20thru30Efficiency->GetPaintedGraph();
    graph->SetMinimum(0);
    graph->SetMaximum(1);

    TCanvas* canv4 = new TCanvas("canv4", "mu30thru40");
    MET_Algmu30thru40Efficiency->Draw();
    gPad->Update();
    graph = MET_Algmu30thru40Efficiency->GetPaintedGraph();
    graph->SetMinimum(0);
    graph->SetMaximum(1);

    TCanvas* canv5 = new TCanvas("canv5", "mu40thru50");
    MET_Algmu40thru50Efficiency->Draw();
    gPad->Update();
    graph = MET_Algmu40thru50Efficiency->GetPaintedGraph();
    graph->SetMinimum(0);
    graph->SetMaximum(1);

    TCanvas* canv6 = new TCanvas("canv6", "mu50thru60");
    MET_Algmu50thru60Efficiency->Draw();
    gPad->Update();
    graph = MET_Algmu50thru60Efficiency->GetPaintedGraph();
    graph->SetMinimum(0);
    graph->SetMaximum(1);

    TCanvas* canv7 = new TCanvas("canv7", "mu60thru70");
    MET_Algmu60thru70Efficiency->Draw();
    gPad->Update();
    graph = MET_Algmu60thru70Efficiency->GetPaintedGraph();
    graph->SetMinimum(0);
    graph->SetMaximum(1);

    gStyle->SetOptStat(0);

    /*
    TImage *img = TImage::Create();
    img->FromPad(mycanv);
    img->WriteImage("../Plots/EfficiencyFits.png");
    */

    TFile* FitFile = TFile::Open( efficiencyFitsFilePath , "RECREATE" );
    mu0thru10FitFunction->Write();
    mu10thru20FitFunction->Write();
    mu20thru30FitFunction->Write();
    mu30thru40FitFunction->Write();
    mu40thru50FitFunction->Write();
    mu50thru60FitFunction->Write();
    mu60thru70FitFunction->Write();

    FitFile->Close();
    
}
