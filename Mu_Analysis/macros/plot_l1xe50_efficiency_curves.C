{
    TFile* mu_analysis_file = TFile::Open("mu_analysis.root", "READ");
    TObjArray* l1xe50_efficiency_objects = 0;

    mu_analysis_file->GetObject("l1xe50_efficiency_objects", l1xe50_efficiency_objects);
    int number_mu_bins = 7;
    // this needs to be the literal 7 for some reason..
    int Colors[7] = {1,2,3,4,12,6,9};

    TEfficiency* l1xe50_efficiency_curve;
    TString outFileName = "";
    TCanvas* l1xe50_eff_canv = new TCanvas("l1xe50_eff_canv","Canvas with l1xe50 Efficiencies");
    TLegend* correctedLegend = new TLegend(0.48,0.1,0.9,0.5);
    // "NDC" means make limits represent fractions of pad
    TPaveLabel *title = new TPaveLabel(0.2,0.9,0.8,0.95, "L1xe50 Efficiencies", "NDC");
    // remove showing of random things
    gStyle->SetOptStat(0);
    // suppress the title of the first object to be drawn
    gStyle->SetOptTitle(0);
    title->SetTextFont(72);
    l1xe50_efficiency_curve = ((TEfficiency*)(l1xe50_efficiency_objects->At(0)));
    // don't plot fit functions
    l1xe50_efficiency_curve->GetListOfFunctions()->Clear();
    l1xe50_efficiency_curve->SetLineColor( Colors[0] );
    correctedLegend->AddEntry( l1xe50_efficiency_curve );
    l1xe50_efficiency_curve->Draw();
    for (int i = 1; i <= l1xe50_efficiency_objects->GetLast(); i++){
        l1xe50_efficiency_curve = ((TEfficiency*)(l1xe50_efficiency_objects->At(i)));
        correctedLegend->AddEntry( l1xe50_efficiency_curve );
        l1xe50_efficiency_curve->GetListOfFunctions()->Clear();
        l1xe50_efficiency_curve->SetLineColor( Colors[i] );

        l1xe50_efficiency_curve->Draw("SAME");
        correctedLegend->Draw("SAME");
        l1xe50_eff_canv->SetLogy();
    }
    title->Draw("SAME");
    gPad->Update();
    l1xe50_efficiency_curve->GetPaintedGraph()->GetXaxis()->SetLimits(0.0,200.0);
    l1xe50_efficiency_curve->GetPaintedGraph()->GetYaxis()->SetLimits(0.0,1.0);

    outFileName.Form("plots/l1xe50Efficiency_Curves.png");
    l1xe50_eff_canv->Print(outFileName);
    mu_analysis_file->Close()
}
