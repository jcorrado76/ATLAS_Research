
    Double_t fit( Double_t *x , Double_t *par )
    {
        Double_t PI = TMath::Pi();
        Double_t arg = 0;

        Float_t l1cut = 20.0;

        Double_t fitval = (1./2.)*(1.+TMath::Erf((par[0]*x[0]+par[1]-l1cut)/(par[2]*TMath::Sqrt(2.))));
        return(fitval);
    }


void efficiency_fitter(){

    TFile* myfile = TFile::Open("temp.root","READ");

    TEfficiency* eff = (TEfficiency*) myfile->Get("teff");

    //TF1* erf = new TF1( "fit" , fit , 0.0 , 105.0 , 3);
    TF1* erf = new TF1( "fit" , fit , 0.0 , 200.0 , 3);

    //set the normalization to 1
    erf->SetParameter(0, 1.);
    //set the x translation to 0
    erf->SetParameter(1, 0.);
    //initialize sigma to 10
    erf->SetParameter(2, 10.);
    //initializing parameters reasonably is important because it is a maximum likelihood fit

    erf->SetParNames("Slope","Translation","Sigma");
    //"R" tells the fit function from BinomialEfficiency::Fit to use the range of the TF1 as the fitting range
    eff->Fit( erf, "R" );

    std::cout << "Value of fit for a: " << erf->GetParameter(0) << std::endl;
    std::cout << "Value of error on a: " << erf->GetParError(0) << std::endl;
    std::cout << "Value of fit for b: " << erf->GetParameter(1) << std::endl;
    std::cout << "Value of error on b: " << erf->GetParError(1) << std::endl;
    std::cout << "Value of fit for sigma: " << erf->GetParameter(2) << std::endl;
    std::cout << "Value of error on sigma: " << erf->GetParError(2) << std::endl;


    eff->Draw();



}
