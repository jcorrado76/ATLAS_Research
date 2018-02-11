void efficiency_fitter(){


    TFile* myfile = TFile::Open("temp.root","READ");

    TEfficiency* eff = (TEfficiency*) myfile->Get("teff");

    //I set the range of the Tf1 to be up to 60 GeV because beyond that the error bars are so large those points don't
    //work to pull the fit at all
    //TF1* erf = new TF1( "erf" , "[0]*TMath::Erf( ( x - [1] ) / [2] ) + [3] ", 0.0 , 60.0);
    TF1* erf = new TF1( "erf" , "[0]*TMath::Erf( ( x - [1] ) / [2] ) + [3] ", 0.0 , 100.0);

    //set the normalization to 1
    erf->SetParameter(0, 1.);
    //set the x translation to 0
    erf->SetParameter(1, 0.);
    //division by 1 
    erf->SetParameter(2, 1.);
    //no vertical translation
    erf->SetParameter(3,0.);

    //"R" tells the fit function from BinomialEfficiency::Fit to use the range of the TF1 as the fitting range
    eff->Fit( erf, "R" );

    eff->Draw();



}
