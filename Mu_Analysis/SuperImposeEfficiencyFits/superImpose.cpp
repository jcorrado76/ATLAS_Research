void superImpose(){
    TString efficiencyObjectFilePath = "../Root_Files/EfficiencyObjects.root";
    TString efficiencyFitsFilePath = "../Root_Files/EfficiencyFits.root";

    TFile* myfile = TFile::Open(efficiencyObjectFilePath);
    TEfficiency*  MET_Algmu0thru10Efficiency = (TEfficiency*)myfile->Get("metmu0thru10Efficiency");
    TEfficiency*  MET_Algmu10thru20Efficiency =(TEfficiency*)myfile->Get("metmu10thru20Efficiency");
    TEfficiency*  MET_Algmu20thru30Efficiency = (TEfficiency*)myfile->Get("metmu20thru30Efficiency");
    TEfficiency*  MET_Algmu30thru40Efficiency = (TEfficiency*)myfile->Get("metmu30thru40Efficiency");
    TEfficiency*  MET_Algmu40thru50Efficiency = (TEfficiency*)myfile->Get("metmu40thru50Efficiency");
    TEfficiency*  MET_Algmu50thru60Efficiency = (TEfficiency*)myfile->Get("metmu50thru60Efficiency");
    TEfficiency*  MET_Algmu60thru70Efficiency = (TEfficiency*)myfile->Get("metmu60thru70Efficiency");
    std::cout << "Successfully got efficiency objects from file" << std::endl;

    myfile->Close();

    myfile = TFile::Open(efficiencyFitsFilePath);
    TF1*  MET_Algmu0thru10Fit = (TF1*)myfile->Get("metmu0thru10Fit");
    TF1*  MET_Algmu10thru20Fit =(TF1*)myfile->Get("metmu10thru20Fit");
    TF1*  MET_Algmu20thru30Fit = (TF1*)myfile->Get("metmu20thru30Fit");
    TF1*  MET_Algmu30thru40Fit = (TF1*)myfile->Get("metmu30thru40Fit");
    TF1*  MET_Algmu40thru50Fit = (TF1*)myfile->Get("metmu40thru50Fit");
    TF1*  MET_Algmu50thru60Fit = (TF1*)myfile->Get("metmu50thru60Fit");
    TF1*  MET_Algmu60thru70Fit = (TF1*)myfile->Get("metmu60thru70Fit");
    std::cout << "Successfully got efficiency fits from file" << std::endl;

    myfile->Close();

    TCanvas* METCanvmu0thru10 = new TCanvas("canv1", "mu0thru10");
    MET_Algmu0thru10Efficiency->Draw();
    MET_Algmu0thru10Fit->Draw("SAME");



    /*
    mu0thru10FitFunction->SetLineColor(1);
    mu10thru20FitFunction->SetLineColor(2);
    mu20thru30FitFunction->SetLineColor(3);
    mu30thru40FitFunction->SetLineColor(4);
    mu40thru50FitFunction->SetLineColor(12);
    mu50thru60FitFunction->SetLineColor(6);
    mu60thru70FitFunction->SetLineColor(8);

    mu0thru10FitFunction->Draw();
    mu10thru20FitFunction->Draw("SAME");
    mu20thru30FitFunction->Draw("SAME");
    mu30thru40FitFunction->Draw("SAME");
    mu40thru50FitFunction->Draw("SAME");
    mu50thru60FitFunction->Draw("SAME");
    mu60thru70FitFunction->Draw("SAME");

    mycanv->SetTitle("Fits to Efficiency");
    //gPad->SetLogy();
    TLegend* legend = new TLegend();
    legend->AddEntry(mu0thru10FitFunction, "mu 0 to 10");
    legend->AddEntry(mu10thru20FitFunction , "mu 10 to 20");
    legend->AddEntry(mu20thru30FitFunction, "mu 20 to 30");
    legend->AddEntry(mu30thru40FitFunction, "mu 30 to 40");
    legend->AddEntry(mu40thru50FitFunction, "mu 40 to 50");
    legend->AddEntry(mu50thru60FitFunction , "mu 50 to 60");
    legend->AddEntry(mu60thru70FitFunction , "mu 60 to 70");
    legend->Draw("SAME");
    gStyle->SetOptStat(0);

    TImage *img = TImage::Create();
    img->FromPad(mycanv);
    img->WriteImage("../Plots/EfficiencyFits.png");

    TFile* FitFile = TFile::Open( efficiencyFitsFilePath , "RECREATE" );
    mu0thru10FitFunction->Write();
    mu10thru20FitFunction->Write();
    mu20thru30FitFunction->Write();
    mu30thru40FitFunction->Write();
    mu40thru50FitFunction->Write();
    mu50thru60FitFunction->Write();
    mu60thru70FitFunction->Write();

    FitFile->Close();
   */ 
}
