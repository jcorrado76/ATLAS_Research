
    Double_t fit( Double_t *x , Double_t *par )
    {
        Double_t PI = TMath::Pi();
        Double_t arg = 0;

        Float_t l1cut = 20.0;
        //arg = ( l1cut  - par[0]*x[0]+ par[1])/(par[2]*TMath::Sqrt(2.0));
        //Double_t fitval = (1./(2*par[2]*TMath::Sqrt(2*PI)))-(1/TMath::Sqrt(PI))*TMath::Erf(arg);

        Double_t fitval = (1./2.)*(1.+TMath::Erf((par[0]*x[0]+par[1]-l1cut)/(par[2]*TMath::Sqrt(2.))));
        return(fitval);
    }


void efficiency_fitter(){

    TFile* myfile = TFile::Open("temp.root","READ");

    TEfficiency* eff = (TEfficiency*) myfile->Get("teff");

    //I set the range of the Tf1 to be up to 60 GeV because beyond that the error bars are so large those points don't
    //work to pull the fit at all

    //TF1* erf = new TF1( "fit" , fit , 0.0 , 105.0 , 3);
    TF1* erf = new TF1( "fit" , fit , 0.0 , 200.0 , 3);

    //set the normalization to 1
    erf->SetParameter(0, 1.);
    //set the x translation to 0
    erf->SetParameter(1, 0.);
    //set sigma to 1
    erf->SetParameter(2, 10.);

    erf->SetParNames("Slope","Translation","Sigma");
    //"R" tells the fit function from BinomialEfficiency::Fit to use the range of the TF1 as the fitting range
    eff->Fit( erf, "R" );

    eff->Draw();



}
