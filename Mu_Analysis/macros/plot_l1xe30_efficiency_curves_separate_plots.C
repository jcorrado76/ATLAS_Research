{
    TFile* mu_analysis_file = TFile::Open("mu_analysis.root", "READ");
    TObjArray* l1xe30_efficiency_objects = 0;

    mu_analysis_file->GetObject("l1xe30_efficiency_objects", l1xe30_efficiency_objects);
    int number_mu_bins = 7;
    // this needs to be the literal 7 for some reason..
    int Colors[7] = {1,2,3,4,5,6,9};

    TEfficiency* l1xe30_efficiency_curve;
    TString outFileName = "";
    TString canvName = "";
    TString funcName = "";

    for (int i = 0; i <= l1xe30_efficiency_objects->GetLast(); i++){
        canvName.Form("L1XE30 Efficiency for %d < #mu < %d", i*10 , (i+1)*10);
        TCanvas* l1xe30_eff_canv = new TCanvas( canvName );
        l1xe30_eff_canv->SetFillColor(42);
        TLegend* correctedLegend = new TLegend(0.48,0.2,0.9,0.4);
        TPaveLabel *title = new TPaveLabel(0.2,0.9,0.8,0.95, "L1XE30 Efficiencies", "NDC");
        gStyle->SetOptStat(0);
        gStyle->SetOptTitle(0);
        title->SetTextFont(72);
        l1xe30_efficiency_curve = ((TEfficiency*)(l1xe30_efficiency_objects->At(i)));
       funcName.Form("L1XE30 Efficiency Fit for %d < #mu < %d" , i*10, (i+1)*10 );
       l1xe30_efficiency_curve->SetTitle( funcName );
        l1xe30_efficiency_curve->SetLineColor( Colors[i] );
        l1xe30_efficiency_curve->Draw();
        correctedLegend->AddEntry( l1xe30_efficiency_curve );
        l1xe30_eff_canv->SetLogy();
        correctedLegend->Draw("SAME");
        title->Draw("SAME");

        outFileName.Form("plots/l1xe30_efficiencies/L1XE30Efficiency_mu_between_%d_%d.png", i*10, (i+1)*10);
        l1xe30_eff_canv->Print(outFileName);
    }
    mu_analysis_file->Close()
}
