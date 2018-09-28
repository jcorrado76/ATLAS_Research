{

    // plot original zb met
    TFile* mu_analysis_file = TFile::Open("../Root_Files/mu_analysis.root");
    TDirectory* zb_met = mu_analysis_file->GetDirectory("zb_met");
    TH1F* metbin4 = 0;
    zb_met->GetObject("metmu40thru50",metbin4);
    metbin4->Draw();

    // get corrected distribution
    TDirectory* efficiency_dir = mu_analysis_file->GetDirectory("efficiency_curves");
    TEfficiency* teff4 = 0;
    efficiency_dir->GetObject("metmu40thru50Efficiency",teff4);
    teff4->Draw("SAME")



}

