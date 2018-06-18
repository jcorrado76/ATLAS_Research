#include <TFile.h>
#include <TF1.h>
#include <TEfficiency.h>
#include <TClonesArray.h>

Double_t fit( Double_t *x , Double_t *par )
{
    Float_t l1cut = 30.0;
    Double_t fitval = (1./2.)*(1.+TMath::fitErrorFunction((par[0]*x[0]+par[1]-l1cut)/(par[2]*TMath::Sqrt(2.))));
    return(fitval);
}

void fit_efficiencies(){
    // suppose there exists a root file containing a TClonesArray of Efficiency Curves
    TFile* efficiencyCurveFile = TFile::Open("efficiencyCurves.root");
    // how many efficiency curves to fit
    Int_t numberSlices = 7;
    // initialize TClonesArray to hold the efficiency curves
    TClonesArray* efficiencyArray = new TClonesArray( "TEfficiency", numberSlices );
    // initialize TClonesArray to hold the fit objects 
    TClonesArray* efficiencyFitArray = new TClonesArray( "TF1", numberSlices );

    // initialize the TEfficiency object that will hold each TEfficiency on each iteration 
    TEfficiency* efficiencyObject = 0;
    for ( int i = 0 ; i < numberSlices ; i++){
        TF1* fitErrorFunction = new TF1( "fit" , fit , 0.0 , 105.0 , 3);

        //set the normalization to 1
        fitErrorFunction->SetParameter(0, 1.);
        //set the x translation to 0
        fitErrorFunction->SetParameter(1, 0.);
        //initialize sigma to 10
        fitErrorFunction->SetParameter(2, 10.);
        //initializing parameters reasonably is important because it is a maximum likelihood fit

        fitErrorFunction->SetParNames("Slope","Translation","Sigma");
        //"R" tells the fit function from BinomialEfficiency::Fit to use the range of the TF1 as the fitting range
        efficiencyObject->Fit( fitErrorFunction, "R" );

        std::cout << "Value of fit for a: " << fitErrorFunction->GetParameter(0) << std::endl;
        std::cout << "Value of error on a: " << fitErrorFunction->GetParError(0) << std::endl;
        std::cout << "Value of fit for b: " << fitErrorFunction->GetParameter(1) << std::endl;
        std::cout << "Value of error on b: " << fitErrorFunction->GetParError(1) << std::endl;
        std::cout << "Value of fit for sigma: " << fitErrorFunction->GetParameter(2) << std::endl;
        std::cout << "Value of error on sigma: " << fitErrorFunction->GetParError(2) << std::endl;

        efficiencyObject = (TEfficiency*)efficiencyArray->ConstructedAt(i);
        
    }


}
