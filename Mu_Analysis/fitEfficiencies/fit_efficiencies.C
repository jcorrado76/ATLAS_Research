#include <iostream>
#include <TClonesArray.h>

Double_t fitFunction(Double_t *x , Double_t *par ){
    Float_t xx = x[0];
    Double_t l1cut = 30.0;
    Double_t f = (1./2.)*(1.+TMath::Erf((par[0]*x[0]+par[1]-l1cut)/(par[2]*TMath::Sqrt(2.))));
    return f;
}

void myfunc()
{
   TF1 *fitErrorFunction = new TF1("myfunc",fitFunction,0.0,105.0,3);
    //set the normalization to 1
    //set the x translation to 0
    //initialize sigma to 10
    fitErrorFunction->SetParameter(0, 1.);
    fitErrorFunction->SetParameter(1, 0.);
    fitErrorFunction->SetParameter(2, 10.);
    //initializing parameters reasonably is important because it is a maximum likelihood fit
    fitErrorFunction->SetParNames("Slope","Translation","Sigma");
}

TF1* generateFitFunction(){
    // initialize the TEfficiency object that will hold each TEfficiency on each iteration 
    TF1* fitErrorFunction = (TF1*)gROOT->GetFunction("myfunc");
    // get the efficiency from the tclones array
    currTEfficiencyObj = (TEfficiency*)TEfficiencyArray->ConstructedAt(sliceNdx);
    //"R" tells the fit function from BinomialEfficiency::Fit to use the range of the TF1 as the fitting range
    currTEfficiencyObj->Fit( fitErrorFunction  , "R" );

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
   TEfficiency*  MET_Algmu0thru10Efficiency = (TEfficiency*)myfile->Get("metmu0thru10Efficiency");
   TEfficiency*  MET_Algmu10thru20Efficiency =(TEfficiency*)myfile->Get("metmu10thru20Efficiency");
   TEfficiency*  MET_Algmu20thru30Efficiency = (TEfficiency*)myfile->Get("metmu20thru30Efficiency");
   TEfficiency*  MET_Algmu30thru40Efficiency = (TEfficiency*)myfile->Get("metmu30thru40Efficiency");
   TEfficiency*  MET_Algmu40thru50Efficiency = (TEfficiency*)myfile->Get("metmu40thru50Efficiency");
   TEfficiency*  MET_Algmu50thru60Efficiency = (TEfficiency*)myfile->Get("metmu50thru60Efficiency");
   TEfficiency*  MET_Algmu60thru70Efficiency = (TEfficiency*)myfile->Get("metmu60thru70Efficiency");



        MyFittingRoutine->fit_efficiencies();
    FitFile = TFile::Open( efficiencyFitsFilePath , "RECREATE" );
    FitArray->Write();
    FitFile->Close();
}



void FittingRoutine::fit_efficiencies(){
    printf("Number of objects in TEfficiency File: %d", numberSlices);
    TEfficiencyArray = new TClonesArray( "TEfficiency", numberSlices );
    FitArray = new TClonesArray( "TF1", numberSlices );
    for ( sliceNdx ; sliceNdx  < numberSlices ; sliceNdx++){
        printf("Current slice: %d" , sliceNdx);
        // get TEfficiency from file reading in
        currTEfficiencyObj = (TEfficiency*) TEfficiencyArray->ConstructedAt( sliceNdx );
        currFitFunc = generateFitFunction();
        // construct a fit object in output array 
        currFitFunc = (TF1*) FitArray->ConstructedAt( sliceNdx );
    }
}

