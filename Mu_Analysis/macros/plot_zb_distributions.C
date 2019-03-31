{
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

    TString zb_name, l1xe30_corrected_name, l1xe50_corrected_name ;

    TString outFileName = "";
    for (int i = 1; i <= hlt_zb_l1_zb_distributions->GetLast(); i++){
        zb_dist = ((TH1F*)(hlt_zb_l1_zb_distributions->At(i)));
        l1xe30_corrected_zb_dist = ((TH1F*)(l1xe30_corrected_zb_distributions->At(i)));
        l1xe50_corrected_zb_dist = ((TH1F*)(l1xe50_corrected_zb_distributions->At(i)));

        // set appropriate titles
       zb_name.Form("Zero Bias Distribution for %d < #mu < %d" , i*10,(i+1)*10  );
       zb_dist->SetTitle( zb_name );
       l1xe30_corrected_name.Form("L1XE30 Corrected to ZeroBias Distribution for %d < #mu < %d" , i*10,(i+1)*10  );
       l1xe30_corrected_zb_dist->SetTitle( l1xe30_corrected_name );
       l1xe50_corrected_name.Form("L1XE50 Corrected to Zero Bias Distribution for %d < #mu < %d" , i*10,(i+1)*10  );
       l1xe50_corrected_zb_dist->SetTitle( l1xe50_corrected_name );

        // set line colors
        zb_dist->SetLineColor( kBlue );
        l1xe30_corrected_zb_dist->SetLineColor( kGreen );
        l1xe50_corrected_zb_dist->SetLineColor( kRed );

        TCanvas* corrected_canvas = new TCanvas("correctedCanvas","Canvas with ZB Distributions");
        TLegend* correctedLegend = new TLegend(0.48,0.7,0.9,0.9);
        l1xe50_corrected_zb_dist->Draw("P E1");
        zb_dist->Draw("P E1 SAME");
        l1xe30_corrected_zb_dist->Draw("P E1 SAME");
        correctedLegend->AddEntry( zb_dist );
        correctedLegend->AddEntry( l1xe30_corrected_zb_dist );
        correctedLegend->AddEntry( l1xe50_corrected_zb_dist );
        correctedLegend->Draw("SAME");
        correctedCanvas->SetLogy();
        gStyle->SetOptStat(0);
        outFileName.Form("plots/zerobias_distributions_corrected/zb_met_distributions_mubin_%d.png",i);
        correctedCanvas->Print(outFileName);
    }
    mu_analysis_file->Close()
}
