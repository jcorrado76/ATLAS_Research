
{
    // Scale the corrected ones to the original zb ones
    TFile* mu_analysis_file = TFile::Open("mu_analysis.root", "READ");
    TObjArray* hlt_zb_l1_zb_distributions = 0;
    TObjArray* l1xe30_corrected_zb_distributions = 0;
    TObjArray* l1xe50_corrected_zb_distributions = 0;

    mu_analysis_file->GetObject("hlt_zb_l1zb_met_distributions",hlt_zb_l1_zb_distributions);
    mu_analysis_file->GetObject("hlt_zb_l1xe30_corrected_zb_met_distributions",l1xe30_corrected_zb_distributions);
    mu_analysis_file->GetObject("hlt_zb_l1xe50_corrected_zb_met_distributions",l1xe50_corrected_zb_distributions);

    std::cout << "Number of objects in hlt_zb_l1_zb_distributions: " << hlt_zb_l1_zb_distributions->GetEntries() << std::endl;
    TH1F* zb_dist;
    TH1F* l1xe30_corrected_zb_dist;
    TH1F* l1xe50_corrected_zb_dist;
    Double_t scale_factor = 0.0;
    //TODO: create two normalization bin number arrays
    //TODO: write functions to compute the correct scale factor, given the points and their uncertainties
    for (int i = 0 ;i < Number_Mu_Bins ; i++ ) {
        // get the histograms
        zb_dist = ((TH1F*)(hlt_zb_l1_zb_distributions->At(i)));
        l1xe30_corrected_zb_dist = ((TH1F*)(l1xe30_corrected_zb_distributions->At(i)));
        l1xe50_corrected_zb_dist = ((TH1F*)(l1xe50_corrected_zb_distributions->At(i)));

        // Compute L1XE30 scale factor
        scale_factor = zb_dist->GetBinContent( Normalization_Bin_Numbers[i] ) / 
            l1xe30_corrected_zb_dist->GetBinContent( Normalization_Bin_Numbers[i] );
        std::cout << "L1XE30 Scale factor: " << i << " = " << scale_factor << std::endl;

        l1xe30_corrected_zb_dist->Scale( scale_factor );
        zb_dist->SetNormFactor( 1. );
        l1xe30_corrected_zb_dist->SetNormFactor( 1. );

        // Compute L1XE50 scale factor
        scale_factor = zb_dist->GetBinContent( Normalization_Bin_Numbers[i] ) / 
            l1xe50_corrected_zb_dist->GetBinContent( Normalization_Bin_Numbers[i] );
        std::cout << "L1XE50 Scale factor: " << i << " = " << scale_factor << std::endl;

        l1xe50_corrected_zb_dist->Scale( scale_factor );
        zb_dist->SetNormFactor( 1. );
        l1xe50_corrected_zb_dist->SetNormFactor( 1. );
    }
    mu_analysis_file->Close()
}
