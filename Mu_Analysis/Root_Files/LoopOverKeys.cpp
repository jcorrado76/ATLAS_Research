{
    TFile* myfile = TFile::Open("EfficiencyFits.root");
    TCanvas* mycanv = new TCanvas("mycanv","FitsCanvas");
    for (const auto&& keyObj : *(file->GetListOfKeys()) ){
        auto key = (TKey*) keyObj;
        TH1F* CurrentHist = (TH1F*) key->ReadObj();
        CurrentHist->Draw();
    }
}
