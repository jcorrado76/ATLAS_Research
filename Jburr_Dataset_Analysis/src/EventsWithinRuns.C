#include <TH1F.h>
#include <TFile.h>
#include <TNtuple.h>





void EventsWithinRuns(){


    TFile* diffhistfile = TFile::Open("$jburr/RunNumberHists.root");

    TH1F* diffhist = (TH1F*)diffhistfile->Get("histo3");

    Int_t Nentries = 0;
    Int_t RunNumber = 0;
    Int_t Gbin = 0;


    TNtuple* nonzeroRuns = new TNtuple("ntuple" , "Non-zero Run Numbers" , "Global_Bin:Entries:Run_Number");


    for ( Int_t i = 0 ; i < diffhist->GetNbinsX() ; i++ ){
        if ( diffhist->GetBinContent(i) != 0 ){

            Gbin = i;
            Nentries = diffhist->GetBinContent(i);
            RunNumber = diffhist->GetBinCenter(i);
            
            std::cout << "|| Bin: " << i << " || Entries: " << diffhist->GetBinContent(i) << " || Run Number: " << diffhist->GetBinCenter(i) << std::endl;
            nonzeroRuns->Fill( Gbin , Nentries , RunNumber );
        }
    }

    nonzeroRuns->Scan();
  





}
