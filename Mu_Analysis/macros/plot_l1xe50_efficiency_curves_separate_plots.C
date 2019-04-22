{
    TFile* mu_analysis_file = TFile::Open("mu_analysis.root", "READ");
    TObjArray* l1xe50_efficiency_objects = 0;

    mu_analysis_file->GetObject("l1xe50_efficiency_objects", l1xe50_efficiency_objects);

    TEfficiency* l1xe50_efficiency_curve;
    TString outFileName = "";
    TString canvName = "";

    for (int i = 0; i <= l1xe50_efficiency_objects->GetLast(); i++){
        canvName.Form("L1XE50 Efficiency for %d < #mu < %d", i*10 , (i+1)*10);
        TCanvas* l1xe50_eff_canv = new TCanvas(canvName);
        l1xe50_eff_canv->SetFillColor(42);
        TLegend* correctedLegend = new TLegend(0.48,0.2,0.9,0.4);
        TPaveLabel *title = new TPaveLabel(0.2,0.9,0.8,0.95, canvName , "NDC");
        gStyle->SetOptStat(0);
        gStyle->SetOptTitle(0);
        title->SetTextFont(72);
        l1xe50_efficiency_curve = ((TEfficiency*)(l1xe50_efficiency_objects->At(i)));
        correctedLegend->AddEntry( l1xe50_efficiency_curve );
        l1xe50_efficiency_curve->Draw();
        correctedLegend->Draw("SAME");
        l1xe50_eff_canv->SetLogy();
        title->Draw("SAME");

        outFileName.Form("plots/l1xe50_efficiencies/L1XE50Efficiency_mu_between_%d_%d.png", i*10, (i+1)*10);
        l1xe50_eff_canv->Print(outFileName);
    }
    mu_analysis_file->Close()
}
