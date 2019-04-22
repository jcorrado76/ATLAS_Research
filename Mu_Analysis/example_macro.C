{
    TFile* mu_analysis_file = TFile::Open("mu_analysis.root", "READ");
    // initialize empty TObjArray
    TObjArray* l1xe30_efficiency_objects = 0;
    // this string matches name in file 
    mu_analysis_file->GetObject("l1xe30_efficiency_objects", l1xe30_efficiency_objects);
    // holder for single element
    TEfficiency* l1xe30_efficiency_curve;
    TString outFileName = "";
    TCanvas* l1xe30_eff_canv = new TCanvas("l1xe30_eff_canv","Canvas with L1XE30 Efficiencies");
    l1xe30_eff_canv->SetFillColor(42);
    TLegend* correctedLegend = new TLegend(0.48,0.2,0.9,0.4);
    // "NDC" means make limits represent fractions of pad
    TPaveLabel *title = new TPaveLabel(0.2,0.9,0.8,0.95, "L1XE30 Efficiencies", "NDC");
    // remove showing of random things
    gStyle->SetOptStat(0);
    // suppress the title of the first object to be drawn
    gStyle->SetOptTitle(0);
    title->SetTextFont(72);
    // the first mu bin often has issues, so draw the second one first so that we avoid axis issues
    l1xe30_efficiency_curve = ((TEfficiency*)(l1xe30_efficiency_objects->At(1)));
    // don't plot fit functions
    l1xe30_efficiency_curve->GetListOfFunctions()->Clear();
    correctedLegend->AddEntry( l1xe30_efficiency_curve );
    l1xe30_efficiency_curve->Draw();

    for (int i = 2; i <= l1xe30_efficiency_objects->GetLast(); i++){
        // get TObject at index i with bounds checking and explicitly cast to TEfficiency
        l1xe30_efficiency_curve = ((TEfficiency*)(l1xe30_efficiency_objects->At(i)));
        correctedLegend->AddEntry( l1xe30_efficiency_curve );
        l1xe30_efficiency_curve->GetListOfFunctions()->Clear();
        l1xe30_efficiency_curve->Draw("SAME");
    }
    l1xe30_efficiency_curve = ((TEfficiency*)(l1xe30_efficiency_objects->At(0)));
    correctedLegend->AddEntry( l1xe30_efficiency_curve );
    l1xe30_efficiency_curve->GetListOfFunctions()->Clear();

    l1xe30_efficiency_curve->Draw("SAME");
    correctedLegend->Draw("SAME");
    l1xe30_eff_canv->SetLogy();
    title->Draw("SAME");

    outFileName.Form("L1XE30Efficiency_Curves.png");
    l1xe30_eff_canv->Print(outFileName);
    mu_analysis_file->Close()
}
