#include <TH1F.h>
#include <TFile.h>
#include <TNtuple.h>
#include <TList.h>
#include <TString.h>



void EventsWithinRuns(){
    /* This macro takes in a histogram containing the difference between two other histograms, and displays the bin * number, number of entries in that bin, and the run number in which there is a nonzero difference */

	TString pathname = "$jburr/RunNumberHists.root";

    TFile* diffhistfile = TFile::Open( pathname );
	std::cout << "Opening file: " << pathname << std::endl;

    //histo3 is the difference between jburr and mincer hists
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
  
    TFile* outfile = TFile::Open("$jburr/NonZeroRunNumbers.root","RECREATE");
    //need this line or else there is a ttree write error with the baskets because the ttree was affiliated with the
    //directory of the input file 
    nonzeroRuns->SetDirectory(outfile);
    nonzeroRuns->Write();



}
