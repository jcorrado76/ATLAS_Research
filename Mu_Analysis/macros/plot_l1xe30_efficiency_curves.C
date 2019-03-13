{
    TFile* mu_analysis_file = TFile::Open("mu_analysis.root", "READ");
    TObjArray* l1xe30_efficiency_objects = 0;

    mu_analysis_file->GetObject("l1xe30_efficiency_objects", l1xe30_efficiency_objects);
    std::cout << "Successfully got the l1xe30_efficiency_objects: " << l1xe30_efficiency_objects->GetName() << std::endl;
    int number_mu_bins = 7;
    // this needs to be the literal 7 for some reason..
    int Colors[7] = {1,2,3,4,12,6,9};

    TEfficiency* l1xe30_efficiency_curve;
    TString outFileName = "";
    TCanvas* l1xe30_eff_canv = new TCanvas("l1xe30_eff_canv","Canvas with L1XE30 Efficiencies");
    TLegend* correctedLegend = new TLegend(0.48,0.7,0.9,0.9);
    TPaveLabel *title = new TPaveLabel(0.4,0.90,0.7,0.98, "L1XE30 Efficiencies");
    gStyle->SetOptStat(0);
    title->SetFillColor(16);
    title->SetTextFont(42);
    l1xe30_efficiency_curve = ((TEfficiency*)(l1xe30_efficiency_objects->At(0)));
    l1xe30_efficiency_curve->SetLineColor( Colors[0] );
    l1xe30_efficiency_curve->Draw();
    for (int i = 1; i < l1xe30_efficiency_objects->GetLast(); i++){
        correctedLegend->AddEntry( l1xe30_efficiency_curve );
        l1xe30_efficiency_curve = ((TEfficiency*)(l1xe30_efficiency_objects->At(i)));
        l1xe30_efficiency_curve->SetLineColor( Colors[i] );

        l1xe30_efficiency_curve->Draw("SAME");
        correctedLegend->Draw("SAME");
        l1xe30_eff_canv->SetLogy();
    }
    title->Draw("SAME");
    outFileName.Form("plots/L1XE30Efficiency_Curves.png");
    l1xe30_eff_canv->Print(outFileName);
    mu_analysis_file->Close()
}
