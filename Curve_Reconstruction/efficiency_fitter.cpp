
    Float_t PI = TMath::Pi();
    Double_t fit( Float_t *x , Float_t* par )
    {
        par[0] = 1.0;
        par[1] = 0.0;
        par[2] = 1.0;

        Float_t l1cut = 20.0;
        Double_t arg = ( l1cut  - par[0]*x[0]+ par[1])/(par[2]*TMath::Sqrt(2.0));
        Double_t fitval = (1./(2*par[2]*TMath::Sqrt(2*TMath::Pi())))-(1/TMath::Sqrt(TMath::Pi()))*TMath::Erf(arg);

        return(fitval );
    }


void efficiency_fitter(){



    Float_t hltcut = 0.0;


    std::cout << fit(5.,1.,1.,1.,1.) << std::endl;

    TFile* myfile = TFile::Open("temp.root","READ");

    TEfficiency* eff = (TEfficiency*) myfile->Get("teff");

    //I set the range of the Tf1 to be up to 60 GeV because beyond that the error bars are so large those points don't
    //work to pull the fit at all







    TF1* erf = new TF1( "erf" , fit , 0.0 , 100.0 , 4);

    //set the normalization to 1
    erf->SetParameter(0, 1.);
    //set the x translation to 0
    erf->SetParameter(1, 0.);
    //division by 1 

    //"R" tells the fit function from BinomialEfficiency::Fit to use the range of the TF1 as the fitting range
    eff->Fit( erf, "R" );

    eff->Draw();



}
