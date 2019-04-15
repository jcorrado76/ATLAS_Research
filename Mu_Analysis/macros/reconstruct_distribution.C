{
    TFile* mu_analysis_file = TFile::Open("mu_analysis.root","READ");

    TObjArray* hlt_zb_l1_zb_distributions = 0;
    TObjArray* l1xe30_corrected_zb_distributions = 0;
    TObjArray* l1xe50_corrected_zb_distributions = 0;
    TObjArray* reconstructed_distributions = 0;

    mu_analysis_file->GetObject("hlt_zb_l1zb_met_distributions",hlt_zb_l1_zb_distributions);
    mu_analysis_file->GetObject("hlt_zb_l1xe30_corrected_zb_met_distributions",l1xe30_corrected_zb_distributions);
    mu_analysis_file->GetObject("hlt_zb_l1xe50_corrected_zb_met_distributions",l1xe50_corrected_zb_distributions);

    std::cout << "Number of objects in hlt_zb_l1_zb_distributions: " << hlt_zb_l1_zb_distributions->GetEntries() << std::endl;
    TH1D* zb_dist;
    TH1D* l1xe30_corrected_zb_dist;
    TH1D* l1xe50_corrected_zb_dist;

    Int_t nbins = ((TH1D*)hlt_zb_l1_zb_distributions->At(2))->GetNbinsX();
    std::cout << "Number of MET Bins: " << nbins << std::endl;

    Float_t met_low = 0.0;
    Float_t met_high = 300.0;

    TH1D* Reconstructed_MET_Distribution = new TH1D("reconst", "reconst" , nbins , met_low , met_high );

    TString reconstructed_name;

    Int_t L1XE30BinThreshes[7] = {11,11,14,15,15,12,11}; 
    Int_t L1XE50BinThreshes[7] = {20,20,20,20,16,18,18};

    TString outFileName = "";
    for (int i = 0; i <= hlt_zb_l1_zb_distributions->GetLast(); i++){
        // read the histograms into memory
        zb_dist = ((TH1D*)(hlt_zb_l1_zb_distributions->At(i)));
        l1xe30_corrected_zb_dist = ((TH1D*)(l1xe30_corrected_zb_distributions->At(i)));
        l1xe50_corrected_zb_dist = ((TH1D*)(l1xe50_corrected_zb_distributions->At(i)));

        // initialize the new histogram
        reconstructed_name.Form("Reconstructed Zero Bias Distribution for %d < #mu < %d" , i*10,(i+1)*10  );
        Reconstructed_MET_Distribution->SetTitle(reconstructed_name);

        for ( int j = 1 ; j < nbins ; j++ ){
            if (j < L1XE30BinThreshes[i]){
                Reconstructed_MET_Distribution->SetBinContent( j , zb_dist->GetBinContent( j ) );
                Reconstructed_MET_Distribution->SetBinError( j , zb_dist->GetBinError( j ) );
            }else if ( j < L1XE50BinThreshes[i] ){
                Reconstructed_MET_Distribution->SetBinContent( j , l1xe30_corrected_zb_dist->GetBinContent( j ) );
                Reconstructed_MET_Distribution->SetBinError( j , l1xe30_corrected_zb_dist->GetBinError( j ) );
            } else{
                Reconstructed_MET_Distribution->SetBinContent( j , l1xe50_corrected_zb_dist->GetBinContent( j ) );
                Reconstructed_MET_Distribution->SetBinError( j , l1xe50_corrected_zb_dist->GetBinError( j ) );
            }
        }

        // set line color
        Reconstructed_MET_Distribution->SetLineColor( kBlack );
        Reconstructed_MET_Distribution->SetNormFactor(1.);

        TCanvas* reconstructed_canvas = new TCanvas("reconstructedCanvas","Canvas with Reconstructed MET Distribution");
        TLegend* reconstructedLegend = new TLegend(0.48,0.7,0.9,0.9);
        Reconstructed_MET_Distribution->Draw("P E1");
        reconstructedLegend->AddEntry( Reconstructed_MET_Distribution );
        reconstructed_canvas->SetLogy();
        gStyle->SetOptStat(0);
        outFileName.Form("plots/reconstructed_distributions/reconstructed_distribution_mubin_%d.png",i);
        reconstructed_canvas->Print(outFileName);
    }
    mu_analysis_file->Close()
}
