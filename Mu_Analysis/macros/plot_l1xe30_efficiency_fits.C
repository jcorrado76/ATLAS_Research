{
    TFile* mu_analysis_file = TFile::Open("mu_analysis.root", "READ");
    TObjArray* l1xe30_efficiency_fit_objects = 0;

    mu_analysis_file->GetObject("l1xe30_efficiency_fit_objects", l1xe30_efficiency_fit_objects);

    TF1* l1xe30_efficiency_fit;
    TString outFileName = "";
    TString Name;
    TCanvas* l1xe30_eff_canv = new TCanvas("l1xe30_eff_canv","Canvas with L1XE30 Efficiency Fits");
    l1xe30_eff_canv->SetFillColor(42);
    TLegend* correctedLegend = new TLegend(0.48,0.2,0.9,0.4);
    // "NDC" means make limits represent fractions of pad
    TPaveLabel *title = new TPaveLabel(0.2,0.9,0.8,0.95, "L1XE30 Efficiency Fits", "NDC");
    // remove showing of random things
    gStyle->SetOptStat(0);
    // suppress the title of the first object to be drawn
    gStyle->SetOptTitle(0);
    title->SetTextFont(72);
    l1xe30_efficiency_fit = ((TF1*)(l1xe30_efficiency_fit_objects->At(1)));
   Name.Form("L1XE30 Efficiency Fit for %d < #mu < %d;CELL MET [GeV];#epsilon" , 10, 20 );
   l1xe30_efficiency_fit->SetTitle( Name );
    correctedLegend->AddEntry( l1xe30_efficiency_fit );
    l1xe30_efficiency_fit->Draw();

    // to fix plotting. draw the mubin 0 first because it was messing everything up
    for (int i = 2; i <= l1xe30_efficiency_fit_objects->GetLast(); i++){
        l1xe30_efficiency_fit = ((TF1*)(l1xe30_efficiency_fit_objects->At(i)));
       Name.Form("L1XE30 Efficiency Fit for %d < #mu < %d;CELL MET [GeV];#epsilon" , i*10,(i+1)*10  );
       l1xe30_efficiency_fit->SetTitle( Name );
        correctedLegend->AddEntry( l1xe30_efficiency_fit );
       l1xe30_efficiency_fit->Draw("SAME");
    }
    l1xe30_efficiency_fit = ((TF1*)(l1xe30_efficiency_fit_objects->At(0)));
   Name.Form("L1XE30 Efficiency Fit for %d < #mu < %d;CELL MET [GeV];#epsilon" , 0,10  );
   l1xe30_efficiency_fit->SetTitle( Name );
    correctedLegend->AddEntry( l1xe30_efficiency_fit );

    l1xe30_efficiency_fit->Draw("SAME");
    correctedLegend->Draw("SAME");
    l1xe30_eff_canv->SetLogy();
    title->Draw("SAME");

    outFileName.Form("plots/L1XE30Efficiency_Fits.png");
    l1xe30_eff_canv->Print(outFileName);
    mu_analysis_file->Close()
}
