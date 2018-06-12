#define CheckDuplicateEventNumbs_cxx

#include "CheckDuplicateEventNumbs.h"
#include <TH2.h>
#include <TStyle.h>

/* This selector should fill a histogram with the event numbers of the events contained in the mincer tree
 */

void CheckDuplicateEventNumbs::Begin(TTree * /*tree*/)
{

   mincerhist = new TH1F("eventNumHist" , "Event Number Histogram",10000, 0.0, 200.0 );
   //mincerhist = new TH1F("histo1" , "MincerDuplictedRunNumHist",2.1474833e9-2.1474832e9, -2.1474832e9 , 2.1474833e9 );
   TString option = GetOption();
}

void CheckDuplicateEventNumbs::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();
}

Bool_t CheckDuplicateEventNumbs::Process(Long64_t entry)
{
   fReader.SetEntry(entry);
   mincerhist->Fill(*eventnum);
   return kTRUE;
}

void CheckDuplicateEventNumbs::SlaveTerminate()
{

}

void CheckDuplicateEventNumbs::Terminate()
{
    mincerhist->Draw();
}
