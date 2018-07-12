#include <iostream>
#include <TEfficiency.h>
#include <TFile.h>
#include <TF1.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TImage.h>


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
    TString efficiencyObjectFilePath = "EfficiencyObjects.root";
    TString efficiencyFitsFilePath = "EfficiencyFits.root";

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

    std::cout << "Attempting to generate fit functions" << std::endl;
    TF1* mu0thru10FitFunction = generateFitFunction( MET_Algmu0thru10Efficiency);
    TF1* mu10thru20FitFunction = generateFitFunction( MET_Algmu10thru20Efficiency);
    TF1* mu20thru30FitFunction = generateFitFunction( MET_Algmu20thru30Efficiency);
    TF1* mu30thru40FitFunction = generateFitFunction( MET_Algmu30thru40Efficiency);
    TF1* mu40thru50FitFunction = generateFitFunction( MET_Algmu40thru50Efficiency);
    TF1* mu50thru60FitFunction = generateFitFunction( MET_Algmu50thru60Efficiency);
    TF1* mu60thru70FitFunction = generateFitFunction( MET_Algmu60thru70Efficiency);
    std::cout << "Successfully generated fit functions" << std::endl;

    myfile->Close();

    mu0thru10FitFunction->SetName("metmu0thru10Fit");
    mu10thru20FitFunction->SetName("metmu10thru20Fit");
    mu20thru30FitFunction->SetName("metmu20thru30Fit");
    mu30thru40FitFunction->SetName("metmu30thru40Fit");
    mu40thru50FitFunction->SetName("metmu40thru50Fit");
    mu50thru60FitFunction->SetName("metmu50thru60Fit");
    mu60thru70FitFunction->SetName("metmu60thru70Fit");

    TCanvas* mycanv = new TCanvas("fitFunctionCanv", "Efficiency Fits");

    mu0thru10FitFunction->SetLineColor(1);
    mu10thru20FitFunction->SetLineColor(2);
    mu20thru30FitFunction->SetLineColor(3);
    mu30thru40FitFunction->SetLineColor(4);
    mu40thru50FitFunction->SetLineColor(12);
    mu50thru60FitFunction->SetLineColor(6);
    mu60thru70FitFunction->SetLineColor(8);

    mu0thru10FitFunction->Draw();
    mu10thru20FitFunction->Draw("SAME");
    mu20thru30FitFunction->Draw("SAME");
    mu30thru40FitFunction->Draw("SAME");
    mu40thru50FitFunction->Draw("SAME");
    mu50thru60FitFunction->Draw("SAME");
    mu60thru70FitFunction->Draw("SAME");

    mycanv->SetTitle("Fits to Efficiency");
    //gPad->SetLogy();
    TLegend* legend = new TLegend();
    legend->AddEntry(mu0thru10FitFunction, "mu 0 to 10");
    legend->AddEntry(mu10thru20FitFunction , "mu 10 to 20");
    legend->AddEntry(mu20thru30FitFunction, "mu 20 to 30");
    legend->AddEntry(mu30thru40FitFunction, "mu 30 to 40");
    legend->AddEntry(mu40thru50FitFunction, "mu 40 to 50");
    legend->AddEntry(mu50thru60FitFunction , "mu 50 to 60");
    legend->AddEntry(mu60thru70FitFunction , "mu 60 to 70");
    legend->Draw("SAME");
    gStyle->SetOptStat(0);

    TImage *img = TImage::Create();
    img->FromPad(mycanv);
    img->WriteImage("EfficiencyFits.png");

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
