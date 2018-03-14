#include <TH1F.h>
#include <TList.h>





void HistListDiffRunNumbers(){

    //for each run number in which there is a difference, create a histogram of the event numbers of both mincer's and
    //jburr's events and see what the overlap by event number is. This would show if either of them included the same
    //file twice, and in which events within a run there is a difference
    
    TList* histlist = 0;

    TString histname = "hist";
    TH1F* histTemp = 0;
    for ( Int j = 0 ; j < nonzeroRuns->GetEntries() ; j++ ){
        histname += j;
        histTemp = new TH1F(histname,histname,5000);

    }
