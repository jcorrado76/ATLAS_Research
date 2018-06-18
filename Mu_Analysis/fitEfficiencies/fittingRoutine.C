#include "fittingRoutine.h"


Double_t FittingRoutine::myfunction(Double_t *x , Double_t *par ){
    Float_t xx = x[0];
    Double_t l1cut = 30.0;
    Double_t f = (1./2.)*(1.+TMath::Erf((par[0]*x[0]+par[1]-l1cut)/(par[2]*TMath::Sqrt(2.))));
    return f;

}

void FittingRoutine::myfunc()
{
   TF1 *fitErrorFunction = new TF1("myfunc",myfunction,0.0,105.0,3);
    //set the normalization to 1
    //set the x translation to 0
    //initialize sigma to 10
    fitErrorFunction->SetParameter(0, 1.);
    fitErrorFunction->SetParameter(1, 0.);
    fitErrorFunction->SetParameter(2, 10.);
    //initializing parameters reasonably is important because it is a maximum likelihood fit
    fitErrorFunction->SetParNames("Slope","Translation","Sigma");
}


TF1* FittingRoutine::generateFitFunction(){
    // initialize the TEfficiency object that will hold each TEfficiency on each iteration 
    TF1* fitErrorFunction = (TF1*)gROOT->GetFunction("myfunc");
    // get the efficiency from the tclones array
    currTEfficiencyObj = (TEfficiency*)EfficiencyArray->ConstructedAt(sliceNdx);
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

void FittingRoutine::fit_efficiencies(){
    printf("Number of objects in TEfficiency File: %d", numberSlices);
    EfficiencyArray = new TClonesArray( "TEfficiency", numberSlices );
    FitArray = new TClonesArray( "TF1", numberSlices );
    for ( sliceNdx ; sliceNdx  < numberSlices ; sliceNdx++){
        printf("Current slice: %d" , sliceNdx);
        currTEfficiencyObj = (TEfficiency*) EfficiencyArray->ConstructedAt( sliceNdx );
        currFitFunc = generateFitFunction();
        currFitFunc = (TF1*) FitArray->ConstructedAt( sliceNdx );
    }
}

void FittingRoutine::getTEfficiencyArray( TString filePath ){
    // load TEfficiency TClonesArray into memory 
    EfficiencyFile = TFile::Open( filePath );
    EfficiencyArray = (TClonesArray*) EfficiencyFile->Get("TEfficiencyArray");
    numberSlices = EfficiencyArray->GetEntries();

}

void FittingRoutine::writeFitsToFile( TString fileName ){
    FitFile = TFile::Open( fileName );
    FitArray->Write();

    FitFile->Close();
}

FittingRoutine::FittingRoutine()
    :EfficiencyFile(0),FitFile(0), EfficiencyArray(0),FitArray(0), numberSlices(0), sliceNdx(0), currTEfficiencyObj(0), currFitFunc(0)
{}

FittingRoutine::~FittingRoutine(){}
