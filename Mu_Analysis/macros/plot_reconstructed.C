{
    // OPEN FILE {{{
    TFile* mu_analysis_file = TFile::Open("mu_analysis.root","UPDATE");
    //}}}
    // INITIALIZE TOBJARRAYS {{{
    TObjArray* hlt_zb_l1_zb_distributions = 0;
    TObjArray* l1xe30_corrected_zb_distributions = 0;
    TObjArray* l1xe50_corrected_zb_distributions = 0;
    TObjArray* l1xe30_efficiency_objects = 0;
    TObjArray* l1xe50_efficiency_objects = 0;
    TObjArray* hlt_zb_l1xe30_met_distributions = 0;
    TObjArray* hlt_zb_l1xe50_met_distributions = 0;
    TObjArray* reconstructed_distributions = new TObjArray();
    //}}}
    // GET TOBJARRAYS FROM FILE {{{
    mu_analysis_file->GetObject("hlt_zb_l1zb_met_distributions",hlt_zb_l1_zb_distributions);
    mu_analysis_file->GetObject("hlt_zb_l1xe30_corrected_zb_met_distributions",l1xe30_corrected_zb_distributions);
    mu_analysis_file->GetObject("hlt_zb_l1xe50_corrected_zb_met_distributions",l1xe50_corrected_zb_distributions);
    mu_analysis_file->GetObject("l1xe30_efficiency_objects", l1xe30_efficiency_objects);
    mu_analysis_file->GetObject("l1xe50_efficiency_objects", l1xe50_efficiency_objects);
    mu_analysis_file->GetObject("hlt_zb_l1xe30_met_distributions",hlt_zb_l1xe30_met_distributions);
    mu_analysis_file->GetObject("hlt_zb_l1xe50_met_distributions",hlt_zb_l1xe50_met_distributions);
    //}}}

    std::cout << "Number of objects in hlt_zb_l1_zb_distributions: " << hlt_zb_l1_zb_distributions->GetEntries() << std::endl;
    TH1D* zb_dist;
    TH1D* l1xe30_noalg_dist;
    TH1D* l1xe50_noalg_dist;
    TH1D* l1xe30_corrected_zb_dist;
    TH1D* l1xe50_corrected_zb_dist;
    TEfficiency* l1xe30_efficiency_curve;
    TEfficiency* l1xe50_efficiency_curve;
    TString zb_name, l1xe30_corrected_name, l1xe50_corrected_name ;

    Int_t nbins = ((TH1D*)hlt_zb_l1_zb_distributions->At(2))->GetNbinsX();
    std::cout << "Number of MET Bins: " << nbins << std::endl;

    Float_t met_low = 0.0;
    Float_t met_high = 300.0;

    TString reconstructed_name;
    TString reconstructed_title;
    TString x_axis_label = "Cell Algorithm MET [GeV]";
    TString y_axis_label = "Fraction of events / 5 GeV";

    // reconstruction left edge thresholds
    //Int_t L1XE30BinThreshes[7] = {6,11,14,15,15,12,11}; 
    //Int_t L1XE50BinThreshes[7] = {20,20,20,20,16,18,18};
    // to not use XE30 data, set threshold to be a large number, so bin number never greater than it 
    Int_t L1XE30BinThreshes[7] = {11,18,nbins+1,nbins+1,nbins+1,nbins+1,nbins+1}; 
    Int_t L1XE50BinThreshes[7] = {14,20,12,12,12,12,12};

    TString outFileName = "";
    for (int i = 0; i <= hlt_zb_l1_zb_distributions->GetLast(); i++){
        // READ IN HISTOGRAMS {{{ 
        zb_dist = ((TH1D*)(hlt_zb_l1_zb_distributions->At(i)));
        l1xe30_noalg_dist = ((TH1D*)(hlt_zb_l1xe30_met_distributions->At(i)));
        l1xe50_noalg_dist = ((TH1D*)(hlt_zb_l1xe50_met_distributions->At(i)));
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
        l1xe50_corrected_zb_dist->GetXaxis()->SetTitle(x_axis_label);
        l1xe50_corrected_zb_dist->GetYaxis()->SetTitle(y_axis_label);

        //}}}
        // PLOT MET DISTRIBUTIONS WITH EFFICIENCY CURVES {{{
        TCanvas* corrected_canvas = new TCanvas("correctedCanvas","Canvas with ZB Distributions");
        gStyle->SetOptStat(0);
        corrected_canvas->Divide(1,2);
        // PAD 1
        corrected_canvas->cd(1);
        TH1D* zb_dist_clone = (TH1D*)zb_dist->Clone();
        TH1D* l1xe30_corrected_zb_dist_clone = (TH1D*)l1xe30_corrected_zb_dist->Clone();
        TH1D* l1xe50_corrected_zb_dist_clone = (TH1D*)l1xe50_corrected_zb_dist->Clone();
        zb_dist_clone->SetNormFactor(1.);
        l1xe30_corrected_zb_dist_clone->SetNormFactor(1.);
        l1xe50_corrected_zb_dist_clone->SetNormFactor(1.);
        l1xe50_corrected_zb_dist_clone->Draw("P E1");
        zb_dist_clone->Draw("P E1 SAME");
        l1xe30_corrected_zb_dist_clone->Draw("P E1 SAME");
        TLegend* correctedLegend = new TLegend(0.48,0.7,0.9,0.9);
        correctedLegend->AddEntry( zb_dist );
        correctedLegend->AddEntry( l1xe30_corrected_zb_dist );
        correctedLegend->AddEntry( l1xe50_corrected_zb_dist );
        correctedLegend->Draw("SAME");
        gPad->SetLogy();
        // PAD 2
        corrected_canvas->cd(2);
        l1xe30_efficiency_curve->SetLineColor(kGreen);
        ((TF1*)l1xe30_efficiency_curve->GetListOfFunctions()->At(0))->SetLineColor(kGreen);
        l1xe50_efficiency_curve->SetLineColor(kRed);
        ((TF1*)l1xe50_efficiency_curve->GetListOfFunctions()->At(0))->SetLineColor(kRed);
        l1xe30_efficiency_curve->Draw();
        l1xe50_efficiency_curve->Draw("SAME");
        TLegend* correctedLegend2 = new TLegend(0.1,0.7,0.3,0.9);
        correctedLegend2->AddEntry( l1xe30_efficiency_curve );
        correctedLegend2->AddEntry( l1xe50_efficiency_curve );
        gPad->Update();
        l1xe30_efficiency_curve->GetPaintedGraph()->GetXaxis()->SetRange(0.0,300.0);
        Double_t l1xe30Discriminant = L1XE30BinThreshes[i] * 5.0;
        Double_t l1xe50Discriminant = L1XE50BinThreshes[i] * 5.0;
        TLine* l1xe30Line = new TLine( l1xe30Discriminant , 0.0 , l1xe30Discriminant, 1.0);
        TLine* l1xe50Line = new TLine( l1xe50Discriminant , 0.0 , l1xe50Discriminant ,1.0);
        correctedLegend2->Draw("SAME");
        l1xe30Line->Draw("SAME");
        l1xe50Line->Draw("SAME");
        outFileName.Form("plots/zerobias_distributions_corrected/zb_met_distributions_mubin_%d.png",i);
        correctedCanvas->Print(outFileName);
        // }}}
        //PLOT HLTnoalgL1XE30 DISTS{{{
        TCanvas* HLTnoalgL1XE30_canvas = new TCanvas("HLTnoalgL1XE30canv","Canvas with HLT noalg L1XE30 Distributions");
        gStyle->SetOptStat(0);
        HLTnoalgL1XE30_canvas->SetFillColor(42);
        l1xe30_noalg_dist->SetLineColor( kMagenta );
        l1xe30_corrected_zb_dist_clone->GetXaxis()->SetTitle(x_axis_label);
        l1xe30_corrected_zb_dist_clone->GetYaxis()->SetTitle(y_axis_label);
        l1xe30_corrected_zb_dist_clone->Draw("P E1");
        TH1D* l1xe30_noalg_dist_clone = (TH1D*)l1xe30_noalg_dist->Clone();
        l1xe30_noalg_dist_clone->SetNormFactor(1.);
        l1xe30_noalg_dist_clone->Draw("P E1 SAME");
        TLegend* HLTnoalgL1XE30_Legend = new TLegend(0.48,0.7,0.9,0.9);
        HLTnoalgL1XE30_Legend->AddEntry( l1xe30_corrected_zb_dist );
        HLTnoalgL1XE30_Legend->AddEntry( l1xe30_noalg_dist);
        HLTnoalgL1XE30_Legend->Draw("SAME");
        HLTnoalgL1XE30_canvas->SetLogy();
        outFileName.Form("plots/hlt_noalg_l1xe30_plots/hlt_noalg_L1XE30_dist_mubin_%d.png",i);
        HLTnoalgL1XE30_canvas->Print(outFileName);
        //}}}
        //PLOT HLTnoalgL1XE50 DISTS{{{
        TCanvas* HLTnoalgL1XE50_canvas = new TCanvas("HLTnoalgL1XE50canv","Canvas with HLT noalg L1XE50 Distributions");
        HLTnoalgL1XE50_canvas->SetFillColor(42);
        gStyle->SetOptStat(0);
        l1xe50_noalg_dist->SetLineColor( kMagenta );
        l1xe50_corrected_zb_dist_clone->GetXaxis()->SetTitle(x_axis_label);
        l1xe50_corrected_zb_dist_clone->GetYaxis()->SetTitle(y_axis_label);
        TH1D* l1xe50_noalg_dist_clone = (TH1D*)l1xe50_noalg_dist->Clone();
        l1xe50_noalg_dist_clone->SetNormFactor(1.);
        l1xe50_corrected_zb_dist_clone->Draw("P E1");
        l1xe50_noalg_dist_clone->Draw("P E1 SAME");
        TLegend* HLTnoalgL1XE50_Legend = new TLegend(0.48,0.7,0.9,0.9);
        HLTnoalgL1XE50_Legend->AddEntry( l1xe50_corrected_zb_dist );
        HLTnoalgL1XE50_Legend->AddEntry( l1xe50_noalg_dist);
        HLTnoalgL1XE50_Legend->Draw("SAME");
        HLTnoalgL1XE50_canvas->SetLogy();
        outFileName.Form("plots/hlt_noalg_l1xe50_plots/hlt_noalg_L1XE50_dist_mubin_%d.png",i);
        HLTnoalgL1XE50_canvas->Print(outFileName);
        //}}}
        // CREATE RECONSTRUCTED HISTOGRAM{{{
        reconstructed_name.Form("reconstructed_dist_mubin%d",i);
        reconstructed_title.Form("Reconstructed Zero Bias Distribution for %d < #mu < %d" , i*10,(i+1)*10  );
        TH1D* Reconstructed_MET_Distribution = new TH1D(reconstructed_name, reconstructed_title, nbins , met_low , met_high );
        Reconstructed_MET_Distribution->GetXaxis()->SetTitle(x_axis_label);
        Reconstructed_MET_Distribution->GetYaxis()->SetTitle(y_axis_label);
        //}}}
        // PERFORM RECONSTRUCTION {{{
        for ( int j = 1 ; j < nbins ; j++ ){
            if ( j < L1XE30BinThreshes[i] ){
                Reconstructed_MET_Distribution->SetBinContent( j , zb_dist->GetBinContent( j ) );
                Reconstructed_MET_Distribution->SetBinError( j , zb_dist->GetBinError( j ) );
            }
            if (j > L1XE30BinThreshes[i] && j < L1XE50BinThreshes[i]){
                Reconstructed_MET_Distribution->SetBinContent( j , l1xe30_corrected_zb_dist->GetBinContent( j ) );
                Reconstructed_MET_Distribution->SetBinError( j , l1xe30_corrected_zb_dist->GetBinError( j ) );
            }
            if ( j > L1XE50BinThreshes[i] ){
                Reconstructed_MET_Distribution->SetBinContent( j , l1xe50_corrected_zb_dist->GetBinContent( j ) );
                Reconstructed_MET_Distribution->SetBinError( j , l1xe50_corrected_zb_dist->GetBinError( j ) );
            }
        }
        // }}}
        // PLOT RECONSTRUCTION{{{
        Reconstructed_MET_Distribution->SetLineColor( kBlack );
        Reconstructed_MET_Distribution->SetLineWidth( 5 );
        reconstructed_distributions->Add( Reconstructed_MET_Distribution );
        TH1D* Reconstructed_MET_Distribution_clone = (TH1D*)Reconstructed_MET_Distribution->Clone();
        Reconstructed_MET_Distribution_clone->SetNormFactor(1.);
        TCanvas* reconstructed_canvas = new TCanvas("reconstructedCanvas","Canvas with Reconstructed MET Distribution");
        gStyle->SetOptStat(0);
        Reconstructed_MET_Distribution_clone->Draw("P E1");
        zb_dist_clone->Draw("SAME P E1");
        TLegend* reconstructedLegend = new TLegend(0.48,0.7,0.9,0.9);
        reconstructedLegend->AddEntry( Reconstructed_MET_Distribution );
        reconstructedLegend->AddEntry( zb_dist );
        reconstructed_canvas->SetLogy();
        reconstructedLegend->Draw("SAME");
        outFileName.Form("plots/reconstructed_distributions/reconstructed_distribution_mubin_%d.png",i);
        reconstructed_canvas->Print(outFileName);
        // }}}
    }
    reconstructed_distributions->Write("reconstructed_distributions",TObject::kSingleKey | TObject::kWriteDelete);
    mu_analysis_file->Close()
}
