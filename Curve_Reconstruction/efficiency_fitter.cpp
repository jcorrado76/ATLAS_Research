void efficiency_fitter(){


    TFile* myfile = TFile::Open("temp.root","READ");

    TEfficiency* eff = (TEfficiency*) myfile->Get("teff");

    


    auto myErf2Lambda = [](double* x, double* p) { 
                return (TMath::Erf((x[0]-p[0])/p[1]) + 1)/2 * p[2]; };
    TF1* myErf2 = new TF1("myErf2", myErf2Lambda, 
                       -10, 10, 3 /*number of parameters*/);
    myErf2->SetParameter(0, 5.);
    myErf2->SetParameter(1, 3.);
    myErf2->SetParameter(2, 0.8);

    eff->Fit(myErf2);


   // myErf2->Draw();
    eff->Draw();



}
