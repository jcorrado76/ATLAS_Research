#include <TH1F.h>
#include <TList.h>





void HistListDiffRunNumbers(){

    //for each run number in which there is a difference, create a histogram of the event numbers of both mincer's and
    //jburr's events and see what the overlap by event number is. This would show if either of them included the same
    //file twice, and in which events within a run there is a difference
    
    TFile* mincerfile = TFile::Open("$DATA/ZeroBiasL1KF2016R307195R311481.51Runs.root","READ");  
    TFile* jburrfile = TFile::Open("data/totalntuple16.root","READ");

    TTree* mincertree = (TTree*) mincerfile->Get("tree");
    TTree* burrtree = (TTree*) jburrfile->Get("METTree");

    UInt_t RunNumber;
    //TODO: needs to be changed to maximum and minimum event number...
    Int_t MincerEventNumMinimum = 958225964;
    Int_t MincerEventNumMaximum = ;
    Int_t JburrEventNumMinimum = 4981632;
    Int_t JburrEventNumMaximum = 7.04e9;

    Int_t runLow = 307195;
    Int_t runHigh = 311481;
    Int_t nbins = 10000;

    Int_t mincerRunNumber, jburrRunNumber;
    Int_t mincerpassrndm;
    Bool_t jburrpassrndm;

    TList* mincerhistlist = 0;
    TList* staggeredmincerhistlist = 0;
    TList* burrhistlist = 0;
    TList* canvaslist = 0;

    TH1F* mincerhist = 0;    
    TH1F* burrhist = 0;  

    TString* mincerhistname = "mincerhist";
    TString* burrhistname = "burrhist"
   
    for ( Int j = 0 ; j < nonzeroRuns->GetEntries() ; j++ ){
        //for each nonzero run number, fill 2 histograms with events distributed by event number 
        //append each hist to the corresponding tlist
        //then make the difference hist ; add to corresponding tlist
        //then make the canvas of the staggered version of the hist and add to corresponding tlist 

        mincerhistname += j;
        burrhistname += j;

        mincerhist = new TH1F( mincerhistname , mincerhistname , nbins , MincerEventNumMinimum, MincerEventNumMaximum);
        burrhist = new TH1F( burrhistname , burrhistname , nbins , JburrEventNumMinimum, JburrEventNumMaximum);


    }




    mincertree->SetBranchAddress("runnum",&mincerRunNumber);
    mincertree->SetBranchAddress("passrndm",&mincerpassrndm);
    burrtree->SetBranchAddress("HLT_noalg_zb_L1ZB.passed",&jburrpassrndm);
    burrtree->SetBranchAddress("RunNumber",&RunNumber);


    Int_t mincerentries = mincertree->GetEntries();
    Int_t burrentries = burrtree->GetEntries();


    for ( Int_t i = 0 ; i < mincerentries ; i++){
        mincertree->GetEntry(i);
        if (mincerpassrndm > 0.5 && mincerRunNumber < 310000 ){
        mincerhist->Fill(mincerRunNumber + 10.);
        }
    }

    for ( Int_t i = 0 ; i < burrentries; i++){
        burrtree->GetEntry(i);
        if (jburrpassrndm && RunNumber < runHigh && RunNumber > runLow){
        burrhist->Fill(RunNumber);
        }
    }

    mincerhist->SetLineColor(kRed);
    burrhist->SetLineColor(kBlue);

    //create a new file containing the Tlists of jburr hists, mincer hists, diff hists, and combined tcanvases
    TFile* outfile = new TFile::Open("HistList.root", "RECREATE");
}
