{
    TFile* mu_analysis_file = TFile::Open("mu_analysis.root","READ");

    TObjArray* hlt_zb_l1_zb_distributions = 0;
    TObjArray* l1xe30_corrected_zb_distributions = 0;
    TObjArray* l1xe50_corrected_zb_distributions = 0;
    TObjArray* reconstructed_distributions = 0;
    TObjArray* l1xe30_efficiency_objects = 0;
    TObjArray* l1xe50_efficiency_objects = 0;
    TObjArray* hlt_zb_l1xe30_met_distributions = 0;
    TObjArray* hlt_zb_l1xe50_met_distributions = 0;

    mu_analysis_file->GetObject("hlt_zb_l1zb_met_distributions",hlt_zb_l1_zb_distributions);
    mu_analysis_file->GetObject("hlt_zb_l1xe30_corrected_zb_met_distributions",l1xe30_corrected_zb_distributions);
    mu_analysis_file->GetObject("hlt_zb_l1xe50_corrected_zb_met_distributions",l1xe50_corrected_zb_distributions);
    mu_analysis_file->GetObject("l1xe30_efficiency_objects", l1xe30_efficiency_objects);
    mu_analysis_file->GetObject("l1xe50_efficiency_objects", l1xe50_efficiency_objects);
    mu_analysis_file->GetObject("hlt_zb_l1xe30__met_distributions",hlt_zb_l1xe30_met_distributions);
    mu_analysis_file->GetObject("hlt_zb_l1xe50__met_distributions",hlt_zb_l1xe50_met_distributions);

    std::cout << "Number of objects in hlt_zb_l1_zb_distributions: " << hlt_zb_l1_zb_distributions->GetEntries() << std::endl;
    TH1D* zb_dist;
    TH1D* l1xe30_corrected_zb_dist;
    TH1D* l1xe50_corrected_zb_dist;
    TEfficiency* l1xe30_efficiency_curve;
    TEfficiency* l1xe50_efficiency_curve;
    TString zb_name, l1xe30_corrected_name, l1xe50_corrected_name ;

    Int_t nbins = ((TH1D*)hlt_zb_l1_zb_distributions->At(2))->GetNbinsX();
    std::cout << "Number of MET Bins: " << nbins << std::endl;

    Float_t met_low = 0.0;
    Float_t met_high = 300.0;

    TH1D* Reconstructed_MET_Distribution = new TH1D("reconst", "reconst" , nbins , met_low , met_high );

    TString reconstructed_name;
    TString x_axis_label = "Cell Algorithm MET [GeV]";
    TString y_axis_label = "Fraction of events / 5 GeV";

    // reconstruction thresholds
    Int_t L1XE30BinThreshes[7] = {11,11,14,15,15,12,11}; 
    Int_t L1XE50BinThreshes[7] = {20,20,20,20,16,18,18};

    TString outFileName = "";
    for (int i = 0; i <= hlt_zb_l1_zb_distributions->GetLast(); i++){
        // READ IN HISTOGRAMS {{{ 
        zb_dist = ((TH1D*)(hlt_zb_l1_zb_distributions->At(i)));
        l1xe30_corrected_zb_dist = ((TH1D*)(l1xe30_corrected_zb_distributions->At(i)));
        l1xe50_corrected_zb_dist = ((TH1D*)(l1xe50_corrected_zb_distributions->At(i)));
        l1xe30_efficiency_curve = ((TEfficiency*)(l1xe30_efficiency_objects->At(i)));
        l1xe50_efficiency_curve = ((TEfficiency*)(l1xe50_efficiency_objects->At(i)));
        //}}}
        // MET DISTRIBUTION FORMATTING {{{ 
        // titles
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
        //}}}
        // PLOT MET DISTRIBUTIONS WITH EFFICIENCY CURVES {{{
        TCanvas* corrected_canvas = new TCanvas("correctedCanvas","Canvas with ZB Distributions");
        gStyle->SetOptStat(0);
        corrected_canvas->Divide(1,2);
        corrected_canvas->cd(1);
        l1xe50_corrected_zb_dist->Draw("P E1");
        zb_dist->Draw("P E1 SAME");
        l1xe30_corrected_zb_dist->Draw("P E1 SAME");
        TLegend* correctedLegend = new TLegend(0.48,0.7,0.9,0.9);
        correctedLegend->AddEntry( zb_dist );
        correctedLegend->AddEntry( l1xe30_corrected_zb_dist );
        correctedLegend->AddEntry( l1xe50_corrected_zb_dist );
        correctedLegend->Draw("SAME");
        correctedCanvas->SetLogy();
        corrected_canvas->cd(2);
        l1xe30_efficiency_curve->Draw();
        l1xe50_efficiency_curve->Draw("SAME");
        auto graph = l1xe30_efficiency_curve->GetPaintedGraph();
        graph->GetXaxis()->SetRange(0.0,300.0);
        Double_t l1xe30Discriminant = L1XE30BinThreshes[i] * 5.0;
        Double_t l1xe50Discriminant = L1XE50BinThreshes[i] * 5.0;
        TLine* l1xe30Line = new TLine( l1xe30Discriminant , 0.0 , l1xe30Discriminant, 1.0 );
        TLine* l1xe50Line = new TLine( l1xe50Discriminant , 0.0 , l1xe50Discriminant , 1.0 );
        l1xe30Line->Draw("SAME");
        l1xe50Line->Draw("SAME");
        outFileName.Form("plots/zerobias_distributions_corrected/zb_met_distributions_mubin_%d.png",i);
        correctedCanvas->Print(outFileName);
        // }}}
        // CREATE RECONSTRUCTED HISTOGRAM{{{
        reconstructed_name.Form("Reconstructed Zero Bias Distribution for %d < #mu < %d" , i*10,(i+1)*10  );
        Reconstructed_MET_Distribution->SetTitle(reconstructed_name);
        Reconstructed_MET_Distribution->GetXaxis()->SetTitle(x_axis_label);
        Reconstructed_MET_Distribution->GetYaxis()->SetTitle(y_axis_label);
        //}}}
        // PERFORM RECONSTRUCTION {{{
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
        // }}}
        // PLOT RECONSTRUCTION{{{
        Reconstructed_MET_Distribution->SetLineColor( kBlack );
        Reconstructed_MET_Distribution->SetNormFactor(1.);

        TCanvas* reconstructed_canvas = new TCanvas("reconstructedCanvas","Canvas with Reconstructed MET Distribution");
        gStyle->SetOptStat(0);
        reconstructed_canvas->Divide(1,2);
        reconstructed_canvas->cd(1);
        Reconstructed_MET_Distribution->Draw("P E1");
        TLegend* reconstructedLegend = new TLegend(0.48,0.7,0.9,0.9);
        reconstructedLegend->AddEntry( Reconstructed_MET_Distribution );
        reconstructed_canvas->SetLogy();
        reconstructedLegend->Draw("SAME");

        reconstructed_canvas->cd(2);
        l1xe30_efficiency_curve->Draw();
        l1xe50_efficiency_curve->Draw("SAME");
        auto graph = l1xe30_efficiency_curve->GetPaintedGraph();
        graph->GetXaxis()->SetRange(0.0,300.0);
        Double_t l1xe30Discriminant = L1XE30BinThreshes[i] * 5.0;
        Double_t l1xe50Discriminant = L1XE50BinThreshes[i] * 5.0;
        TLine* l1xe30Line = new TLine( l1xe30Discriminant , 0.0 , l1xe30Discriminant, 1.0 );
        TLine* l1xe50Line = new TLine( l1xe50Discriminant , 0.0 , l1xe50Discriminant , 1.0 );
        l1xe30Line->Draw("SAME");
        l1xe50Line->Draw("SAME");
        outFileName.Form("plots/reconstructed_distributions/reconstructed_distribution_mubin_%d.png",i);
        reconstructed_canvas->Print(outFileName);
        // }}}
    }
    mu_analysis_file->Close()
}
