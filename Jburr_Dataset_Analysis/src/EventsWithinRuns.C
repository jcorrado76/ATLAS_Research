




void EventsWithinRuns(){


    TFile* diffhistfile = TFile::Open("../RunNumberHists.root");

    TH1F* diffhist = (TH1F*)diffhistfile->Get("histo3");





    for ( Int_t i = 0 ; i < diffhist->GetNBins() ; i++ ){
        if ( diffhist->GetBinContent(i) != 0 ){
            std::cout << "|| Bin: " << i << " || Entries: " << diffhist->GetBinContent(i) << " || Run Number: " << diffhist->GetBinCenter(i) << std::endl;
        }
    }


}
